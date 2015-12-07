#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
// #include <unordered_map>
#include "mapping.h"
#include <utility>
#include <vector>

#include "docparser.h"
#include "porter2_stemmer.h"
#include "term.h"
#include "runquery.h"

using namespace std;

// First = pageID; total = TD-IDF across all queried terms.
typedef pair<int, double> resultPair;

// typedef unordered_map<int, double> relevancyMap;
typedef _map<int, double> relevancyMap;

/*! \brief
 * Holds a relevancyMap (unordered_map_map<int, double>) that stores the total TD/IDF values
 * that a pageID has for the current query.  Keywords AND and OR will find the intersection and
 * union of potential results, respectively.  Control is passed to IndexInterface to print the PageInfo
 * for the best 15 (or less) results.
 */
class QueryProcessor
{
public:
    //QueryProcessor();
    ~QueryProcessor();
    QueryProcessor(IndexInterface &theIndex);

    void initiate_query(string query); ///< Get input from the user.
    void answer_query(); ///< Start writing to "results".
    void andQuery(int type);
    void orQuery(int type);
    void notQuery(int type);
    void singleQuery(string, int, int);
    void init_relev_map(Term* term); ///< Fill "results" with an initial candidate set.
    void intersection_incr_relev_map(Term* term); ///< Explained in RunQuery.cpp.
    void union_incr_relev_map(Term* term); ///< Explained in RunQuery.cpp.
    void sort_results(); /// Sort results in descending order of TD/IDF value.
    void display_only_multi_word(string search_string);
    void display_best_fifteen_results(); ///< Display results in descending order of summed TD/IDF value.
    void multiAndWordQuery(string, int type);
    //void multiOrWordQuery(string);
    void multiWord(string, int, int);
    void displayResults();





private:
    relevancyMap results; ///< A relevancyMap holding total TD/IDF values for pageIDs regarding the whole query.
    vector<resultPair> sortedResults; ///< To copy in finding the instersection
    relevancyMap regularResults;
    relevancyMap notResults;
    relevancyMap orMultiResults;
    IndexInterface& index;
    //bool multiWord;
    int totalWords;
    int totalMultiWords;
    vector<string> multiWords;
    vector<string> singleWords;
    vector<string> multiNotWords;
    vector<string> singleNotWords;
    int queryTypeNum = -1;
};

#endif // QUERYPROCESSOR_H
