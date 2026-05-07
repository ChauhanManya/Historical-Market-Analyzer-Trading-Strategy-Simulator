// Manages a user’s stock portfolio. Must contain:
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

#include <iostream>
#include <vector>
#include "Portfolio.h"
using namespace std;

Portfolio(const string& ownerName, double initialCash);
void buyShares(const string& ticker, int shares, double price, const string& date);
void sellShares(const string& ticker, int shares, double price, const string& date);
void undoLastTrade();
void queueOrder(const Order& order);
void executeNextOrder(double currentPrice, const string& date);
double getTotalMarketValue() const;
double getTotalValue() const;
double getTotalUnrealizedReturn() const;
double getCashBalance() const;
void updatePrice(const string& ticker, double newPrice);
void sortHoldingsByUnrealizedReturn();  // descending: best performer first
void sortHoldingsByTicker();            // alphabetical ascending
void printHoldings()     const;
void printTradeHistory() const;   // delegates to tradeHistory.printAll()
void printPendingOrders() const;  // delegates to pendingOrders.printAll()