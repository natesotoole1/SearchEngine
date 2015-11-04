#include "docparser.h"

DocParser::DocParser(IndexInterface& theIndex) : index(theIndex)
{
    // Add all stop words to stopWords.

    // Load the list of stop from the build directory.
    ifstream ifs("StopWords.txt");

    string word;
    // For each line in the stop words file (there is only one
    // word per line, add that word as if it were an appearance.
    // This function will only be called by letters[0].
    while (ifs >> word)
    {
        word = clean_term(word);
        stopWords.emplace(make_pair(word, word));
    }
}

DocParser::~DocParser()
{

}


string DocParser::clean_term(string term)
{
    // Stem term.
    Porter2Stemmer::stem(term);

    // Remove all uppercase letter from term.
    transform(term.begin(), term.end(), term.begin(), ::tolower);

    return term;
}

void DocParser::clear()
{
    stopWords.erase(stopWords.begin(), stopWords.end());
}

int DocParser::index_for_letter(char letter)
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

void DocParser::read_page(xml_node<>* currNode, bool readText)
{
    // Regardless, init the pageInfo for this page.

    // Get the page title.

    currNode = currNode->first_node();
    currTitle = currNode->value();

    // Get the timestamp.

    // Go to 'revision' node.
    currNode = currNode->next_sibling("revision");

    // Move one level inward.
    currNode = currNode->first_node();

    // Get timestamp.
    currNode = currNode->next_sibling("timestamp");
    currTimestamp = currNode->value();

    // Get contributor or IP address.
    currNode = currNode->next_sibling("contributor");
    currContributorNameOrIP = currNode->value();

    // Go to 'text' node.
    currNode = currNode->next_sibling("text");
    currContent = currNode->value();

    // Having found all info for this page, push back a new
    // PageInfo object to the index's infoForIDs.
    index.append_page_info(new PageInfo(
                               currContent, currContributorNameOrIP, currTimestamp, currTitle));

    // If text should be read (i.e. it's a new file),
    // call read_text.
    if (readText) read_text(currNode);
}

void DocParser::read_text(xml_node<>* currNode)
{
    int currID = index.get_totalPages()-1;
    currContent = currNode->value();

    // Replace all non-letters with whitespace char.
    // Got from http://stackoverflow.com/questions/5540008/need-a-regular-expression-
    // to-extract-only-letters-and-whitespace-from-a-string
    replace_if(currContent.begin(), currContent.end(),
               is_not_alpha,
               ' '
               );

    istringstream stream(currContent);

    while (stream >> currWord)
    {
        // Increment the totalWords for currID.
        index.incr_total_words_on_page(currID, 1);

        // Loads whatever characters are between each pair of whitespaces,
        // so clean it.
        currWord = clean_term(currWord);

        // If the currTerm a stop word, or it's longer than 12
        // characters, forego adding it to allTerms.
        if ((is_stop_word(currWord))
                || (currWord.length() > 12)) continue;

        found = index.find_term(currWord);

        // If the word isn't already in the index, push back a new Term with 1 pageAprn at (currID, 1);

        if (!found)
        {
            pageMap aprn;
            aprn.emplace(make_pair(currID, 1));
            index.add_term_to_ii(index_for_letter(currWord.front()), new Term(currWord, aprn));
        }

        // Otherwise, increment that Term's freq by 1 for that doc if it has appeared there.
        else found->incrm_aprn_for_pageID(currID);
    }
}

void DocParser::init_file_page_infos(xml_node<> *currNode, bool readText)
{
    read_page(currNode, readText);
    // Index the remaining pages in the file.

    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        read_page(currNode, readText);
    }
}

void DocParser::read_file(string filePath)
{
    // Use RapidXML's "parse" function to make all data
    // accessible via nodes and values.
    file<> theFile(filePath.c_str());
    xml_document<> theDoc;
    theDoc.parse<0>(theFile.data());

    // Find the first node with name 'mediawiki'.
    xml_node<>* currNode = theDoc.first_node();

    // Go to 'siteinfo'.
    currNode = currNode->first_node();

    // Go to the first 'page'.
    currNode = currNode->next_sibling();

    if (filePath.compare("WikiBooks.xml") == 0)
    {
        cout<<"Initializing info for corpus pages...\n";
        init_file_page_infos(currNode, false);
        index.read_persistence_files();
    }
    else
    {
        init_file_page_infos(currNode, true);
        index.write_persistence_files();
    }
}

bool DocParser::is_stop_word(string term)
{
    // Use term as the key and see if it is in the stopWordMap.
    try
    {
        stopWords.at(term);
    }
    catch (const out_of_range& notAStopWord)
    {
        return false;
    }
    return true;
}
