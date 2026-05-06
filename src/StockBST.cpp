// A BST that indexes stocks by a double key (annual return % or volatility). Must contain:

#include <iostream>
#include <stdexcept>
#include "StockBST.h"
using namespace std;
//gives address of duplicate
StockBST::BSTNode* StockBST::insertHelper(BSTNode* node, const string& ticker, double key, int year){
    if(node->key == key && node->ticker == ticker && node->year == year){
        insertHelper(node->right,ticker, key, year);
    }
    else if(node->key > key){
        if(!node->left){
            StockBST::BSTNode* addNode = new StockBST::BSTNode(ticker, key, year);
            node->left = addNode;
        }
        insertHelper(node->left, ticker, key, year);
    }
    else if(node->key < key){
        if(!node->right){//if node->right doesn't exists
            StockBST::BSTNode* addNode = new StockBST::BSTNode(ticker, key, year);
            node->right = addNode;
        }
        insertHelper(node->right, ticker, key, year);
    } 
        
}
StockBST::BSTNode* StockBST::searchHelper(BSTNode* node, double key) const {
    if (node == nullptr)
        return nullptr;
    if (key == node->key)
        return node;
    else if (key < node->key)
        searchHelper(node->left, key );
    else
        searchHelper(node->right, key);
}
void StockBST::rangeSearchHelper(BSTNode* node, double low, double high, vector<StockBST::BSTNode*>& results) const{
    if(node->key >= low&& node->key <= high){
        results.push_back(node);
    }
    rangeSearchHelper(node->left, low, high, results);
    rangeSearchHelper(node->right, low, high, results);
}
void StockBST::inorderHelper(BSTNode* node)  const{ //left -> root -> right
    if(!node) return;
    cout << "Node:  " << node->key;
    inorderHelper(node->left);
    cout << "Node:  " << node->key;
    inorderHelper(node->right);
}
void StockBST::preorderHelper(BSTNode* node) const{ //root -> left -> right
    if(!node) return;
    cout << "Node:  " << node->key;
    preorderHelper(node->left);
    preorderHelper(node->right);
}
void StockBST::postorderHelper(BSTNode* node) const{//left -> right -> root
        if(!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << "Node:  " << node->key;
}
int  StockBST::heightHelper(BSTNode* node)   const{
    int suml = 1, sumr =1;
    if(!node) return suml>sumr ? suml :  sumr;
    suml += heightHelper(node->left);
    sumr += heightHelper(node->right);

}
void StockBST::clearHelper(BSTNode* node){
    if(!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
    
StockBST::StockBST(){
    root = nullptr;
}
StockBST::BSTNode* StockBST::search(double key) const {// Return pointer to a node whose key exactly matches. nullptr if not found.
    return searchHelper(root, key);
}
void StockBST::insert(const string& ticker, double key, int year = 0){
    insertHelper(root, ticker, key, year);
}

void StockBST::rangeSearch(double low, double high, vector<BSTNode*>& results) const{// Collect all nodes where low <= key <= high into 'results' vector.
    rangeSearchHelper(root, low, high, results);
}

// Tree traversals — each prints: ticker (key) per line
// sorted ascending by key
void StockBST::inorder()   const{
    inorderHelper(root);
}  
void StockBST::preorder()  const{
    preorderHelper(root);
}
void StockBST::postorder() const{
    postorderHelper(root);
}

// Returns the number of edges on the longest root-to-leaf path. -1 if empty.
int StockBST::getHeight() const{
        if (root == nullptr) {
        return -1;
    }
    
    int leftHeight = heightHelper(root->left);
    int rightHeight = heightHelper(root->right);
    
    return leftHeight > rightHeight ?leftHeight +1 : rightHeight +1 ;
}
// Finds and returns the node with the maximum key (rightmost node).
// Returns nullptr if tree is empty.
StockBST::BSTNode* StockBST::findMax() const{
    StockBST::BSTNode* curr = root;
    while(curr->right){
        curr = curr->right;
    }
    return curr;
}

// Frees all nodes. Resets root to nullptr.
void StockBST::clear(){
    if (root) 
        clearHelper(root);
}



