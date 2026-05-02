// struct SimResult {
// string strategyName;
// double finalValue;
// double totalInvested;
// double totalReturn; // percentage
// double cagr; // Compound Annual Growth Rate
// double maxDrawdown; // worst peak-to-trough drop
// int totalTrades;
// };
//  Pure virtual: virtual SimResult backtest(PriceHistory* history, double
// monthlyCapital, int startYear, int endYear) = 0
//  Pure virtual: virtual string getName() const = 0
//  Non-virtual: void printResult(const SimResult& result) const
//  Non-virtual helper: double calculateCAGR(double startVal, double endVal,
// int years) const
//  Non-virtual helper: double calculateMaxDrawdown(const vector<double>&
// portfolioValues) const
//  Virtual destructor