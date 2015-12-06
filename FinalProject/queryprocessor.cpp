/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/

#include "queryprocessor.h"

/*QueryProcessor::QueryProcessor()
{

}*/

QueryProcessor::~QueryProcessor()
{

}

QueryProcessor::QueryProcessor(IndexInterface& theIndex) : index(theIndex)
{
    sortedResults = vector<resultPair>();
}

void QueryProcessor::display_best_fifteen_results()
{
    int max;
    int numResults = sortedResults.size();
    if (numResults == 0)
    {
        cout<<"Sorry, there were no results for your query.\n";
        return;
    }
    if (numResults < 15) max = numResults;
    else max = 15;

    cout<<"Results\n";
    for (int i=1; i<=max; ++i)
    {
        index.display_result(i, sortedResults.at(i-1).first, sortedResults.at(i-1).second);
    }
    cout<<"Would you like to read the text of one of the results?\n=>\tYes\n=>\tNo\n";
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    while((input.compare("yes") != 0)
          && (input.compare("no") != 0))
    {
        cout<<"Invalid command\n";
        cout<<"Would you like to read the text of (one of) the result(s)?\n";
        cin >> input;
    }
    if (input.compare("no") == 0) return;
    else
    {
        if (numResults == 1){
            index.display_page_content(sortedResults.at(0).first);
            return;
        }
        cout<<"Which document?  Enter a rank #:\n";
        cin>>input;
        int numInput = stoi(input);
        while (!((numInput > 0)
               && (numInput <= max)))
        {
            cout<<"Invalid command\n";
            cout<<"Which document?  Enter a rank #\n";
            cin >> input;
            numInput = stoi(input);
        }
        index.display_page_content(sortedResults.at(numInput-1).first);
    }
}

void QueryProcessor::display_only_multi_word(string full_query)
{
    int max;
    int numResults = sortedResults.size();
    if (numResults == 0)
    {
        cout<<"Sorry, there were no results for your query.\n";
        return;
    }
    if (numResults < 15) max = numResults;
    else max = 15;

    cout<<"Results\n";
    for (int i=1; i<=max; ++i)
    {
        cout << "====" << endl;
        index.display_result_multi_word(i, sortedResults.at(i-1).first, sortedResults.at(i-1).second, full_query);
    }
    cout<<"Would you like to read the text of one of the results?\n=>\tYes\n=>\tNo\n";
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    while((input.compare("yes") != 0)
          && (input.compare("no") != 0))
    {
        cout<<"Invalid command\n";
        cout<<"Would you like to read the text of (one of) the result(s)?\n";
        cin >> input;
    }
    if (input.compare("no") == 0) return;
    else
    {
        if (numResults == 1){
            index.display_page_content_multi_word(sortedResults.at(0).first, full_query);
            return;
        }
        cout<<"Which document?  Enter a rank #:\n";
        cin>>input;
        int numInput = stoi(input);
        while (!((numInput > 0)
               && (numInput <= max)))
        {
            cout<<"Invalid command\n";
            cout<<"Which document?  Enter a rank #\n";
            cin >> input;
            numInput = stoi(input);
        }

        index.display_page_content_multi_word(sortedResults.at(numInput-1).first, full_query);
    }
}

void QueryProcessor::init_relev_map(Term* term)
{
    for (auto & page : term->get_pageAprns())
    {
        results.emplace(make_pair(page.first, term->get_tdidf_for_page(page.first)));
    }
}

void QueryProcessor::intersection_incr_relev_map(Term* term)
{
    // Make a new relevancy map to store the insersection of
    // pageIDs and TD/IDFs with incremented TD/IDF values from the
    // current queried term;

    relevancyMap intersection;

    for (auto& page : term->get_pageAprns())
    {
        // See if the pageID is in results.
        try
        {
            results.at(page.first);
        }
        // If not, skip this page.
        catch (const out_of_range& notInResults)
        {
            continue;
        }
        // If it is, add the two TD/IDF values together and emplace the
        // new value in the intersection relevancyMap.
        double tdidf = results.at(page.first);
        tdidf += index.calc_tdidf(page.first, page.second, term->get_spread());
        intersection.emplace(make_pair(page.first, tdidf));
    }
    results = intersection;
}

