// A fixed-size circular buffer for computing N-day moving averages. Must contain: - double*
// buffer, int capacity, int head, int tail, int count - void enqueue(double value) —
// if full, overwrites oldest (circular behavior) - double dequeue() - double peek() const —
// returns oldest value without removing - double getAverage() const — O(n) sum / count -
// bool isFull() const, bool isEmpty() const - int getCount() const - Constructor
// takes capacity: CircularQueue(int capacity) - Destructor frees buffer
// Usage: To compute a 50-day moving average, create CircularQueue(50). Enqueue each
// day’s close price. Once full, getAverage() returns the 50-day MA.