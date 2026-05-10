#include "FixedSIPStrategy.h"
#include "PriceHistory.h"
#include "Portfolio.h"
#include <string>
#include <iostream>
using namespace std;

FixedSIPStrategy::FixedSIPStrategy() {}

SimResult FixedSIPStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear){
    SimResult s;
    s.strategyName = getName();
    s.totalInvested = 0.0;
    s.totalTrades = 0.0;

    vector<double> portfolioValues;

    Portfolio owner("Manya", monthlyCapital);
       
    for( int i = startYear; i <= endYear ; i++){
        for( int j = 1; j <= 12 ; j++){
            string date = to_string(i) + "-" + to_string(j) + "-01";
            PriceNode* p = history->findByDate(date);
            if (owner.getCashBalance() < monthlyCapital){
                cout << date << ": cash balance too low" << endl;
                continue;
            }

            double closePrice = p->close;
            int shares = monthlyCapital / closePrice;
            owner.buyShares("AMZN", shares, closePrice, date);
            
            portfolioValues.push_back(owner.getTotalValue());

            s.totalInvested+= monthlyCapital;
            s.totalTrades++;

        }
        
    }
    s.finalValue = owner.getTotalValue();
    s.totalReturn = 100*(s.finalValue - s.totalInvested)/s.totalInvested;
    s.maxDrawdown = calculateMaxDrawdown(portfolioValues);
    s.cagr = calculateCAGR(monthlyCapital, s.finalValue, endYear - startYear);
    return s;

}


string FixedSIPStrategy::getName() const{
    return "FIXED SIP";
}