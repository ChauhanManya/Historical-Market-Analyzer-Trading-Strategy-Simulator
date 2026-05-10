#include "FixedSIPStrategy.h"
#include "PriceHistory.h"
#include "Portfolio.h"
#include <string>
#include <iostream>
using namespace std;

FixedSIPStrategy::FixedSIPStrategy() {}

SimResult FixedSIPStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear) override{
    SimResult s;
    s.strategyName = "Fixed SIP";
    Portfolio owner("Manya", 10000);
    string date =  startYear + "-01-01" ;
    PriceNode* p = history->findByDate(date); 

    for( int i = startYear; i <= endYear ; i++){
        for( int j = 1; j <= 12 ; j++){
            string date = to_string(i) + "-" + to_string(j) + "-01";

            if (owner.getCashBalance() < monthlyCapital){
                cout << date << ": cash balance too low" << endl;
                continue;
            }
            double closePrice = p->close;
            int shares = monthlyCapital / closePrice;
            owner.buyShares("AMZN", shares, closePrice, date);
            p = p->next;
        }
        
    }
}


string FixedSIPStrategy::getName() const override{
    return "FIXED SIP";
}