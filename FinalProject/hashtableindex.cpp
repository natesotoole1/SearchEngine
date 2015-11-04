/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Kiko Whiteley
 **/
#include "hashtableindex.h"

HashTableIndex::HashTableIndex()
{
    buckets = new TermBucket[arrSize];
}

HashTableIndex::~HashTableIndex()
{

}

void HashTableIndex::add_term_to_ht_index(Term *term)
{
    // Call add_aprn for the corresponding bucket.  add_aprn will handle collisions.
    buckets[hash_key(term->get_name())].add_term_to_bucket(term);
}

Term* HashTableIndex::find(string term)
{
    return buckets[hash_key(term)].find(term);
}

int HashTableIndex::hash_key(string key)
{
    // To save overhead.
    int size = key.size();

    // To make a relatively unique key for each word, multiply the
    // ASCII value of each letter by its position divided by the size
    // of the word.  This way, "pol" hashes differently than "lop".

    // For example, "cart" will hash to
    //   (1/4)*(ASCII val of 'c')
    // + (2/4)*(ASCII val of 'a')
    // + (3/4)*(ASCII val of 'r')
    // + (4/4)*(ASCII val of 't').

    // Use doubles for all calculation quantities for accuracy's sake.

    double index = 0;
    for (int i=0; i<size; ++i)
    {
        double shrink = (double)i / (double)size;
        index += (double)key.at(i) * shrink;
    }

    // Round the index down to the nearest int.
    int intIndex = (int) index;

    // Mod the index by arrSize to make sure it is within bounds.
    intIndex = intIndex % arrSize;

    return intIndex;
}

void HashTableIndex::write_hti(ofstream &persistence)
{
    // Write all terms in the corresponding bucket.
    for (int i=0; i<1024; ++i)
    {
       buckets[i].write_term_bucket(persistence);
    }
}
void HashTableIndex::clear_table(){
    for(int i = 0; i < arrSize; i ++){
        buckets[i].clear();

    }
    delete [] buckets;
}
