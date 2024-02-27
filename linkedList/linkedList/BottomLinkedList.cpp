#include "BottomLinkedList.hpp"
#include <iostream>

BottomLinkedList::BottomLinkedList() {
    head = nullptr;
}

BottomLinkedList::~BottomLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void BottomLinkedList::add(int data) {
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

void BottomLinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;
}

double BottomLinkedList::calculateSum() {
    double sum = 0.0;
    Node* current = head;
    while (current != nullptr) {
        sum += static_cast<double>(current->data);
        current = current->next;
    }
    return sum;
}
