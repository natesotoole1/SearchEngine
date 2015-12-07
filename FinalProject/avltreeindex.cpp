/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/06/15
 * Nate O'Toole
 * Brandon McFarland
 * Ashvin Asava
 **/


#include "AVLTreeIndex.h"

AVLTreeIndex::AVLTreeIndex(){
    root = NULL;
    
}
//passes term and than root to private insert()
void AVLTreeIndex::insert(Term* value){
    insert(root, value);
}

// Balancing AVL Tree
AVL_Node* AVLTreeIndex::balance(AVL_Node*& temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0){ //if left node height difference is greater than 0 rotate left
            temp = rotateLeftChild (temp);
        }else{ //else rotate left
            temp = doubleLeftChild (temp);
        }
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0){ //if right node height difference is greater than 0 rotate left
            temp = doubleRightChild (temp);
        }else{
            temp = rotateRightChild (temp);
        }
    }
    return temp;
    
}

// Height Difference
int AVLTreeIndex::diff(AVL_Node*& temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}

//returns height
int AVLTreeIndex::height(AVL_Node*& temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

//returns the max height
int AVLTreeIndex::max(int value1, int value2){
    return ((value1 > value2) ? value1:value2);
}


// Right- Right Rotation
AVL_Node* AVLTreeIndex::rotateRightChild(AVL_Node*& parent){
    AVL_Node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Left- Left Rotation
AVL_Node* AVLTreeIndex::rotateLeftChild(AVL_Node *& parent){
    AVL_Node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

// Left - Right Rotation
AVL_Node* AVLTreeIndex::doubleLeftChild(AVL_Node *&parent){
    parent->left = rotateRightChild(parent->left);
    return rotateLeftChild (parent);
}

// Right- Left Rotation
AVL_Node* AVLTreeIndex::doubleRightChild(AVL_Node *&parent){
    parent->right = rotateLeftChild (parent->right);
    return rotateRightChild (parent);
}

//searches word and returns the term when word is found
Term* AVLTreeIndex::find (string word){
    AVL_Node* foundNode = root;
    string word2 = root->data->get_name();
    if ((word < word2) && (root->left)){
        foundNode = foundNode->left;
        continue_search(foundNode, word);
    }else if((word > word2) && (root->right)){
        foundNode = foundNode->right;
        continue_search(foundNode, word);
    }else if(word == word2){
        return foundNode->data;
    }
    if (foundNode) return foundNode->data;
    return NULL;
}


//passes the root, level and persistence to the private function createPersistence()
void AVLTreeIndex::createPersistence(int level, ofstream &persistence)
{
    createPersistence(root, level, persistence);
}

void AVLTreeIndex::clearTree(){
    clearTree(root);
}

//private functions

//continues the insert of the avl
void AVLTreeIndex::insert(AVL_Node*& root, Term* value)
{
    //if root = null than it will create the new alphabetical avl tree
    if (root == NULL){
        root = new AVL_Node;
        root->left = NULL;
        root->right = NULL;
        root->data = value;
        return;
    }
    //if the roots word is greater than the word in value insert left and than balance
    else if (value->get_name() < root->data->get_name()){
        insert(root->left, value);
        root = balance(root);
    }
    //if the roots word is less than the word in value insert right and than balance
    else if (value->get_name() > root->data->get_name()){
        insert(root->right, value);
        root = balance(root);
    }
    //if the roots word is equal to the word in value than it will just return
    else if(value->get_name() == root->data->get_name() == 0 ){
        return;
    }
    //return root;

}

// creates Persistence from the AVL Tree
void AVLTreeIndex::createPersistence(AVL_Node*& ptr, int level, ofstream &persistence)
{
    if (ptr!=NULL)
    {
        createPersistence(ptr->left, level + 1, persistence);
        ptr->data->write_term(persistence);
        createPersistence(ptr->right, level + 1, persistence);

    }
}

//continues search for word
void AVLTreeIndex::continue_search(AVL_Node*& curr, string word){
    string word2 = curr->data->get_name();

    if ((word < word2) && (curr->left)){
        curr = curr->left;
        continue_search(curr, word);
    }else if((word > word2) && (curr->right)){
        curr = curr->right;
        continue_search(curr, word);
    }else if(word == word2){
        return;
    } else curr = NULL;
}

//clears tree
void AVLTreeIndex::clearTree(AVL_Node* r){
    if (r != NULL){
        clearTree(r->left);
        clearTree(r->right);
        delete r;
    }
    r = NULL;
}


