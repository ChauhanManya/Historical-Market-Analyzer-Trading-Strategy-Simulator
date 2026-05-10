#include "../include/MomentumStrategy.h"
#include "../include/CSVParser.h"
#include <vector>

using namespace std;

MomentumStrategy::MomentumStrategy(double momentumThreshold, int lookbackDays) {
    this->momentumThreshold = momentumThreshold;
    this->lookbackDays = lookbackDays;
}

string MomentumStrategy::getName() const {
    return "Momentum";
}

SimResult MomentumStrategy::backtest(PriceHistory* history, double monthlyCapital, int startYear, int endYear) {
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

    double cash = 0;
    double shares = 0;
    double lastClose = 0;

    int lastMonth = -1;

    vector<double> trailingPrices;
    vector<double> portfolioValues;

    PriceNode* current = history->getHead();

    while (current != nullptr) {
        int year = CSVParser::extractYear(current->date);
        int month = CSVParser::extractMonth(current->date);

        if (year >= startYear && year < endYear) {
            lastClose = current->close;

            trailingPrices.push_back(current->close);

            if (month != lastMonth) {
                cash += monthlyCapital;
                result.totalInvested += monthlyCapital;

                if ((int)trailingPrices.size() >= lookbackDays) {
                    double oldPrice =
                        trailingPrices[trailingPrices.size() - lookbackDays];

                    double currentPrice = current->close;

                    double momentum =
                        ((currentPrice - oldPrice) / oldPrice) * 100.0;

                    if (momentum > momentumThreshold && cash > 0) {
                        shares += cash / currentPrice;
                        cash = 0;
                        result.totalTrades++;
                    } else if (momentum < 0 && shares > 0) {
                        cash += shares * currentPrice;
                        shares = 0;
                        result.totalTrades++;
                    }
                }

                lastMonth = month;
            }

            portfolioValues.push_back(cash + shares * current->close);
        }

        current = current->next;
    }

    result.finalValue = cash + shares * lastClose;

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