/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/06/15
 * Nate O'Toole
 * Brandon McFarland
 * Ashvin Asava
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
    //queries = new QueryProcessor(index);
}


void QueryProcessor::initiate_query(string query)
{
    // Used later to remake the stream with the first word added back in.
    string fullQuery = query;


    // Make all letters lowercase.
    transform(query.begin(), query.end(), query.begin(), ::tolower);




    istringstream stream(query);

    // Initiate the proper kind of query.
    string mode;
    stream >> mode;
    string currString = query;
    string notQueryString;
    string queryString;
    string queryType;
    int typeBool;
    string oneWord;


    if (mode.compare("and") == 0){
        typeBool = 0;
        queryType = currString.substr(0,3);
        int x = 3;
        while(currString[x] == ' '){
            x++;
        }
        currString = currString.erase(0,x);
        if(currString.find("not") == -1){
             queryTypeNum = 0;

            //  Check for two-word
            if (currString.find('[') != -1)
            {
                int i = currString.find_first_of('[');
                while(i < currString.length()){
                    int j = currString.find_first_of(']');


                    multiWords.push_back(currString.substr(i+1, j-i-1));
                    while(currString[j + 1] == ' '){
                        j++;
                    }
                    if(currString[i-1] != ' '){
                        j--;
                    }
                    while(currString[i-2] == ' '){
                        i--;
                    }

                    currString = currString.erase(i, j - i + 1);
                    i = currString.find_first_of('[');
                }

            }
            if(currString.length() > 2){
                istringstream oneWords(currString);
                oneWords >> oneWord;

                singleWords.push_back(oneWord);
                while(oneWords >> oneWord){

                    singleWords.push_back(oneWord);
                }
            }
        }else{
                queryTypeNum = 1;
                int numForNot = currString.find("not");
                while(currString[numForNot] == ' '){
                    numForNot ++;
                }
                queryString = currString.substr(0, numForNot);

                notQueryString = currString.substr(numForNot);
                int x = 3;

                while(notQueryString[x] == ' '){
                    x++;
                }
                notQueryString = notQueryString.erase(0, x);
                if (notQueryString.find('[') != -1)
                {
                    int i = notQueryString.find_first_of('[');
                    while(i < notQueryString.length()){
                        int j = notQueryString.find_first_of(']');
                        multiNotWords.push_back(notQueryString.substr(i+1, j-i-1));
                        while(notQueryString[j + 1] == ' '){
                            j++;
                        }
                        if(notQueryString[i-1] != ' '){
                            j--;
                        }
                        while(notQueryString[i-2] == ' '){
                            i--;
                        }

                        notQueryString = notQueryString.erase(i, j - i + 1);
                        i = notQueryString.find_first_of('[');
                    }

                }
                if(notQueryString.length() > 2){
                    istringstream oneWords(notQueryString);
                    oneWords >> oneWord;
                    singleNotWords.push_back(oneWord);
                    while(oneWords >> oneWord){
                        singleNotWords.push_back(oneWord);
                    }
                }

                if (queryString.find('[') != -1)
                {
                    int i = queryString.find_first_of('[');
                    while(i < queryString.length()){
                        int j = queryString.find_first_of(']');
                        multiWords.push_back(queryString.substr(i+1, j-i-1));
                        while(queryString[j + 1] == ' '){
                            j++;
                        }
                        if(queryString[i-1] != ' '){
                            j--;
                        }
                        while(queryString[i-2] == ' '){
                            i--;
                        }

                        queryString = queryString.erase(i, j - i + 1);
                        i = queryString.find_first_of('[');
                    }

                }
                if(queryString.length() > 2){
                    istringstream oneWords(queryString);
                    oneWords >> oneWord;
                    singleWords.push_back(oneWord);
                    while(oneWords >> oneWord){
                    singleWords.push_back(oneWord);
                }
                }
       }


    }
    else if (mode.compare("or") == 0){
        typeBool = 1;
        queryType = currString.substr(0, 2);
        int x = 2;
        while(currString[x] == ' ' ){
            x++;
        }
        currString = currString.erase(0,x);
        if(currString.find("not") == -1){
            queryTypeNum = 2;
            //  Check for two-word
            if (currString.find('[') != -1)
            {
                int i = currString.find_first_of('[');
                while(i < currString.length()){
                    int j = currString.find_first_of(']');
                    multiWords.push_back(currString.substr(i+1, j-i-1));
                    while(currString[j + 1] == ' '){
                        j++;
                    }
                    if(currString[i-1] != ' '){
                        j--;
                    }
                    while(currString[i-2] == ' '){
                        i--;
                    }

                    currString = currString.erase(i, j - i + 1);
                    i = currString.find_first_of('[');
                }

            }
            if(currString.length() > 2){
                istringstream oneWords(currString);
                oneWords >> oneWord;
                singleWords.push_back(oneWord);
                while(oneWords >> oneWord){
                    singleWords.push_back(oneWord);
                }

            }
        }else{
            queryTypeNum = 3;
                int numForNot = currString.find("not");
                queryString = currString.substr(0, numForNot);
                notQueryString = currString.substr(numForNot);
                int x = 3;

                while(notQueryString[x] == ' '){
                    x++;
                }
                notQueryString = notQueryString.erase(0, x);
                if (notQueryString.find('[') != -1)
                {
                    int i = notQueryString.find_first_of('[');
                    while(i < notQueryString.length()){
                        int j = notQueryString.find_first_of(']');
                        multiNotWords.push_back(notQueryString.substr(i+1, j-i-1));
                        while(notQueryString[j + 1] == ' '){
                            j++;
                        }
                        if(notQueryString[i-1] != ' '){
                            j--;
                        }
                        while(notQueryString[i-2] == ' '){
                            i--;
                        }

                        notQueryString = notQueryString.erase(i, j - i + 1);
                        i = notQueryString.find_first_of('[');
                    }

                }
                if(notQueryString.length() > 2){
                    istringstream oneWords(notQueryString);
                    oneWords >> oneWord;
                    singleNotWords.push_back(oneWord);
                    while(oneWords >> oneWord){
                        singleNotWords.push_back(oneWord);
                    }
                }

                if (queryString.find('[') != -1)
                {
                    int i = queryString.find_first_of('[');
                    while(i < queryString.length()){
                        int j = queryString.find_first_of(']');
                        multiWords.push_back(queryString.substr(i+1, j-i-1));
                        while(queryString[j + 1] == ' '){
                            j++;
                        }
                        if(queryString[i-1] != ' '){
                            j--;
                        }
                        while(queryString[i-2] == ' '){
                            i--;
                        }

                        queryString = queryString.erase(i, j - i + 1);
                        i = queryString.find_first_of('[');
                    }

                }
                if(currString.length() > 2){
                    istringstream oneWords(queryString);
                    oneWords >> oneWord;
                    singleWords.push_back(oneWord);
                    while(oneWords >> oneWord){
                        singleWords.push_back(oneWord);
                    }
               }
       }
    }

    else if(query.find("not") != -1){
        typeBool = 0;
        int nt = query.find("not");
        string newQuery = fullQuery;
        newQuery = newQuery.erase(nt,3);
        queryTypeNum = 5;
        int wordCount = 0;
        while(wordCount != 2){

            if(wordCount == 0){
                if (newQuery.find('[') != -1){
                      int i = newQuery.find('[');
                      int j = newQuery.find(']');
                      multiWords.push_back(newQuery.substr(i + 1, j-1));
                      while(newQuery[j+1] == ' '){
                        j++;
                      }
                      wordCount ++;
                      newQuery.erase(i, j+1);
                }if(newQuery.length() > 2){
                    istringstream f(newQuery);
                    string temp;
                    f >>  temp;
                    singleWords.push_back(temp);
                    wordCount ++;
                }
            }else{
                if (newQuery.find('[') != -1){
                      int i = newQuery.find('[');
                      int j = newQuery.find(']');
                      multiNotWords.push_back(newQuery.substr(i + 1, j-1));
                      while(newQuery[j+1] == ' '){
                        j++;
                      }
                      wordCount ++;
                      newQuery.erase(i, j+1);

                }
                if(newQuery.length() > 2){
                    istringstream f(newQuery);
                    string temp;
                    f >>  temp;
                    singleNotWords.push_back(temp);
                    wordCount++;
                }
            }
       }
    }
    else{
        typeBool == 0;
        if (fullQuery.find('[') != -1){
            queryTypeNum = 4;
              int i = fullQuery.find('[');
              int j = fullQuery.find(']');
              multiWords.push_back(fullQuery.substr(i + 1, j-1));
              fullQuery.erase(i, j);
        }
        if(fullQuery.length() > 2){
            queryTypeNum = 4;
            istringstream f(fullQuery);
            string temp;
            f >>  temp;
            singleWords.push_back(temp);
        }
    }
    totalWords = singleWords.size() + multiWords.size() + singleNotWords.size() + multiNotWords.size();
    totalMultiWords = multiWords.size() + multiNotWords.size();
    for(int j = 0; j < multiWords.size(); j++){
        multiWord(multiWords.at(j), 0, typeBool);
    }
    for(int i = 0; i < singleWords.size(); i++){
        singleQuery(singleWords.at(i), 0, typeBool);
    }
    for(int k = 0; k < multiNotWords.size(); k++){
        multiWord(multiNotWords.at(k), 1,typeBool );
    }
    for(int i = 0; i < singleNotWords.size(); i++){
        singleQuery(singleNotWords.at(i), 1, typeBool);
    }

    answer_query();
}
void QueryProcessor::answer_query()
{ 
//    if(queryTypeNum == 0){
//        andQuery(0);
//    }
//    else if(queryTypeNum == 1){
//        notQuery(queryTypeNum);
//    }
//    else if(queryTypeNum == 2){
//        orQuery(0);
//    }
//    else if(queryTypeNum == 3){
//        notQuery(queryTypeNum);
//    }
//    else if(queryTypeNum == 4){
//        singleQuery();
//    }
//    else if(queryTypeNum == 5){
//        notQuery(queryTypeNum);
//    }

    sort_results();
    display_best_fifteen_results();


}


