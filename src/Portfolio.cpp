#include <iostream>
#include <vector>
#include "Portfolio.h"
using namespace std;

Portfolio::Portfolio(const string& ownerName, double initialCash): ownerName(ownerName), cashBalance(initialCash) {};

void Portfolio::buyShares(const string& ticker, int shares, double price, const string& date){
    TradeRecord t;
    t.ticker = ticker;
    t.price = price; //price per share
    t.date = date;
    t.shares = shares;
    t.action = "BUY";
    t.totalCost = price * shares;
    tradeHistory.push(t);

    cashBalance -= price* shares;

    bool found = false;
    int i = 0;

    do
    {
        if (holdings[i].ticker == ticker)
        {
            // weighted average cost basis
            double oldValue = holdings[i].shares * holdings[i].avgCostBasis;
            double newValue = shares * price;
            holdings[i].shares += shares;
            holdings[i].avgCostBasis = (oldValue + newValue) / holdings[i].shares;
            holdings[i].currentPrice = price;
            found = true;
        }
        i++;
    } while (i < holdings.size() && !found);
    if(!found){
        Position p; 
        p.ticker = ticker;
        p.currentPrice = price;
        p.shares =shares;
        p.avgCostBasis = price;
        holdings.push_back(p);
    }
}

void Portfolio::sellShares(const string& ticker, int shares, double price, const string& date){
    int i=0;
    bool found = false;
    do{
        if(holdings[i].ticker == ticker){
            found = true;
            TradeRecord t;
            t.action = "SELL";
            t.date = date;
            t.price = price;
            t.shares = shares;
            t.ticker = ticker;
            t.totalCost = price * shares;
            cashBalance += price*shares;
        }
        i++;
    }while( i< holdings.size() && !found)
}
void Portfolio::undoLastTrade(){
    TradeRecord r = tradeHistory.pop();
    if(r.action == "SELL"){
        buyShares(r.ticker, r.shares, r.price, r.date);
    }else{
        sellShares(r.ticker, r.shares, r.price, r.date);
    }
}
void Portfolio::queueOrder(const Order& order){
    pendingOrders.enqueue(order);
}
void Portfolio::executeNextOrder(double currentPrice, const string& date){
    Order o = pendingOrders.dequeue();
    
}
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