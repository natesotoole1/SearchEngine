#ifndef TERMBUCKET_H
#define TERMBUCKET_H

#include "term.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// typedef unordered_map<int, int> pageMap;
typedef _map<int, int> pageMap;

/*! \brief
 * A linked list of Term*s (b/c HashTableIndex handles collisions by chanining).
 */
class TermBucket
{
public:
    TermBucket();
    ~TermBucket();

    void add_term_to_bucket(Term* term); ///< Append Term* to linked list.
    Term* find(string term); ///< Search the bucket for the Term* corresponding with a provided name.  If it doesn't exist, retrun NULL.
    bool has_word(string term);
    void write_term_bucket(ofstream& persistence); ///< For each Term in the bucket, call write_term.
    void clear();
private:
    Term* root;
};


#endif // TERMBUCKET_H
