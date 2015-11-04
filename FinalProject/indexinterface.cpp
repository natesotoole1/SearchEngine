/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/
#include "indexinterface.h"

struct threadArgData;

IndexInterface::IndexInterface() : parser(*(new DocParser(*this)))
{
    totalWordsInCorpus = 0;
    infoForIDs = vector<PageInfo*>();
}

IndexInterface::~IndexInterface()
{

}

void IndexInterface::append_page_info(PageInfo* currInfo)
{
    infoForIDs.push_back(currInfo);
}

void IndexInterface::display_result(int rank, int pageID, double tdidf)
{
    PageInfo* resultInfo = infoForIDs.at(pageID);
    cout<<"#"<<rank<<": \""<<resultInfo->get_title()<<"\"\n";
    cout<<"\tTotal TDF/IDF value: "<<tdidf<<endl;
    cout<<"\tTimestamp: "<<resultInfo->get_timestamp()<<endl;
    cout<<"\tContributor name or IP Address: "<<resultInfo->get_contributor()<<endl;
}

void IndexInterface::display_page_content(int pageID)
{
    cout<<"Text displayed below:\n=======================\n";
    cout<<infoForIDs.at(pageID)->get_content()<<endl;
}


int IndexInterface::index_for_letter(char letter)
{
    // Get the raw ASCII value of the letter.
    int ascii = (int)letter;

    // If the letter is uppercase, get the lowercase equivalent
    // by increasing its ASCII value by 32.
    if (ascii > 64 && ascii < 91) ascii += 32;

    // a's ASCII value is 97; b's is 98, and so on...
    // To get the return value, subtract 96.
    ascii -= 97;
    return ascii;
}

PageInfo* IndexInterface::info_for_pageID(int pageID)
{
    return infoForIDs.at(pageID);
}

void IndexInterface::read_file(string filePath)
{
    parser.read_file(filePath);
}

double IndexInterface::calc_tdidf(int pageID, int freq, int spread)
{
    // In case the persistence index grew through read_file.
    try
    {
        infoForIDs.at(pageID);
    }
    catch (out_of_range& notInPageIDs)
    {
        return 0;
    }

    // Calculate TF value.
    int totalWords = infoForIDs.at(pageID)->get_totalWords();
    double tf = (double)freq/totalWords;

    // Calculate IDF value.
    int totalDocsInCorpus = infoForIDs.size();
    double idf = log((double)totalDocsInCorpus/spread);

    return tf*idf;
}

void IndexInterface::incr_total_words_on_page(int currID, int incr)
{
    try
    {
        infoForIDs.at(currID);
    }
    catch (out_of_range& notInPageInfos)
    {
        return;
    }
    infoForIDs.at(currID)->incr_totalWords(incr);
}

void IndexInterface::read_pers_file(int index)
{
    cout<<"("<<index+1<<"/26)...\n";

    ifstream ifs;
    string filePath = to_string(index) + ext;
    ifs.open(filePath);

    // Load two words at a time.
    string word1, word2;

    ifs >> word1 >> word2;

    while (!ifs.eof())
    {
        // For each new term, extract two words at a time until
        // another exclamation point is reached.
        if (word1.compare("!") == 0)
        {
            pageMap pageAprns;
            string name = word2;

            ifs >> word1 >> word2;

            // For each subsequent pageID-frequency pair, add that to pageAprns
            // and increment that pageID's totalWords.
            while ((word1.compare("!") != 0) && (!ifs.eof()))
            {

                int num1 = stoi(word1);
                int num2 = stoi(word2);

                pageAprns.emplace(make_pair(num1, num2));

                // Increment the totalWords for currID by the freq.
                incr_total_words_on_page(num1, num2);
                ifs >> word1 >> word2;
            }
            add_term_to_ii(index, new Term(name, pageAprns));
        }
    }
    ifs.close();
}

void IndexInterface::read_persistence_files()
{
    cout<<"Reading persistence documents...\n";
    for (int i=0; i<26; ++i) read_pers_file(i);
}

int IndexInterface::get_totalPages(){
    return infoForIDs.size();
}

int IndexInterface::get_totalWordsInCorpus()
{
    if (totalWordsInCorpus == 0)
    {
        for (int i=0; i<infoForIDs.size(); ++i) totalWordsInCorpus += infoForIDs.at(i)->get_totalWords();
    }
    return totalWordsInCorpus;
}
