#include "DynamicSIPStrategy.h"
#include "CSVParser.h"
#include "CircularQueue.h"
#include <math.h>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

DynamicSIPStrategy::DynamicSIPStrategy(double dipThreshold, double rallyThreshold, double multiplier): dipThreshold(dipThreshold), rallyThreshold(rallyThreshold), multiplier(multiplier){}

string DynamicSIPStrategy::getName() const {
    return "Dynamic SIP ";
}

SimResult DynamicSIPStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear) {
    SimResult s;
    s.strategyName = getName();
    s.totalInvested = 0.0;
    s.totalTrades = 0;

    double annualCapital = 12* monthlyCapital;
    
    CircularQueue recentPrices(365);
    
    //load 12 month data from before the start date 
    PriceNode* curr = history->getHead();
    double high = pow(2,-53), low = pow(2,53);
    while(curr){
        if(CSVParser::extractYear(curr->date) == startYear-1){
            recentPrices.enqueue(curr->close);
            if(curr->close > high) 
                high = curr->close;
            else if (curr->close < low)
                low = curr-> close;
        }
        curr = curr->next;
    }

    vector<double> portfolioValues;
    int lastMonth = 0;
    double thisMonthBudget, lastMonthBudget;
    int sharesBought;
    while (curr) {
        int year = CSVParser::extractYear(curr->date);
        int month = CSVParser::extractMonth(curr->date);

        if (year <= endYear) {
            recentPrices.enqueue(curr->close);

            if (month != lastMonth) {
                int shares;
                lastMonth = month;
                if (100*(high - curr->close) / high>= dipThreshold){ // dip -> market is on sale --buy more
                    thisMonthBudget = (annualCapital/12) * multiplier;
                    
                }else if(100*(low - curr->close)/low >= rallyThreshold){//price is too high -> buy less
                    thisMonthBudget = (annualCapital/12) * 0.5;
                }
                else {
                    thisMonthBudget = (annualCapital/12);
                }
                shares = thisMonthBudget / curr->close;
                sharesBought += shares;
                s.totalInvested += shares * curr->close;
                s.totalTrades++;
                annualCapital -= thisMonthBudget;
                s.totalTrades++;
                portfolioValues.push_back(curr->close);
            }
        }
        curr = curr->next;
    }

    s.finalValue = sharesBought * curr->close;
    s.totalReturn = ((s.finalValue - s.totalInvested)/ s.totalInvested) * 100.0;
    s.cagr = calculateCAGR(s.totalInvested, s.finalValue,endYear - startYear);
    s.maxDrawdown = calculateMaxDrawdown(portfolioValues);

    return s;
}