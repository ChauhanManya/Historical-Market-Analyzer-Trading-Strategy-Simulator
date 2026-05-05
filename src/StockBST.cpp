// A BST that indexes stocks by a double key (annual return % or volatility). Must contain:

#include <iostream>
#include <stdexcept>
#include "StockBST.h"
using namespace std;

StockBST::BSTNode* StockBST::insertHelper(BSTNode* node, const string& ticker, double key, int year){
    StockBST::BSTNode addNode(ticker, key, year);
}
StockBST::BSTNode* StockBST::searchHelper(StockBST::BSTNode* node, double key) const {
    if (node == nullptr)
        return nullptr;
    if (key == node->key)
        return node;
    else if (key < node->key)
        return searchHelper(key, node->left);
    else
        return searchHelper(key, node->right);
}
void rangesearchHelper(StockBST::BSTNode* node, double low, double high, vector<StockBST::BSTNode*>& results) const;
void inorderHelper(StockBST::BSTNode* node)  const{ //left -> root -> right
    if(!node) return;
    cout << "Node:  " << node->key;
    inorderHelper(node->left);
    cout << "Node:  " << node->key;
    inorderHelper(node->right);
}
void preorderHelper(StockBST::BSTNode* node) const{ //root -> left -> right
    if(!node) return;
    cout << "Node:  " << node->key;
    preorderHelper(node->left);
    preorderHelper(node->right);
}
void postorderHelper(StockBST::BSTNode* node) const{//left -> right -> root
        if(!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << "Node:  " << node->key;
}
int  heightHelper(StockBST::BSTNode* node)   const{
    
}
void clearHelper(StockBST::BSTNode* node){
    if(!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
    
StockBST::StockBST(){
    root = nullptr;
}

StockBST::BSTNode* search(double key) const {// Return pointer to a node whose key exactly matches. nullptr if not found.
    return searchHelper(key, root);
}
void StockBST::insert(const string& ticker, double key, int year = 0);{
        if (!search(key)) //if search returns nullptr the node already exists add to right subtree
            inserthelper(addNode); //insert 
}

// Collect all nodes where low <= key <= high into 'results' vector.
void rangeSearch(double low, double high, vector<BSTNode*>& results) const{}

// Tree traversals — each prints: ticker (key) per line
// sorted ascending by key
void inorder()   const{
    inorderHelper(root);
}  
void preorder()  const{
    preorderHelper(root);
}
void postorder() const{
    postorderHelper(root);
}

// Returns the number of edges on the longest root-to-leaf path. -1 if empty.
int getHeight() const{
        if (root == nullptr) {
        return -1;
    }
    
    int leftHeight = heightHelper(root->left);
    int rightHeight = heightHelper(root->right);
    
    return leftHeight > rightHeight ?leftHeight +1 : rightHeight +1 ;
}

// Finds and returns the node with the maximum key (rightmost node).
// Returns nullptr if tree is empty.
StockBST::BSTNode* findMax() const{
    if(!root) return nullptr;
    StockBST::BSTNode* curr = findMax(root->right);
    return curr;
}

// Frees all nodes. Resets root to nullptr.
void clear(){
    if (root) 
        clearHelper(root);
}