//void QueryProcessor::andQuery(int type){
//    string currWord;
//    Term* foundTerm;


//    //  No single words "and" with multi-word

//        if(singleWords.size() == 0 && multiWords.size() != 0){
//            for(int i = 0; i < multiWords.size(); i++){
//                  multiAndWordQuery(currWord =  multiWords.at(i), type);

//            }


//       }
//        //  Single words && no multi-words

//        else if(singleWords.size()!= 0 &&  multiWords.size() == 0){

//            //  Loop thru all the single words
//            //  Stores in currWord
//            //  Cleans up each word in Porter2Stemmer
//            //  Finds them in index ...  stores pointer in foundterm
//            //  If foundterm == NULL, no words appeared

//            for(int i = 0; i < singleWords.size(); i ++){
//              currWord =  singleWords.at(i);
//              Porter2Stemmer::stem(currWord);
//              foundTerm = index.find_term(currWord);
//              if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//              else
//              {
//                  foundTerm->init_tdidfs(index);
//                  init_relev_map(foundTerm);
//              }
//            }
//        }else{
//            for(int i = 0; i < multiWords.size(); i++){
//                multiAndWordQuery(currWord =  multiWords.at(i), type);
//            }
//            singleQuery();
//            for(int i = 0; i < singleWords.size(); i ++){
//              currWord =  singleWords.at(i);
//              Porter2Stemmer::stem(currWord);
//              foundTerm = index.find_term(currWord);
//              if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//              else
//              {
//                  foundTerm->init_tdidfs(index);
//                  intersection_incr_relev_map(foundTerm);
//              }
//            }


