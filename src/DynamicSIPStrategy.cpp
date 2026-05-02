// Your custom investment algorithm — the only strategy in this project where you define the
// logic.
// The baseline you are trying to beat: FixedSIPStrategy invests the same dollar amount
// on the same day every month, regardless of market conditions.
// Your freedom: you may design any algorithm that uses the daily price data available in
// PriceHistory. Some dimensions to consider (not a checklist — think beyond these): -
// When within the month to invest — not necessarily the 1st day - How much to invest each
// month — vary based on market signals - Whether to skip a month and carry funds forward -
// Any signal you can derive from price, volume, moving averages, or trend direction
// Hard constraints: - Total capital deployed over the full period must equal (months) ×
// monthlyCapital — budget-neutral relative to Fixed SIP - You may only use data available
// up to the current trading day (no lookahead in the linked list) - No external libraries — only
// the data structures you built in this project
// You define your own constructor and member variables. The only interface requirement
// is implementing backtest() and getName() (inherited from TradingStrategy).
//  backtest(history, monthlyCapital, startYear, endYear) — your full algorithm
//  getName() — include your key parameters in the string so results are identifiable