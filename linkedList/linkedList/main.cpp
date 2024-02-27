#include <iostream>
#include <fstream>
#include <string>
#include "TopLinkedList.hpp"
#include "BottomLinkedList.hpp"
#include "DataProcessor.hpp"

int main() {
    DataProcessor dataProcessor;
    std::ifstream file("data.txt");
    int lineCount = 0;
    lineCount = dataProcessor.countFileLines("data.txt");


    if (lineCount == -1) {
        std::cout << "File could not be opened." << std::endl;
        return 1;
    }

  
    dataProcessor.readDataFromFile(file, lineCount);
    dataProcessor.printLists();

    int positionA, positionB;
    std::cout << "\nPosition A: ";
    std::cin >> positionA;
    std::cout << "Position B: ";
    std::cin >> positionB;

    if (positionA >= 0 && positionA < lineCount && positionB >= 0 && positionB < lineCount) {
        dataProcessor.swapLists(positionA, positionB);
        std::cout << "\nNew Lists After Swapping:\n";
        dataProcessor.printLists();

        double topListSum = dataProcessor.calculateTopListSum();
        double bottomListSum = dataProcessor.calculateBottomListSum();
        std::cout << "Top: " << topListSum << std::endl;
        std::cout << "Bottom: " << bottomListSum << std::endl;
    }
    else {
        std::cout << "Invalid positions. Please enter positions between 0 and " << lineCount - 1 << "." << std::endl;
    }

    return 0;
}
