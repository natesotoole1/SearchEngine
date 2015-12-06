#ifndef TERM_H
#define TERM_H

#include <fstream>
#include <iostream>
#include <string>
// #include <unordered_map>
#include <utility>
#include <vector>
#include "mapping.cpp"
#include "indexinterface.h"

using namespace std;

// typedef unordered_map<int, int> pageMap;
// typedef unordered_map<int, double> tdidfMap;

typedef _map<int, int> pageMap;
typedef _map<int, double> tdidfMap;

class IndexInterface;
/*! \brief
 * The heart of the inverted file index.  Each Term object has a name and pageMap,
 * holding the pageIDs it's appeared on and the frequency for each page.
 */
class Term
{
public:
    Term();
    ~Term();

    Term(string theName, pageMap& theAprns); ///< The only constructor called.


    void init_spread_and_totalFreq(); ///< The only Terms that will need spread and totalFreq are result candidates.
    void init_tdidfs(IndexInterface& index); ///< Calculate TD/IDF values for each document.
    void incrm_aprn_for_pageID(int currID); ///< Increase a pageID's frequency by 1.  Handles out_of_range exceptions.

    pageMap get_pageAprns();
    string get_name();
    Term* get_next();
    int get_spread();
    int get_totalFreq();
    double get_tdidf_for_page(int pageID);

    void set_next(Term* theNext);

    void write_term(ofstream& persistence); ///< Write Term's info to the persistence index.


private:
    pageMap pageAprns; ///< Holds the IDs of pages on which it appeared.


    string name;


    Term* next; ///< For the linked list functionality of each TermBucket. Only used in HashTableIndex.


    int spread; ///< The number of unique documents on which the term has appeared.

    tdidfMap tdidfs; ///< Only calculated for result candidates.

    int totalFreq; ///< The total number of times it's appeared int the corpus.
};

#endif // TERM_H
