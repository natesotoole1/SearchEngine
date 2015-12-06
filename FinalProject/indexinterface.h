#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <math.h>
#include <pthread.h>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// #include <unordered_map>
#include "mapping.h"
#include "docparser.h"
#include "pageinfo.h"
#include "term.h"


class DocParser;
class HashTableIndex;
class Term;

typedef _map<int, int> pageMap;
typedef _map<string, pageMap> termMap;

using namespace std;
/*! \brief
 * The inverted file index.  Two derived classes, HashTableInterface and AVLTreeInterface,
 * store the inverted file index as a hash table and AVL tree, respectively.
 * Also holds totalWordsInCorpus for TD/IDF calculation.
 * All virtual functions in this header implemented in HashTableInterface.cpp.
 * AVLTreeInterface redefines said virtual functions.
 */
class IndexInterface
{
public:

    IndexInterface();
    ~IndexInterface();

    void append_page_info(PageInfo* currInfo); ///< Each time the DocParser finds info for a new page, push it back to infoForIDs.
    double calc_tdidf(int pageID, int freq, int spread); ///< Each Term has a TD/IDF value for each page.  Calculate those as doubles.
    void display_result(int rank, int pageID, double tdidf); ///< cout the top results found my QueryProcessor.
    void display_result_multi_word(int rank, int pageID, double tdidf, string multi_word);
    void display_page_content(int pageID); ///< Access infoForIDs for a pageID.  cout its title.
    void display_page_content_multi_word(int pageID, string string_search);
    void incr_total_words_on_page(int currID, int incr); /// Increase a totalWords for a pageID.
    void read_file(string filePath); ///< Pass control to the parser.
    void read_persistence_files(); ///< When the program launches or when the inverted index is cleared, read the inverted index in from the persistence files.
    void read_pers_file(int index); ///< Read a single persistence file.

    virtual void add_term_to_ii(int letterIndex, Term *term); /// Add a term to the inverted index.
    virtual void clear(); ///< Deallocate data members.

    virtual Term* find_term(string term); ///< Find the Term* in the inverted index for a string.  Retun NULL if there is no such Term*.
    virtual void write_persistence_files(); ///< Output persistence files.

    int index_for_letter(char letter); ///< Determine which AVLTreeIndex or HashTableIndex should handle the appearance. Returns  0 if the term is a number, 1 for 'a', 2 for 'b', and so forth.
    PageInfo* info_for_pageID(int pageID);

    int get_totalWordsInCorpus();
    int get_totalPages();

protected:
    const string ext = ".txt";

    // Only used for HashTableIndex.
    HashTableIndex* letters;

    // PageInfo will be passed by a pageID (int).
    vector<PageInfo*> infoForIDs;

    DocParser& parser;

    int totalPages;
    int totalWordsInCorpus;
};

#endif // INDEXINTERFACE_H
