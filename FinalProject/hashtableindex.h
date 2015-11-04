#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H


#include "term.h"
#include "termbucket.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef unordered_map<int, int> pageMap;
/*! \brief
 * Holds 1024 TermBuckets.  Hashes strings to map to Term* values.
 * Handles collisions with chaining.
 */
class HashTableIndex
{
public:
    HashTableIndex();
    ~HashTableIndex();

    void add_term_to_ht_index(Term* term); ///< Call add_term_to_bucket at the hashed bucket.
    Term* find(string term); ///< Return Term* (matching the passed string) from the inverted index.  Return NULL if none is found.
    int hash_key(string key); ///< Custom hash function.  Specifics in hashtableindex.cpp.
    void write_hti(ofstream& persistence); ///< Call write_term_bucket for the hashed bucket.
    void clear_table(); ///< Deallocate data members.
private:
    const int arrSize = 1024; ///< The chosen number of buckets.
    TermBucket* buckets; ///< One bucket for each letter of the alphabet.

};

#endif // HASHTABLEINDEX_H
