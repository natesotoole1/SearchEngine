/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Kiko Whiteley
 **/
#include "hashtableinterface.h"

HashTableInterface::HashTableInterface()
{
    letters = new HashTableIndex[26];
}

HashTableInterface::~HashTableInterface()
{

}


void IndexInterface::write_persistence_files()
{
    // To check if we can do threading.
    for (int i=0; i<26; ++i)
    {
        cout << "Creating file: " << to_string(i) << endl;
        ofstream persistence;
        string ext = ".txt";
        string filePath = to_string(i) + ext;
        persistence.open(filePath);
        letters[i].write_hti(persistence);
        persistence.close();

    }
}

void IndexInterface::add_term_to_ii(int letterIndex, Term* term)
{
    letters[letterIndex].add_term_to_ht_index(term);
}

Term *IndexInterface::find_term(string term)
{
    return letters[index_for_letter(term.front())].find(term);
}

void IndexInterface::clear()
{
    for (int i=0; i<26; ++i)
    {
        letters[i].clear_table();
    }
    delete [] letters;
    parser.clear();
}