void QueryProcessor::union_incr_relev_map(Term* term)
{
    for (auto& page : term->get_pageAprns())
    {
        // See if the pageID is in results.
        try
        {
            results.at(page.first);
        }

        // If not, add it to results.
        catch (const out_of_range& notInResults)
        {
            results.emplace(make_pair(page.first, term->get_tdidf_for_page(page.first)));
            continue;
        }

        // If the pageID is in results, increase that entry's
        // TD/IDF value by the this term's TD/IDF value on that page.
        results.at(page.first)+=term->get_tdidf_for_page(page.first);
    }
}

void QueryProcessor::answer_query(istringstream& query, string full_query, bool intersection)
{
    string currTerm;
    string search_string = full_query;

    // Find the intersection of all queried terms,
    // adding the TD/IDF values from each term.

    // Add functioanlity for NOT

    // Put the first queried term into results.
    query >> currTerm;
    Porter2Stemmer::stem(currTerm);
    Term* foundTerm = index.find_term(currTerm);
    if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
    else
    {
        foundTerm->init_tdidfs(index);
        init_relev_map(foundTerm);
    }

    while (query >> currTerm)
    {
        if (currTerm.compare("not") == 0)
        {
            // Get the next word.
            query >> currTerm;
             cout << "CurrTerm: Next Word " << currTerm << endl;
            Porter2Stemmer::stem(currTerm);

            foundTerm = index.find_term(currTerm);
            if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
            else
            {
                foundTerm->init_tdidfs(index);
                // For each pageID in foundTerm, remove it from results
                // if that pageID is in results.
                for (auto& page : foundTerm->get_pageAprns())
                {
                    try
                    {
                        results.at(page.first);
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is in results, remove that entry.
                    results.erase(page.first);
                }
            }
        }
        else
        {
            // Find the intersection of the words, adding together the TD/IDF
            // values so far and the TD/IDF values for this term.
            foundTerm = index.find_term(currTerm);
            if (!foundTerm) cout<<"The term \""<<currTerm<<"\" never appeared in the corpus\n";
            else
            {
                foundTerm->init_tdidfs(index);
                if (intersection) intersection_incr_relev_map(foundTerm);
                else union_incr_relev_map(foundTerm);
            }
        }
    }
    bool multi_word = false;

    if (search_string.find(' ') < search_string.length())
    {
        cout << "This is a multi-word query" << endl;
        sort_results(true);
        display_only_multi_word(search_string);
    }
    else
    {
        sort_results(false);
        display_best_fifteen_results();
    }
}

void QueryProcessor::initiate_query(string query)
{
    // Used later to remake the stream with the first word added back in.
    string fullQuery = query;

    // Remove all non-letters from the query.
    replace_if(query.begin(), query.end(), is_not_alpha, ' ');

    // Make all letters lowercase.
    transform(query.begin(), query.end(), query.begin(), ::tolower);


    istringstream stream(query);

    // Initiate the proper kind of query.
    string mode;
    stream >> mode;

    if (mode.compare("and") == 0) answer_query(stream, fullQuery, true);
    else if (mode.compare("or") == 0) answer_query(stream, fullQuery, false);
    else
        // Regular query.  Treat is as an AND query because
        // the section where the instersection variable matters will never be reached.
    {
        cout << "Initiating query:  " << fullQuery << endl;
        stream = istringstream(fullQuery);
        answer_query(stream, fullQuery, true);
    }
}

void QueryProcessor::sort_results(bool multi_word)
{
    // To find the top results, some
    relevancyMap resultsToSort = results;
    int number_to_sort;

 /*   if (multi_word)
        number_to_sort = 10,000;
    else */
        number_to_sort = 16;


    while (resultsToSort.size() != 0 && ((sortedResults.size() < number_to_sort) || multi_word))
    {
        int maxKey = 0;

        // Make sure that key is in the results.
        bool isInResults = false;
        while (!isInResults)
        {
            try
            {
                resultsToSort.at(maxKey);
            }
            catch (const out_of_range& notInResultsToSort)
            {
                ++maxKey;
                continue;
            }
            // If it reaches here, the key was in results,
            // so set isInResults to true.
            isInResults = true;
        }

        // Find the maximum TD/IDF in results and emplace it
        // in sortedResults.
        for (auto& result : resultsToSort)
        {
            if (result.second > results.at(maxKey)) maxKey = result.first;
        }
        sortedResults.push_back(make_pair(maxKey, resultsToSort.at(maxKey)));
        resultsToSort.erase(maxKey);
    }
}
