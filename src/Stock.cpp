#include "../include/Stock.h"
#include "../include/CSVParser.h"
#include <iostream>
#include <iomanip>

using namespace std;

Stock::Stock(const string& ticker,
             const string& name,
             const string& sector)
    : FinancialAsset(ticker, name, sector) {
    history = nullptr;
}

Stock::~Stock() {
    delete history;
}

bool Stock::loadFromCSV(const string& filename) {
    delete history;

    history = CSVParser::loadHistory(filename);

    if (history == nullptr || history->getSize() == 0) {
        cout << "Failed to load data for " << ticker << endl;
        return false;
    }

    cout << "Loaded " << history->getSize()
         << " trading days for " << ticker << endl;

    return true;
}

PriceHistory* Stock::getHistory() const {
    return history;
}

double Stock::getPriceOnDate(const string& date) const {
    if (history == nullptr) {
        return -1;
    }

    PriceNode* node = history->findByDate(date);

    if (node == nullptr) {
        return -1;
    }

    return node->close;
}

double Stock::calculateAnnualReturn(int year) const {
    if (history == nullptr || history->getSize() == 0) {
        return 0;
    }

    PriceNode* current = history->getHead();

    PriceNode* first = nullptr;
    PriceNode* last = nullptr;

    while (current != nullptr) {
        int currentYear = CSVParser::extractYear(current->date);

        if (currentYear == year) {
            if (first == nullptr) {
                first = current;
            }

            last = current;
        }

        current = current->next;
    }

    if (first == nullptr || last == nullptr || first->close == 0) {
        return 0;
    }

    return ((last->close - first->close) / first->close) * 100.0;
}

void Stock::printSummary() const {
    cout << fixed << setprecision(2);

    cout << "Ticker: " << ticker << endl;
    cout << "Name: " << name << endl;
    cout << "Sector: " << sector << endl;
    cout << "Type: " << getType() << endl;

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

    cout << "Date Range: " << first->date
         << " to " << last->date << endl;

    cout << "Trading Days: " << history->getSize() << endl;

    cout << "Total Return: " << totalReturn << "%" << endl;
}

string Stock::getType() const {
    return "Stock";
}