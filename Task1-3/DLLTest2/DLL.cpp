#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DLL.h"
#include <gtest/gtest.h>

// PerformanceData 構造体の定義
struct PerformanceData {
    int score = 0; // スコアの初期化
    std::string username;

    friend std::ostream& operator<<(std::ostream& os, const PerformanceData& data) {
        os << "Score: " << data.score << ", Username: " << data.username;
        return os;
    }

    bool operator==(const PerformanceData& other) const {
        return score == other.score && username == other.username;
    }

    bool operator!=(const PerformanceData& other) const {
        return !(*this == other);
    }
};

int main(int argc, char** argv) {
    DoublyLinkedList<PerformanceData> list; // DoublyLinkedList はテンプレートです。
    std::ifstream infile("Scores.txt");

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            PerformanceData data;
            if (!(iss >> data.score >> data.username)) {
                break;
            }
            list.addNode(data); // データを追加
        }
        infile.close();
    }
    else {
        std::cerr << "Cannot open file" << std::endl; // ファイルが開けない場合
    }

    list.displayList(); // リストを表示
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
