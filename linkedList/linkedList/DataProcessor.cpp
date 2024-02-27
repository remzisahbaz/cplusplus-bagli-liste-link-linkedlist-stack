#include "DataProcessor.hpp"
#include <iostream>

DataProcessor::DataProcessor() {}

DataProcessor::~DataProcessor() {
    for (int i = 0; i < topLists.size(); i++) {
        delete topLists[i];
        delete bottomLists[i];
    }
}

int DataProcessor::countFileLines(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "File cannot be opened." << std::endl;
        return -1;
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();

    return lineCount;
}

void DataProcessor::readDataFromFile(std::ifstream& file, int lineCount) {
    std::string line;
    int lineIndex = 0;

    while (std::getline(file, line)) {
        TopLinkedList* topList = new TopLinkedList();
        BottomLinkedList* bottomList = new BottomLinkedList();

        int i = 0;
        while (i < line.length()) {
            if (isdigit(line[i]) && i + 1 < line.length() && isdigit(line[i + 1])) {
                int digit1 = line[i] - '0';
                int digit2 = line[i + 1] - '0';
                int number = digit1 * 10 + digit2;

                topList->add(digit1);
                bottomList->add(digit2);

                i += 2;
            }
            else {
                i++;
            }
        }

        topLists.push_back(topList);
        bottomLists.push_back(bottomList);

        lineIndex++;
    }

    file.close();
}

void DataProcessor::swapLists(int positionA, int positionB) {
    TopLinkedList* tempTop = topLists[positionA];
    BottomLinkedList* tempBottom = bottomLists[positionA];

    topLists[positionA] = topLists[positionB];
    bottomLists[positionA] = bottomLists[positionB];

    topLists[positionB] = tempTop;
    bottomLists[positionB] = tempBottom;
}

void DataProcessor::printLists() {
    std::cout << std::endl;
    for (int i = 0; i < topLists.size(); i++) {
        std::cout << "Top Linked List[" << i << "]: ";
        topLists[i]->print();
    }
    std::cout << std::endl;

    for (int i = 0; i < bottomLists.size(); i++) {
        std::cout << "Bottom Linked List[" << i << "]: ";
        bottomLists[i]->print();
    }
}

double DataProcessor::calculateTopListSum() {
    double sum = 0.0;

    for (int i = 0; i < topLists.size(); i++) {
        sum += topLists[i]->calculateAverage();
    }

    return sum;
}

double DataProcessor::calculateBottomListSum() {
    double sum = 0.0;

    for (int i = 0; i < bottomLists.size(); i++) {
        sum += bottomLists[i]->calculateAverage();
    }

    return sum;
}
