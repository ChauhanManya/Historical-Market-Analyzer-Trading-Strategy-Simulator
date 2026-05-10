#include "../include/OrderQueue.h"

OrderQueue::OrderQueue() {
    frontNode = nullptr;
    rearNode = nullptr;
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
        frontNode = rearNode = newNode;
    }
    else {
        rearNode->next = newNode;
        rearNode = newNode;
    }

    size++;
}

Order OrderQueue::dequeue() {
    if (isEmpty()) {
        return {"", "", "", 0.0, 0, ""};
    }

    QueueNode* temp = frontNode;
    Order order = temp->data;

    frontNode = frontNode->next;

    if (frontNode == nullptr) {
        rearNode = nullptr;
    }

    delete temp;
    size--;

    return order;
}

Order OrderQueue::peek() const {
    if (isEmpty()) {
        return {"", "", "", 0.0, 0, ""};
    }

    return frontNode->data;
}

bool OrderQueue::isEmpty() const {
    return frontNode == nullptr;
}

int OrderQueue::getSize() const {
    return size;
}

void OrderQueue::printAll() const {
    QueueNode* current = frontNode;

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