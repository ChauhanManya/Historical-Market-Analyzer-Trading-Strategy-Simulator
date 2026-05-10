#include "OrderQueue.h"
#include <iostream>

OrderQueue::OrderQueue() {
    front = nullptr;
    back = nullptr;
    size = 0;
}

OrderQueue::~OrderQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void OrderQueue::enqueue(const Order& order) {
    QueueNode* newNode = new QueueNode(order);

    if (isEmpty()) {
        front = back = newNode;
    }
    else {
        back->next = newNode;
        back = newNode;
    }

    size++;
}

Order OrderQueue::dequeue() {
    if (isEmpty()) {
        return {"", "", "", 0.0, 0, ""};
    }

    QueueNode* temp = front;
    Order order = temp->data;

    front = front->next;

    if (front == nullptr) {
        back = nullptr;
    }

    delete temp;
    size--;

    return order;
}

Order OrderQueue::peek() const {
    if (isEmpty()) {
        return {"", "", "", 0.0, 0, ""};
    }

    return front->data;
}

bool OrderQueue::isEmpty() const {
    return front == nullptr;
}

int OrderQueue::getSize() const {
    return size;
}

void OrderQueue::printAll() const {
    QueueNode* current = front;

    while (current != nullptr) {
        cout << current->data.ticker
             << " | "
             << current->data.side
             << " | "
             << current->data.shares
             << endl;

        current = current->next;
    }
}