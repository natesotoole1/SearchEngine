#ifndef RUNQUERY_H
#define RUNQUERY_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "mapping.h"
#include <utility>
#include <vector>
#include "docparser.h"
#include "porter2_stemmer.h"
#include "term.h"
#include "pageinfo.h"

using namespace std;

// First = pageID; total = TD-IDF across all queried terms.
typedef pair<int, double> resultPair;

// typedef unordered_map<int, double> relevancyMap;
typedef _map<int, double> relevancyMap;

class RunQuery{
    public:
        //RunQuery();
        ~RunQuery();
        RunQuery(IndexInterface &theIndex);

        void multiWordQuery();
        void singleWordQuery();
        void andQuery();
        void notQuery();
        void orQuery();


    private:
        relevancyMap results; ///< A relevancyMap holding total TD/IDF values for pageIDs regarding the whole query.
        vector<resultPair> sortedResults; ///< To copy in finding the instersection
        vector<PageInfo*> pageIDs;
        IndexInterface& index;
        bool multiWord;

};

#endif //RUNQUERY_H
