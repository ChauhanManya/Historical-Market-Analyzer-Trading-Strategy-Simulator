#include "TradeStack.h"
#include <iostream>
using namespace std;

TradeStack::TradeStack() {
    top = nullptr;
    size = 0;
}

TradeStack::~TradeStack() {
    while (!isEmpty()) {
        pop();
    }
}

void TradeStack::push(const TradeRecord& record) {
    StackNode* newNode;
    newNode->data = record;
    newNode->next = top;
    top = newNode;

    size++;
}

TradeRecord TradeStack::pop() {
    if (isEmpty()) {
        return {"", "", 0.0, 0, "", 0.0};
    }

    StackNode* temp = top;

    TradeRecord record = temp->data;

    top = top->next;

    delete temp;

    size--;

    return record;
}

TradeRecord TradeStack::peek() const {
    if (isEmpty()) {
        return {"", "", 0.0, 0, "", 0.0};
    }

    return top->data;
}

bool TradeStack::isEmpty() const {
    return top == nullptr;
}

int TradeStack::getSize() const {
    return size;
}

void TradeStack::printAll() const {
    if (isEmpty()) {
        cout << "No trades in history." << endl;
        return;
    }

    StackNode* current = top;

    while (current != nullptr) {
        cout << current->data.date
             << " | "
             << current->data.action
             << " | "
             << current->data.ticker
             << " | Shares: "
             << current->data.shares
             << " | Price: $"
             << current->data.price
             << " | Total Cost: $"
             << current->data.totalCost
             << endl;

        current = current->next;
    }
}