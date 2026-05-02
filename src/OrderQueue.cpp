// Node-based FIFO queue for pending trade orders. Must contain:
// struct Order {
// string ticker;
// string type; // "MARKET", "LIMIT"
// string side; // "BUY", "SELL"
// double targetPrice; // used for LIMIT orders; 0 for MARKET
// int shares;
// string submittedDate;
// };
//  struct QueueNode { Order data; QueueNode* next; };
//  void enqueue(const Order& order)
//  Order dequeue()
//  Order peek() const
//  bool isEmpty() const
//  int getSize() const
//  void printAll() const
//  Destructor frees all nodes