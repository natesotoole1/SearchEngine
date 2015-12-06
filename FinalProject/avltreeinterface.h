#ifndef AVLTREEINTERFACE_H
#define AVLTREEINTERFACE_H

#include "indexhandler.h"
#include "indexinterface.h"
#include "avltreeindex.h"
#include "term.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
// typedef unordered_map<int, int> pageMap;
typedef _map<int, int> pageMap;
/*! \brief
 * AVL Tree Interface implements 26 different AVLTreeIndex's.
 */
class AVLTreeInterface : public IndexInterface ///< inherits virtual functions from IndexInterface
{
public:
    AVLTreeInterface();///< constructor
    ~AVLTreeInterface();///< destructor
    
    void add_term_to_ii(int letterIndex, Term* term);///< adds term to the each individual avlTrees
    void clear(); ///< clears avlTrees
    Term* find_term(string term);///<searches each avlTrees for word and than returns term
    void write_persistence_files(); ///< creates the persistance index

private:
    AVLTreeIndex* avlTrees; ///< creates 26 AVLTreeIndex's
    const int numLetters = 26; ///< amount of AVL Trees
};

#endif // AVLTREEINTERFACE_H
