// A BST that indexes stocks by a double key (annual return % or volatility). Must contain:
// struct BSTNode {
// string ticker;
// double key; // return % or volatility
// int year; // which year this stat is for
// BSTNode* left;
// BSTNode* right;
// };
//  void insert(const string& ticker, double key, int year)
//  BSTNode* search(double key) const — exact match
//  void rangeSearch(double low, double high, vector<BSTNode*>& results)
// const — collect all nodes where low <= key <= high
//  void inorder() const — print sorted by key
//  void preorder() const
//  void postorder() const
//  int getHeight() const — recursive
//  void clear() — frees all nodes
//  Destructor calls clear()