#include "TopLinkedList.hpp"
#include <iostream>

TopLinkedList::TopLinkedList() {
    head = nullptr;
}

TopLinkedList::~TopLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void TopLinkedList::add(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void TopLinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;
}

double TopLinkedList::calculateAverage() {
    double sum = 0.0;
    int count = 0;

    Node* current = head;
    while (current != nullptr) {
        sum += current->data;
        count++;
        current = current->next;
    }

    if (count > 0) {
        return sum / count;
    }
    else {
        return 0.0;
    }
}

int TopLinkedList::getNodeCount() {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}
