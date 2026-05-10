#include <iostream>
#include <vector>
#include "Portfolio.h"
using namespace std;

Portfolio::Portfolio(const string& ownerName, double initialCash): ownerName(ownerName), cashBalance(initialCash) {};

void Portfolio::buyShares(const string& ticker, int shares, double price, const string& date){
    if (cashBalance  < price* shares){
        cout << "cash Balance too low for this transaction" << endl;
        return;
    }

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
    }while( i< holdings.size() && !found);
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
    if(o.side == "SELL"){
        if(o.type == "LIMIT" && currentPrice >= o.targetPrice)
            sellShares(o.ticker, o.shares, o.targetPrice, date);
        else if (o.type == "MARKET")
            sellShares(o.ticker, o.shares, currentPrice, date);
    }else{//BUY
        if(o.type == "LIMIT" && currentPrice <= o.targetPrice)
            buyShares(o.ticker, o.shares, o.targetPrice, date);
        else if(o.type == "MARKET")
            buyShares(o.ticker, o.shares, currentPrice, date);
    }
}
double Portfolio::getTotalMarketValue() const{
    int i = 0;
    double sum = 0;
    do{
        sum += holdings[i].currentPrice * holdings[i].shares;
        i++;
    }while( i < holdings.size());
    return sum;
}

double Portfolio::getTotalValue() const{
    return getTotalMarketValue() + cashBalance;
}
double Portfolio::getTotalUnrealizedReturn() const{
    double marketValue = getTotalMarketValue() ;
    double totalCostBasis;
    int i =0, sum = 0;
    do{
        sum += holdings[i].avgCostBasis * holdings[i].shares;
        i++;
    }while( i < holdings.size());
    return 100*(marketValue - totalCostBasis)/totalCostBasis;
}
double Portfolio::getCashBalance() const{
    return cashBalance;
}
void Portfolio::updatePrice(const string& ticker, double newPrice){
    int i = 0;
    bool found = false;
    do{
        if(holdings[i].ticker == ticker){
            holdings[i].currentPrice = newPrice;
            found = true;
        }
        i++;
    }while( i < holdings.size() && !found);
}
void Portfolio::sortHoldingsByUnrealizedReturn(){
    int n = holdings.size();
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            double marketValue_j, marketValue_i, unrealizedValue_i, unrealizedValue_j, totalCostBasis_i, totalCostBasis_j  ;
            marketValue_j = holdings[j].currentPrice;
            marketValue_i = holdings[i].currentPrice;
            totalCostBasis_j = holdings[j].avgCostBasis * holdings[j].shares;
            totalCostBasis_i = holdings[i].avgCostBasis * holdings[i].shares;
            unrealizedValue_j = 100*(marketValue_j - totalCostBasis_j)/totalCostBasis_j;
            unrealizedValue_i = 100*(marketValue_i - totalCostBasis_i)/totalCostBasis_i;
            if (unrealizedValue_i < unrealizedValue_j) {
                swap(holdings[j], holdings[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
} 
void Portfolio::sortHoldingsByTicker(){
    int n = holdings.size();
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (holdings[j].ticker < holdings[j + 1].ticker) {
                swap(holdings[j], holdings[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}       
void Portfolio::printHoldings()     const{
    int i =0;
    cout << "Ticker |" << "| No. of Shares |" << " | Current Price | " << " | Avg. Cost Bases" << endl ;
    do{
       cout << holdings[i].ticker << holdings[i].shares << holdings[i].currentPrice << holdings[i].avgCostBasis << endl;
        i++;
    }while( i < holdings.size());    
}
void Portfolio::printTradeHistory() const{
    tradeHistory.printAll();
} 
void Portfolio::printPendingOrders() const{
    pendingOrders.printAll();
}