//        }
//        int pageID;
//        vector<PageInfo*> pageIDs = index.getPages();


//}

//void QueryProcessor::orQuery(int type){
//    string currWord;
//    Term* foundTerm;
//    if(singleWords.size() == 0 && multiWords.size() != 0){
//        for(int i = 0; i < multiWords.size(); i++){
//            //multiOrWordQuery(currWord =  multiWords.at(i), type);
//        }
//    }
//    else if(singleWords.size()!= 0 &&  multiWords.size() == 0){
//        for(int i = 0; i < singleWords.size(); i ++){
//          currWord =  singleWords.at(i);
//          Porter2Stemmer::stem(currWord);
//          foundTerm = index.find_term(currWord);
//          if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//          else
//          {
//              foundTerm->init_tdidfs(index);
//              init_relev_map(foundTerm);
//          }
//        }
//    }else{

//        for(int i = 0; i < multiWords.size(); i++){
//            //multiOrWordQuery(currWord =  multiWords.at(i), type);

//        }
//        for(int i = 0; i < singleWords.size(); i ++){
//            currWord =  singleWords.at(i);
//            Porter2Stemmer::stem(currWord);
//            foundTerm = index.find_term(currWord);
//            if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//            else
//            {
//                foundTerm->init_tdidfs(index);
//                union_incr_relev_map(foundTerm);
//            }
//        }
//    }
//}

