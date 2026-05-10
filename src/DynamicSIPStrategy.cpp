#include "DynamicSIPStrategy.h"
#include "CSVParser.h"
#include "CircularQueue.h"
#include "Portfolio.h"
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
    SimResult result;
    Portfolio owner("Manya",monthlyCapital*12 );
    result.strategyName = getName();
 
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

    //curr = history->getHead();

    while (curr) {
        int year = CSVParser::extractYear(curr->date);
        int month = CSVParser::extractMonth(curr->date);

        if (year >= startYear && year <= endYear) {
            recentPrices.enqueue(curr->close);

            if (month != lastMonth) {
                result.totalInvested += monthlyCapital;
                double average = recentPrices.getAverage();
                if ((high - curr->close) / high * 100 >= dipThreshold){ // dip
                    thisMonthBudget = monthlyCapital * multiplier;
                    if (thisMonthBudget > owner.getCashBalance()) 
                        thisMonthBudget = owner.getCashBalance();
                    owner.buyShares();
                }
               
                    shares += thisMonthBudget / curr->close;
                    cashReserve -= thisMonthBudget;
                    result.totalTrades++;
                

            }

            portfolioValues.push_back();
        }

        curr = curr->next;
    }



    result.finalValue = shares * lastClose;

    
        result.totalReturn =
            ((result.finalValue - result.totalInvested)
             / result.totalInvested) * 100.0;
    

    result.cagr = calculateCAGR(result.totalInvested,
                                result.finalValue,
                                endYear - startYear);

    result.maxDrawdown = calculateMaxDrawdown(portfolioValues);

    return result;
}