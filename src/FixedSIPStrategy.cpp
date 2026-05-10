#include "FixedSIPStrategy.h"
#include "PriceHistory.h"
#include "CSVParser.h"
#include "Portfolio.h"
#include <string>
#include <iostream>
using namespace std;



SimResult FixedSIPStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear){
    SimResult s;
    s.strategyName = getName();
    s.totalInvested = 0.0;
    s.totalTrades = 0.0;

    int totalMonths = (endYear - startYear + 1) * 12;
    Portfolio owner("Manya", totalMonths * monthlyCapital);

    vector<double> portfolioValues;
    int lastPurchaseYear  = -1;
    int lastPurchaseMonth = -1;

    PriceNode* p = history->getHead();
    while (p != nullptr) {
        int year  = CSVParser::extractYear(p->date);
        int month = extractMonth(p->date);

        if (year < startYear || year > endYear) { p = p->next; continue; }

        // First trading day of this (year, month)
        if (year != lastPurchaseYear || month != lastPurchaseMonth) {
            int shares = (int)(monthlyCapital / p->close);
            if (shares > 0) {
                owner.buyShares("AMZN", shares, p->close, p->date);
                s.totalInvested += monthlyCapital;
                s.totalTrades++;
            }
            lastPurchaseYear  = year;
            lastPurchaseMonth = month;
        }

        owner.updatePrice("AMZN", p->close);
        portfolioValues.push_back(owner.getTotalValue());

        p = p->next;
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

