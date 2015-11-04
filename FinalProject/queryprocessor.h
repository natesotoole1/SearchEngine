#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "docparser.h"
#include "porter2_stemmer.h"
#include "term.h"

using namespace std;

// First = pageID; total = TD-IDF across all queried terms.
typedef pair<int, double> resultPair;

typedef unordered_map<int, double> relevancyMap;
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

    void answer_query(istringstream& query, bool intersection); ///< Start writing to "results".

    void display_best_fifteen_results(); ///< Display results in descending order of summed TD/IDF value.

    void initiate_query(string query); ///< Get input from the user.

    void init_relev_map(Term* term); ///< Fill "results" with an initial candidate set.
    void intersection_incr_relev_map(Term* term); ///< Explained in QueryProcessor.cpp.
    void union_incr_relev_map(Term* term); ///< Explained in QueryProcessor.cpp.

    void sort_results(); /// Sort results in descending order of TD/IDF value.

private:
    relevancyMap results; ///< A relevancyMap holding total TD/IDF values for pageIDs regarding the whole query.
    vector<resultPair> sortedResults; ///< To copy in finding the instersection

    IndexInterface& index;
};

#endif // QUERYPROCESSOR_H
