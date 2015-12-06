/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/
#include "indexhandler.h"

IndexHandler::IndexHandler()
{

}

IndexHandler::~IndexHandler()
{

}

IndexHandler::IndexHandler(bool asHashTable)
{
    if (asHashTable) index = new HashTableInterface();
    else index = new AVLTreeInterface();
}

void IndexHandler::read_file(string filePath)
{
    cout << "Reading file: " << filePath << endl;
    index->read_file(filePath);
}

void IndexHandler::run_queries(string query, bool multi)
{
    QueryProcessor processor = QueryProcessor(*index, multi);
    processor.initiate_query(query);
}
void IndexHandler::clear_index(){
    index->clear();
    delete index;
}
