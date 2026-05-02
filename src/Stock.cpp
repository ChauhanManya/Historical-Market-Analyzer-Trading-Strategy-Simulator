// File: include/Stock.h
// Represents a single stock (e.g., AMZN). Inherits from FinancialAsset. Must contain: - A
// PriceHistory* member — owns the price history linked list - loadFromCSV(const string&
// filename) — parses CSV and builds the linked list - getHistory() — returns pointer to the
// PriceHistory - getPriceOnDate(const string& date) const — O(n) scan -
// calculateAnnualReturn(int year) const — override: (end_price - start_price) /
// start_price * 100 - printSummary() const — override: print ticker, date range, total return,
// number of trading days - getType() const — returns “Stock”