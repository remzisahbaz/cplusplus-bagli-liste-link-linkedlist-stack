#ifndef BOTTOMLINKEDLIST_HPP
#define BOTTOMLINKEDLIST_HPP

#include "Node.hpp"

class BottomLinkedList {
public:
    BottomLinkedList();
    ~BottomLinkedList();
    void add(int data);
    void print();
    double calculateAverage();
    int getNodeCount();

private:
    Node* head;
};

#endif
