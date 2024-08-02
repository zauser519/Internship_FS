#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include "DLL.h"

// メイン関数
int main(int argc, char** argv) {
    DoublyLinkedList list;
    std::ifstream infile("Scores.txt");

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            int score;
            std::string username;
            if (!(iss >> score >> username)) {
                break; // エラー処理
            }
            list.addNode(score, username);
        }
        infile.close();
    }
    else {
        std::cerr << "ファイルを開けません" << std::endl;
    }

    list.displayList();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}