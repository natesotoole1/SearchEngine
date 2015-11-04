#ifndef DOCPARSER_H
#define DOCPARSER_H

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
// Apparently, including the header below creates problems.
// #include <rapidxml_iterators.hpp>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "indexinterface.h"
#include "pageinfo.h"
#include "porter2_stemmer.h"
#include "timer.h"

class IndexInterface;
class Term;

using namespace rapidxml;
using namespace std;

typedef unordered_map<int, int> pageMap;
typedef unordered_map<string, string> stopWordMap;
typedef unordered_map<string, pageMap> termMap;
/*! \brief
 * Handles the text of files, primarily that of WikiBooks.xml.
 * Uses RapidXML libraries.
 * Initiates PageInfo objects for a file and stores them to the inverted index.
 */
class DocParser
{
public:
    ~DocParser();
    DocParser(IndexInterface& theIndex); ///< Default constructor never called; must take a reference to the inverted file intdex.

    string clean_term(string term); ///< Stem the terms then makes all letters lowercase.
    void clear(); ///< Deallocate data members.

    //
    int index_for_letter(char letter); ///< Determine which AVLTreeIndex or HashTableIndex should handle the appearance. Returns  0 if the term is a number, 1 for 'a', 2 for 'b', and so forth.

    void read_page(xml_node<>* currNode, bool readText); ///< Makes a new PageInfo object from a page.  Will or will not fetch term appearances from the text after using it as a PageInfo constructor parameter.
    void read_text(xml_node<>* currNode); ///< Get all page appearances from the current page's text.  Pass this info to the inverted index.

    void init_file_page_infos(xml_node<>* currNode, bool readText); ///< Call read_page for each page.

    void read_file(string filePath); ///< Get to the right node (assuming it's the same structure as WikiBooks.xml, then call init_file_page_infos.

    bool is_stop_word(string term); ///< Checks the stopWordMap; returns true if the passed string is in stopWords.

private:
    IndexInterface& index; ///< The inverted file index.

    stopWordMap stopWords; ///< Words to effectively ignore in the inverted file index.

    string currWord;
    string currContent;
    string currContributorNameOrIP;
    string currTimestamp;
    string currTitle;
    Term* found;
};

inline int is_not_alpha(char c)
{
    return !isalpha(c);
}

#endif // DOCPARSER_H