////  notQuery

//void QueryProcessor::notQuery(int type){
//    string currWord;
//    Term* foundTerm;
//    if(type == 1){
//        andQuery(0);
//        //code for erase
//    }else if(type == 3){
//        orQuery(0);
//        //code for erase
//    }else if(type == 5){
//        singleQuery();

//    }


//        //  No single words "and" with multi-word

//        if(singleNotWords.size() == 0 && multiNotWords.size() != 0){
//            for(int i = 0; i < multiNotWords.size(); i++){
//                multiAndWordQuery(currWord =  multiNotWords.at(i), 1);
//            }


//        }
//        //  Single words && no multi-words

//        else if(singleNotWords.size()!= 0 &&  multiNotWords.size() == 0){

//            //  Loop thru all the single words
//            //  Stores in currWord
//            //  Cleans up each word in Porter2Stemmer
//            //  Finds them in index ...  stores pointer in foundterm
//            //  If foundterm == NULL, no words appeared

//            for(int i = 0; i < singleNotWords.size(); i ++){
//                currWord =  singleNotWords.at(i);
//                Porter2Stemmer::stem(currWord);
//                foundTerm = index.find_term(currWord);
//                if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//                else
//                {
//                    foundTerm->init_tdidfs(index);
//                    init_relev_map(foundTerm);
//                    for (auto& page : foundTerm->get_pageAprns()){
//                        try
//                        {
//                            results.at(page.first);
//                        }
//                        catch (const out_of_range& notInResults)
//                        {
//                            continue;
//                        }
//                        // If it is in results, remove that entry.
//                        results.erase(page.first);
//                    }
//                }

//            }
//        }else{
//            for(int i = 0; i < multiNotWords.size(); i++){
//                multiAndWordQuery(currWord =  multiNotWords.at(i), 1);
//            }
//            for(int i = 0; i < singleNotWords.size(); i ++){
//                currWord =  singleNotWords.at(i);
//                Porter2Stemmer::stem(currWord);
//                foundTerm = index.find_term(currWord);
//                if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//                else
//                {
//                    foundTerm->init_tdidfs(index);
//                    intersection_incr_relev_map(foundTerm);

//                    for (auto& page : foundTerm->get_pageAprns()){
//                        try
//                        {
//                            results.at(page.first);
//                        }
//                        catch (const out_of_range& notInResults)
//                        {
//                            continue;
//                        }
//                        // If it is in results, remove that entry.
//                        results.erase(page.first);
//                    }
//                }

//            }




//            currWord =  singleNotWords.at(0);
//            Porter2Stemmer::stem(currWord);
//            foundTerm = index.find_term(currWord);
//            if (!foundTerm) cout<<"The term \""<< currWord <<"\" never appeared in the corpus\n";
//            else
//            {
//                foundTerm->init_tdidfs(index);
//                init_relev_map(foundTerm);
//                for (auto& page : foundTerm->get_pageAprns()){
//                    try
//                    {
//                        results.at(page.first);
//                    }
//                    catch (const out_of_range& notInResults)
//                    {
//                        continue;
//                    }
//                    // If it is in results, remove that entry.
//                    results.erase(page.first);
//                }
//            }
//        }

//}

