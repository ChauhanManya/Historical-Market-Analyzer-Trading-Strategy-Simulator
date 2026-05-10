#include "../include/DynamicSIPStrategy.h"
#include "../include/CSVParser.h"
#include "../include/CircularQueue.h"
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

DynamicSIPStrategy::DynamicSIPStrategy(double dipThreshold,
                                       double highMultiplier,
                                       double lowMultiplier) {
    this->dipThreshold = dipThreshold;
    this->highMultiplier = highMultiplier;
    this->lowMultiplier = lowMultiplier;
}

string DynamicSIPStrategy::getName() const {
    stringstream ss;
    ss << fixed << setprecision(1);
    ss << "Dynamic SIP Dip "
       << dipThreshold << "% "
       << highMultiplier << "x/"
       << lowMultiplier << "x";
    return ss.str();
}

SimResult DynamicSIPStrategy::backtest(PriceHistory* history,
                                       double monthlyCapital,
                                       int startYear,
                                       int endYear) {
    SimResult result;

    result.strategyName = getName();
    result.finalValue = 0;
    result.totalInvested = 0;
    result.totalReturn = 0;
    result.cagr = 0;
    result.maxDrawdown = 0;
    result.totalTrades = 0;

    if (history == nullptr || history->getSize() == 0) {
        return result;
    }

    double shares = 0;
    double cashReserve = 0;
    double lastClose = 0;
    int lastMonth = -1;

    CircularQueue recentPrices(30);
    vector<double> portfolioValues;

    PriceNode* current = history->getHead();

    while (current != nullptr) {
        int year = CSVParser::extractYear(current->date);
        int month = CSVParser::extractMonth(current->date);

        if (year >= startYear && year < endYear) {
            lastClose = current->close;
            recentPrices.enqueue(current->close);

            if (month != lastMonth) {
                cashReserve += monthlyCapital;
                result.totalInvested += monthlyCapital;

                double thisMonthBudget = monthlyCapital * lowMultiplier;
                double average = recentPrices.getAverage();

                if (recentPrices.getCount() >= 30 &&
                    current->close <= average * (1.0 - dipThreshold / 100.0)) {
                    thisMonthBudget = monthlyCapital * highMultiplier;
                }

                if (thisMonthBudget > cashReserve) {
                    thisMonthBudget = cashReserve;
                }

                if (thisMonthBudget > 0 && current->close > 0) {
                    shares += thisMonthBudget / current->close;
                    cashReserve -= thisMonthBudget;
                    result.totalTrades++;
                }

                lastMonth = month;
            }

            portfolioValues.push_back(shares * current->close + cashReserve);
        }

        current = current->next;
    }

    if (cashReserve > 0 && lastClose > 0) {
        shares += cashReserve / lastClose;
        result.totalTrades++;
        cashReserve = 0;
    }

    result.finalValue = shares * lastClose;

    if (result.totalInvested > 0) {
        result.totalReturn =
            ((result.finalValue - result.totalInvested)
             / result.totalInvested) * 100.0;
    }

    result.cagr = calculateCAGR(result.totalInvested,
                                result.finalValue,
                                endYear - startYear);

    result.maxDrawdown = calculateMaxDrawdown(portfolioValues);

    return result;
}