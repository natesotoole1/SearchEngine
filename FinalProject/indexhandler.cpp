/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/06/15
 * Nate O'Toole
 * Brandon McFarland
 * Ashvin Asava
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

void IndexHandler::get_queries(string query)
{
    QueryProcessor processor = QueryProcessor(*index);
    processor.initiate_query(query);
}
void IndexHandler::clear_index(){
    index->clear();
    delete index;
}
