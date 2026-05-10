#include "TradeStack.h"

TradeStack::TradeStack() {
    topNode = nullptr;
    size = 0;
}

TradeStack::~TradeStack() {
    while (!isEmpty()) {
        pop();
    }
}

void TradeStack::push(const TradeRecord& record) {
    StackNode* newNode = new StackNode(record);

    newNode->next = topNode;
    topNode = newNode;

    size++;
}

TradeRecord TradeStack::pop() {
    if (isEmpty()) {
        return {"", "", 0.0, 0, "", 0.0};
    }

    StackNode* temp = topNode;

    TradeRecord record = temp->data;

    topNode = topNode->next;

    delete temp;

    size--;

    return record;
}

TradeRecord TradeStack::peek() const {
    if (isEmpty()) {
        return {"", "", 0.0, 0, "", 0.0};
    }

    return topNode->data;
}

bool TradeStack::isEmpty() const {
    return topNode == nullptr;
}

int TradeStack::getSize() const {
    return size;
}

void TradeStack::printAll() const {
    if (isEmpty()) {
        cout << "No trades in history." << endl;
        return;
    }

    StackNode* current = topNode;

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