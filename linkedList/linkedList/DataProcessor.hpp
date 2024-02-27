#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include <string>
#include <fstream>
#include <vector>
#include "TopLinkedList.hpp"
#include "BottomLinkedList.hpp"

class DataProcessor {
public:
    DataProcessor();
    ~DataProcessor();
    int countFileLines(const std::string& fileName);
    void readDataFromFile(std::ifstream& file, int lineCount);
    void swapLists(int positionA, int positionB);
    void printLists();
    double calculateTopListSum();
    double calculateBottomListSum();

private:
    std::vector<TopLinkedList*> topLists;
    std::vector<BottomLinkedList*> bottomLists;
};

#endif
