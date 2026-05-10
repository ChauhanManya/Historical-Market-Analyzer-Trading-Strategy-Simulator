#include "../include/ETF.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

ETF::ETF(const string& ticker,
         const string& name,
         const string& sector,
         double expenseRatio)
    : Stock(ticker, name, sector) {
    this->expenseRatio = expenseRatio;
}

ETF::~ETF() {
}

double ETF::getExpenseRatio() const {
    return expenseRatio;
}

string ETF::getType() const {
    return "ETF";
}

double ETF::calculate10YearCAGR() const {
    PriceHistory* history = getHistory();

    if (history == nullptr || history->getSize() == 0) {
        return 0;
    }

    PriceNode* first = history->getHead();
    PriceNode* last = history->getTail();

    if (first == nullptr || last == nullptr || first->close <= 0) {
        return 0;
    }

    double startPrice = first->close;
    double endPrice = last->close;

    return (pow(endPrice / startPrice, 1.0 / 10.0) - 1.0) * 100.0;
}

void ETF::printSummary() const {
    cout << fixed << setprecision(2);

    cout << "Ticker: " << ticker << endl;
    cout << "Name: " << name << endl;
    cout << "Sector: " << sector << endl;
    cout << "Type: " << getType() << endl;
    cout << "Expense Ratio: " << expenseRatio << endl;

    PriceHistory* history = getHistory();

    if (history == nullptr || history->getSize() == 0) {
        cout << "No price history loaded." << endl;
        return;
    }

    PriceNode* first = history->getHead();
    PriceNode* last = history->getTail();

    double totalReturn = 0;

    if (first != nullptr && last != nullptr && first->close != 0) {
        totalReturn = ((last->close - first->close) / first->close) * 100.0;
    }

    cout << "Date Range: " << first->date << " to " << last->date << endl;
    cout << "Trading Days: " << history->getSize() << endl;
    cout << "Total Return: " << totalReturn << "%" << endl;
    cout << "10-Year CAGR: " << calculate10YearCAGR() << "%" << endl;
}