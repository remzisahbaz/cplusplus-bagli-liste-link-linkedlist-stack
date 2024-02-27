#ifndef TOPLINKEDLIST_HPP
#define TOPLINKEDLIST_HPP

#include "Node.hpp"

class TopLinkedList {
public:
    TopLinkedList();
    ~TopLinkedList();
    void add(int data);
    void print();
    double calculateAverage();
    int getNodeCount();

private:
    Node* head;
};

#endif
