#include "FixedSIPStrategy.h"
#include "PriceHistory.h"
#include "CSVParser.h"
#include <string>
#include <iostream>
using namespace std;

SimResult FixedSIPStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear){
    SimResult s;
    s.strategyName = getName();
    s.totalInvested = 0.0;
    s.totalTrades = 0;

    vector<double> portfolioValues;

    //go to startYear
    PriceNode* p = history->getHead();
    while( CSVParser::extractYear(p->date) != startYear)
        p = p->next;

    int lastMonth = 0;
    int sharesBought = 0;
    //find first working day of each month
    while(CSVParser::extractYear(p->date) <= endYear){
        if(CSVParser::extractMonth(p->date) != lastMonth){
            lastMonth = CSVParser::extractMonth(p->date);

            int shares = monthlyCapital / p->close ;
            sharesBought += shares;
            s.totalInvested += shares * p->close;
            s.totalTrades++;

            portfolioValues.push_back(p->close);
        }
    }
    
    s.finalValue = sharesBought * p->close;
    s.totalReturn = 100*(s.finalValue - s.totalInvested)/s.totalInvested;
    s.maxDrawdown = calculateMaxDrawdown(portfolioValues);
    s.cagr = calculateCAGR(monthlyCapital, s.finalValue, endYear - startYear);
    return s;

}


string FixedSIPStrategy::getName() const{
    return "FIXED SIP";
}

