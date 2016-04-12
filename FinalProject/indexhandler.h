#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "avltreeinterface.h"
#include "hashtableindex.h"
#include "hashtableinterface.h"
#include "indexinterface.h"
#include "queryprocessor.h"

#include <vector>

using namespace std;
/*! \brief
 * Connects Interface and IndexInterface.  Will construct either a HashTableIndex
 * or AVLTreeIndex and mediate between user commands and stored info.
 */
class IndexHandler
{
public:
    IndexHandler();
    ~IndexHandler();
    IndexHandler(bool asHashTable); ///< Lets the user choose between data structures.

    void read_file(string filePath); ///< Reads info for a given filePath.

    void get_queries(string query); ///< Call run_queries in IndexInterface.

    void clear_index(); ///< Deallocate data members.

private:
    IndexInterface* index; /// The inverted file index.
};

#endif // INDEXHANDLER_H
