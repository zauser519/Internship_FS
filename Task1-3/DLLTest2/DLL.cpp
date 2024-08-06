#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include "DLL.h"

using PerformanceData = std::pair<int, std::string>;

void displayList(const DoublyLinkedList<PerformanceData>& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << "Score: " << it->first << ", User Name: " << it->second << std::endl;
    }
}

int main(int argc, char** argv) {
    DoublyLinkedList<PerformanceData> list;
    std::ifstream infile("Scores.txt");

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            int score;
            std::string username;
            if (!(iss >> score >> username)) {
                break;
            }
            list.addNode({ score, username });
        }
        infile.close();
    }
    else {
        std::cerr << "Cannot open file" << std::endl;
    }

    displayList(list);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
