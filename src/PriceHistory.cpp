#include "../include/PriceHistory.h"
#include <iostream>
#include <iomanip>

using namespace std;

PriceHistory::PriceHistory() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

PriceHistory::~PriceHistory() {
    PriceNode* current = head;

    while (current != nullptr) {
        PriceNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

void PriceHistory::append(const string& date,
                          double open,
                          double high,
                          double low,
                          double close,
                          long volume) {
    PriceNode* newNode ;

    newNode->date = date;
    newNode->open = open;
    newNode->high = high;
    newNode->low = low;
    newNode->close = close;
    newNode->volume = volume;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

PriceNode* PriceHistory::findByDate(const string& date) const {
    PriceNode* current = head;

    while (current != nullptr) {
        if (current->date == date) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

void PriceHistory::printRange(const string& startDate,
                              const string& endDate) const {
    cout << fixed << setprecision(2);

    PriceNode* current = head;

    while (current != nullptr) {
        if (current->date >= startDate && current->date <= endDate) {
            cout << current->date
                 << " | Open: " << current->open
                 << " | High: " << current->high
                 << " | Low: " << current->low
                 << " | Close: " << current->close
                 << " | Volume: " << current->volume
                 << endl;
        }

        current = current->next;
    }
}

int PriceHistory::getSize() const {
    return size;
}

PriceNode* PriceHistory::getHead() const {
    return head;
}

PriceNode* PriceHistory::getTail() const {
    return tail;
}

PriceHistory::Iterator::Iterator(PriceNode* node) {
    current = node;
}

PriceHistory::Iterator& PriceHistory::Iterator::operator++() {
    if (current != nullptr) {
        current = current->next;
    }

    return *this;
}

PriceNode& PriceHistory::Iterator::operator*() {
    return *current;
}

bool PriceHistory::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

PriceHistory::Iterator PriceHistory::begin() const {
    return Iterator(head);
}

PriceHistory::Iterator PriceHistory::end() const {
    return Iterator(nullptr);
}

PriceHistory::ReverseIterator::ReverseIterator(PriceNode* node) {
    current = node;
}

PriceHistory::ReverseIterator& PriceHistory::ReverseIterator::operator++() {
    if (current != nullptr) {
        current = current->prev;
    }

    return *this;
}

PriceNode& PriceHistory::ReverseIterator::operator*() {
    return *current;
}

bool PriceHistory::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return current != other.current;
}

PriceHistory::ReverseIterator PriceHistory::rbegin() const {
    return ReverseIterator(tail);
}

PriceHistory::ReverseIterator PriceHistory::rend() const {
    return ReverseIterator(nullptr);
}