// Pointer-based stack for trade history (supports undo). Must contain:
// struct TradeRecord {
// string ticker;
// string date;
// double price;
// int shares;
// string action; // "BUY" or "SELL"
// double totalCost;
// };
//  Node-based stack: struct StackNode { TradeRecord data; StackNode* next;
// };
//  void push(const TradeRecord& record)
//  TradeRecord pop()
//  TradeRecord peek() const
//  bool isEmpty() const
//  int getSize() const
//  void printAll() const — print entire trade history top to bottom
//  Destructor frees all nodes