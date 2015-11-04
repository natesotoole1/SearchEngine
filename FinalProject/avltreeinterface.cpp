/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 **/
#include "avltreeinterface.h"

/*! \brief
 * AVLTreeInterface creates 26 different AVL Trees.
 */
//creates 26 avl trees
AVLTreeInterface::AVLTreeInterface()
{
    avlTrees = new AVLTreeIndex[numLetters];

}

AVLTreeInterface::~AVLTreeInterface(){
    clear();
}

//adds terms to each the avl tree of the letter index
void AVLTreeInterface::add_term_to_ii(int letterIndex, Term *term)
{
    avlTrees[letterIndex].insert(term);
}

//clears each avl tree
void AVLTreeInterface::clear()
{
    for(int i = 0; i < numLetters; i++){
        avlTrees[i].clearTree();
    }
    delete [] avlTrees;
    parser.clear();
}
//searches for terms
Term *AVLTreeInterface::find_term(string w)
{
    int letterIndex = index_for_letter(w.front());
    return avlTrees[letterIndex].find(w);
}
//creates persistence
void AVLTreeInterface::write_persistence_files()
{
    for (int i=0; i<26; ++i)
    {
        ofstream persistence;
        string ext = ".txt";
        string filePath = to_string(i) + ext;
        persistence.open(filePath);
        avlTrees[i].createPersistence(0, persistence);
        persistence.close();
    }
}


