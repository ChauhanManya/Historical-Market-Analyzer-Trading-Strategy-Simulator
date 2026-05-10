#include <iostream>
#include "TradingStrategy.h";
#include <math.h>
using namespace std;

void TradingStrategy::printResult(const SimResult& result) const{
    cout << result.strategyName << result.totalInvested << result.totalReturn << result.totalTrades <<  result.maxDrawdown << result.cagr << result.finalValue << endl;  ;
}
double TradingStrategy::calculateCAGR(double startVal, double endVal, int years) const{
    if (years <= 0 || startVal <= 0) return 0.0;
    return (pow( endVal / startVal,1.0/years ) - 1)*100;
}
double TradingStrategy::calculateMaxDrawdown(const vector<double>& portfolioValues) const{
    double max = pow(2,-53), min = pow(2,53);
    int i = 0;
    do{
        if (portfolioValues[i] > max )
            max = portfolioValues[i];
        else if (portfolioValues[i] < min )
            min = portfolioValues[i];
        i++;
    }while( i < portfolioValues.size());

    return abs(100*(max - min)/max);
}