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
    index->read_file(filePath);
}

void IndexHandler::run_queries(string query)
{
    QueryProcessor processor = QueryProcessor(*index);
    processor.initiate_query(query);
}
void IndexHandler::clear_index(){
    index->clear();
    delete index;
}
