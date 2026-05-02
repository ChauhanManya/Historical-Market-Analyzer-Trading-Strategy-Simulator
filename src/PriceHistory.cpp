// A doubly-linked list of PriceNode items. Must contain: - PriceNode* head, PriceNode*
// tail, int size - void append(const string& date, double open, double high,
// double low, double close, long volume) - PriceNode* findByDate(const string&
// date) const — linear search - void printRange(const string& startDate, const
// string& endDate) const - int getSize() const - Destructor: frees all nodes
// Forward Iterator (inner class):
// class Iterator {
// public:
// Iterator(PriceNode* node);
// Iterator& operator++(); // pre-increment
// PriceNode& operator*();
// bool operator!=(const Iterator& other) const;
// };
// Iterator begin() const;
// Iterator end() const;
// Reverse Iterator (inner class):
// class ReverseIterator {
// public:
// ReverseIterator(PriceNode* node);
// ReverseIterator& operator++(); // moves backward through list
// PriceNode& operator*();
// bool operator!=(const ReverseIterator& other) const;
// };
// ReverseIterator rbegin() const;
// ReverseIterator rend() const;
// The reverse iterator must walk from tail toward head using prev pointers.