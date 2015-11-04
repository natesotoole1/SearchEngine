
#ifndef AVLTreeIndex_H
#define AVLTreeIndex_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "indexinterface.h"
#include "term.h"
// git
using namespace std;

/*! \brief
 * AVL Node implementation for the AVL Tree structure.
 */
// Node declaration
struct AVL_Node
{

    Term* data;///< Term pointer where all the data is held
    //struct AVL_Node root;
    
    struct AVL_Node *left; ///< left child
    struct AVL_Node *right; ///< right child
    int height; ///< height of tree
    
};

/*! \brief
 * AVLTreeIndex.h has AVL Trees public and private classes in them.
 */
// Class declaration
class AVLTreeIndex
{
public:
    AVLTreeIndex(); ///< constructor
    void insert(Term*); ///< public insert function that calls the private function
    AVL_Node* balance(AVL_Node*&); ///< figures out when to rotate child or not
    int height(AVL_Node *&); ///< returns the height of the tree
    int diff(AVL_Node *&); ///< returns the difference in height
    int max(int, int); ///< gets the max height
    AVL_Node* rotateRightChild(AVL_Node*&); ///< rotate right child
    AVL_Node* rotateLeftChild(AVL_Node*&); ///< rotate left child
    AVL_Node* doubleLeftChild(AVL_Node*&); ///< rotate left child than rotate right child
    AVL_Node* doubleRightChild(AVL_Node*&); ///< rotate right child than rotate left child

    Term* find(string); ///< public find function that is called from the interface and than passes it to private function
    void createPersistence(int, ofstream&); ///< public call to create persistence than calls the private function
    void clearTree(); ///< public call to clear index than calls the private function

private:
    AVL_Node* root; ///< root of the tree
    void insert(AVL_Node*& ,Term*); ///< inserts node if null than checks balance to see if it is needed to rotate
    void createPersistence(AVL_Node*& , int, ofstream&); ///< creates the persistence from each individual avl tree
    void continue_search(AVL_Node*& curr, string word); ///< finds word called by query
    void clearTree(AVL_Node*); /// <clear the tree
};



#endif // AVLTreeINDEX_H