void QueryProcessor::singleQuery(string word, int typeNot, int typeBool){
    Term* foundTerm;
    if(results.size() != 0){
        if(typeNot == 0){
            if(typeBool == 0){
                Porter2Stemmer::stem(word);
                foundTerm = index.find_term(word);
                if (!foundTerm) cout<<"The term \""<< word <<"\" never appeared in the corpus\n";
                else
                {
                   foundTerm->init_tdidfs(index);
                   intersection_incr_relev_map(foundTerm);
                }
            }else if(typeBool == 1){
                Porter2Stemmer::stem(word);
                foundTerm = index.find_term(word);
                if (!foundTerm) cout<<"The term \""<< word <<"\" never appeared in the corpus\n";
                else
                {
                   foundTerm->init_tdidfs(index);
                   union_incr_relev_map(foundTerm);
                }
            }
        }else if(typeNot ==1){
            if(typeBool == 0){
                Porter2Stemmer::stem(word);
                foundTerm = index.find_term(word);
                if (!foundTerm) cout<<"The term \""<< word <<"\" never appeared in the corpus\n";
                else
                {
                   foundTerm->init_tdidfs(index);
                   for(auto& page : foundTerm->get_pageAprns()){
                       try{
                           results.at(page.first);
                       }
                       catch(const out_of_range& notInResults){
                           continue;
                       }
                       results.erase(page.first);
                   }
                }
            }else if(typeBool == 1){
                Porter2Stemmer::stem(word);
                foundTerm = index.find_term(word);
                if (!foundTerm) cout<<"The term \""<< word <<"\" never appeared in the corpus\n";
                else
                {
                   foundTerm->init_tdidfs(index);
                   union_incr_relev_map(foundTerm);
                }
            }
        }
    }
    else{

        Porter2Stemmer::stem(word);
        foundTerm = index.find_term(word);
        if (!foundTerm) cout<<"The term \""<< word <<"\" never appeared in the corpus\n";
        else
        {
            foundTerm->init_tdidfs(index);
            init_relev_map(foundTerm);
        }

    }
}


