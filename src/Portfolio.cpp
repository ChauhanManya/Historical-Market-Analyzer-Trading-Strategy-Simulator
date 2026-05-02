// Manages a user’s stock portfolio. Must contain:
// struct Position {
// string ticker;
// int shares;
// double avgCostBasis; // average purchase price
// double currentPrice; // updated when refreshed
// };
//  vector<Position> holdings (std::vector is allowed here)
//  OrderQueue pendingOrders
//  TradeStack tradeHistory
//  double cashBalance
// Methods: - void buyShares(const string& ticker, int shares, double price,
// const string& date) - void sellShares(const string& ticker, int shares, double
// price, const string& date) - void undoLastTrade() — pops TradeStack and reverses
// the transaction - void queueOrder(const Order& order) — add to OrderQueue - void
// executeNextOrder(double currentPrice) — dequeue and execute if conditions met -
// double getTotalValue() const - double getTotalReturn() const - void
// printHoldings() const - void sortHoldingsByReturn() — sort vector by unrealized
// gain/loss (use std::sort with comparator) - void sortHoldingsByTicker() — alphabetical