#ifndef STOCK_MANAGER_H
#define STOCK_MANAGER_H

#include <vector>
#include <string>

using namespace std;


// Generic manager for any collection of FinancialAsset-derived objects.
// Must be fully defined in this header (template classes cannot be split across .cpp).
//
// Usage:
//   StockManager<Stock> stockManager;   // manages Stock objects
//   StockManager<ETF>   etfManager;     // manages ETF objects
//
// T must be a type that:
//   - Inherits from FinancialAsset
//   - Has getTicker(), calculateAnnualReturn(int), printSummary()
//
// Course module: Templates (generic programming)
template <typename T>
class StockManager {
private:
    vector<T*> assets;

public:
    StockManager() {}

    ~StockManager() {
        for (int i = 0; i < (int)assets.size(); i++) {
            delete assets[i];
        }
    }

    void addAsset(T* asset) {
        assets.push_back(asset);
    }

    T* findByTicker(const string& ticker) {
        for (int i = 0; i < (int)assets.size(); i++) {
            if (assets[i]->getTicker() == ticker) {
                return assets[i];
            }
        }

        return nullptr;
    }

    vector<T*>& getAssets() {
        return assets;
    }

    void printAll() {
        for (int i = 0; i < (int)assets.size(); i++) {
            assets[i]->printSummary();
        }
    }
};

#endif