void QueryProcessor::multiWord(string multi,  int typeNot, int typeBool){
    Term* foundTerm;
    Term* foundTerm2;
    string word1, word2;
    int j;
    double tdidf;
    int multPageID;
    j = multi.find(' ');
    word1= multi.substr(0,j);
    word2=multi.substr(j+1);
    vector<PageInfo*> pageIDs = index.getPages();
    int pageID;
    PageInfo* resultInfo;

    Porter2Stemmer::stem(word1);
    foundTerm = index.find_term(word1);

    Porter2Stemmer::stem(word2);
    foundTerm2 = index.find_term(word2);

    if(typeNot == 0){
        if(typeBool == 0){

            if (!foundTerm){

                cout<<"The term \""<< word1 <<"\" never appeared in the corpus\n";

            }else if (!foundTerm2){

                cout<<"The term \""<< word2 <<"\" never appeared in the corpus\n";

            }
            else{
                foundTerm->init_tdidfs(index);
                foundTerm2->init_tdidfs(index);
                for (auto & page : foundTerm->get_pageAprns())
                {
                    try{
                       page.first;
                    }
                    catch( const out_of_range& notInResults){
                        continue;
                    }
                    regularResults.emplace(make_pair(page.first, foundTerm->get_tdidf_for_page(page.first)));


                }
                relevancyMap intersection;

                for (auto& page : foundTerm2->get_pageAprns())
                {
                    // See if the pageID is in results.
                    try
                    {
                        regularResults.at(page.first);
                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is, add the two TD/IDF values together and emplace the
                    // new value in the intersection relevancyMap.
                    tdidf = regularResults.at(page.first);
                    tdidf += index.calc_tdidf(page.first, page.second, foundTerm2->get_spread());
                    intersection.emplace(make_pair(page.first, tdidf));
                }
                regularResults = intersection;

                for(auto& x: regularResults) {
                    try{
                        pageID = x.first;
                    //    tdidf = x.second;
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    resultInfo = pageIDs.at(pageID);
                    stringstream _found_stream;
                     _found_stream << NULL;
                     string _output;
                    _found_stream << pageIDs.at(pageID)->get_content();
                    _output = _found_stream.str();
                    if (_output.find(multi) == -1)
                    {
                        cout<< "not found" << endl;
                        regularResults.erase(pageID);
                    }
                }
                for (auto& a : regularResults)
                {
                    // See if the pageID is in results.
                    try
                    {
                        results.at(a.first);

                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        results = regularResults;
                        continue;
                    }

                    regularResults.emplace(make_pair(a.first, a.second));
                }

                results = regularResults;

            }
        }else if(typeBool == 1){

            if (!foundTerm){

                cout<<"The term \""<< word1 <<"\" never appeared in the corpus\n";

            }else if (!foundTerm2){

                cout<<"The term \""<< word2 <<"\" never appeared in the corpus\n";

            }
            else{
                foundTerm->init_tdidfs(index);
                foundTerm2->init_tdidfs(index);
                for (auto & page : foundTerm->get_pageAprns())
                {
                    try{
                       page.first;
                    }
                    catch( const out_of_range& notInResults){
                        continue;
                    }
                    regularResults.emplace(make_pair(page.first, foundTerm->get_tdidf_for_page(page.first)));


                }
                relevancyMap intersection;

                for (auto& page : foundTerm2->get_pageAprns())
                {
                    // See if the pageID is in results.
                    try
                    {
                        regularResults.at(page.first);
                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is, add the two TD/IDF values together and emplace the
                    // new value in the intersection relevancyMap.
                    tdidf = regularResults.at(page.first);
                    tdidf += index.calc_tdidf(page.first, page.second, foundTerm2->get_spread());
                    intersection.emplace(make_pair(page.first, tdidf));
                }
                regularResults = intersection;
                orMultiResults = regularResults;
                for(auto& x: regularResults){
                    try{
                        pageID = x.first;
                    //    tdidf = x.second;
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    resultInfo = pageIDs.at(pageID);
                    stringstream _found_stream;
                     _found_stream << NULL;
                     string _output;
                    _found_stream << pageIDs.at(pageID)->get_content();
                    _output = _found_stream.str();
                    if (_output.find(multi) == -1)
                    {
                        cout<< "not found" << endl;
                        regularResults.erase(pageID);
                    }
                }
                for(auto&x: regularResults){
                    try{
                        pageID = x.first;

                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    for(auto&x: orMultiResults){
                        try{
                            multPageID = x.first;
                            tdidf = x.second;
                        }
                        catch (const out_of_range& notInResults)
                        {
                            continue;
                        }
                        if(pageID != multPageID){
                            regularResults.emplace(make_pair(multPageID, tdidf));
                        }

                    }
                }
                for (auto& a : regularResults)
                {
                    // See if the pageID is in results.
                    try
                    {
                        results.at(a.first);

                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        results.emplace(make_pair(a.first, a.second));
                        continue;
                    }


                    results.at(a.first)+= a.second;
                }

                results = regularResults;
                displayResults();
        }

        }
    }if(typeNot == 1){
        if(typeBool == 0){

            if (!foundTerm){

                cout<<"The term \""<< word1 <<"\" never appeared in the corpus\n";

            }else if (!foundTerm2){

                cout<<"The term \""<< word2 <<"\" never appeared in the corpus\n";

            }
            else{
                foundTerm->init_tdidfs(index);
                foundTerm2->init_tdidfs(index);
                for (auto & page : foundTerm->get_pageAprns())
                {
                    try{
                       page.first;
                    }
                    catch( const out_of_range& notInResults){
                        continue;
                    }
                    regularResults.emplace(make_pair(page.first, foundTerm->get_tdidf_for_page(page.first)));


                }
                relevancyMap intersection;

                for (auto& page : foundTerm2->get_pageAprns())
                {
                    // See if the pageID is in results.
                    try
                    {
                        regularResults.at(page.first);
                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is, add the two TD/IDF values together and emplace the
                    // new value in the intersection relevancyMap.
                    tdidf = regularResults.at(page.first);
                    tdidf += index.calc_tdidf(page.first, page.second, foundTerm2->get_spread());
                    intersection.emplace(make_pair(page.first, tdidf));
                }
                regularResults = intersection;

                for(auto& x: regularResults) {
                    try{
                        pageID = x.first;
                    //    tdidf = x.second;
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    resultInfo = pageIDs.at(pageID);
                    stringstream _found_stream;
                     _found_stream << NULL;
                     string _output;
                    _found_stream << pageIDs.at(pageID)->get_content();
                    _output = _found_stream.str();
                    if (_output.find(multi) != -1)
                    {
                        cout<< "not found" << endl;
                        regularResults.erase(pageID);
                    }
                }
                for (auto& a : regularResults)
                {
                    // See if the pageID is in results.
                    try
                    {
                        results.at(a.first);

                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        results = regularResults;
                        continue;
                    }

                    regularResults.emplace(make_pair(a.first, a.second));
                }

                results = regularResults;

            }
        }else if(typeBool == 1){

            if (!foundTerm){

                cout<<"The term \""<< word1 <<"\" never appeared in the corpus\n";

            }else if (!foundTerm2){

                cout<<"The term \""<< word2 <<"\" never appeared in the corpus\n";

            }
            else{
                foundTerm->init_tdidfs(index);
                foundTerm2->init_tdidfs(index);
                for (auto & page : foundTerm->get_pageAprns())
                {
                    try{
                       page.first;
                    }
                    catch( const out_of_range& notInResults){
                        continue;
                    }
                    regularResults.emplace(make_pair(page.first, foundTerm->get_tdidf_for_page(page.first)));


                }
                relevancyMap intersection;

                for (auto& page : foundTerm2->get_pageAprns())
                {
                    // See if the pageID is in results.
                    try
                    {
                        regularResults.at(page.first);
                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    // If it is, add the two TD/IDF values together and emplace the
                    // new value in the intersection relevancyMap.
                    tdidf = regularResults.at(page.first);
                    tdidf += index.calc_tdidf(page.first, page.second, foundTerm2->get_spread());
                    intersection.emplace(make_pair(page.first, tdidf));
                }
                regularResults = intersection;
                orMultiResults = regularResults;
                for(auto& x: regularResults){
                    try{
                        pageID = x.first;
                    //    tdidf = x.second;
                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    resultInfo = pageIDs.at(pageID);
                    stringstream _found_stream;
                     _found_stream << NULL;
                     string _output;
                    _found_stream << pageIDs.at(pageID)->get_content();
                    _output = _found_stream.str();
                    if (_output.find(multi) != -1)
                    {
                        cout<< "not found" << endl;
                        regularResults.erase(pageID);
                    }
                }
                for(auto&x: regularResults){
                    try{
                        pageID = x.first;

                    }
                    catch (const out_of_range& notInResults)
                    {
                        continue;
                    }
                    for(auto&x: orMultiResults){
                        try{
                            multPageID = x.first;
                            tdidf = x.second;
                        }
                        catch (const out_of_range& notInResults)
                        {
                            continue;
                        }
                        if(pageID != multPageID){
                            regularResults.emplace(make_pair(multPageID, tdidf));
                        }

                    }
                }
                for (auto& a : regularResults)
                {
                    // See if the pageID is in results.
                    try
                    {
                        results.at(a.first);

                    }
                    // If not, skip this page.
                    catch (const out_of_range& notInResults)
                    {
                        results.emplace(make_pair(a.first, a.second));
                        continue;
                    }


                    results.at(a.first)+= a.second;
                }

                results = regularResults;

        }

        }
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

void QueryProcessor::sort_results()
{
    // To find the top results, some
    relevancyMap resultsToSort = results;
    int number_to_sort;

 /*   if (multi_word)
        number_to_sort = 10,000;
    else */
        number_to_sort = 16;


    while (resultsToSort.size() != 0 && ((sortedResults.size() < number_to_sort)))
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
void QueryProcessor::displayResults(){
    int pageID;
    vector<PageInfo*> pageIDs = index.getPages();
    for(auto& x: results){
        try{
            pageID = x.first;

        }
        catch (const out_of_range& notInResults){
            continue;
        }
        cout << "Winning" << endl;
        cout << pageIDs.at(pageID)->get_content() << endl;

    }
}

