// Represents an index instrument (e.g., SPX). Inherits from FinancialAsset. Must contain: -
// Everything in Stock, plus: - expenseRatio (double) member - getType() const — returns
// “ETF” - printSummary() const — override: additionally prints expense ratio and 10-year
// CAGR