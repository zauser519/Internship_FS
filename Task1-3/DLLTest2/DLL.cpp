#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include "DLL.h"

using PerformanceData = std::pair<int, std::string>;

// リストの内容を表示する関数
// 入力: DoublyLinkedList<PerformanceData> 型のリスト
// 期待結果: リストの全要素をコンソールに表示する
void displayList(const DoublyLinkedList<PerformanceData>& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << "Score: " << it->first << ", User Name: " << it->second << std::endl;
    }
}

// ファイルからスコアを読み取りリストに挿入する関数
// 入力: ファイル名 (std::string), DoublyLinkedList<PerformanceData> 型のリスト
// 期待結果: ファイルから読み取ったスコアをリストに挿入する
void readScoresFromFile(const std::string& filename, DoublyLinkedList<PerformanceData>& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int score;
        std::string username;
        if (iss >> score >> username) {
            list.Insert(list.end(), std::make_pair(score, username));
        }
    }
    file.close();
}

// メイン関数
// 入力: コマンドライン引数
// 期待結果: ファイルからスコアを読み込み、リストに挿入して表示し、Google Testを実行する
int main(int argc, char** argv) {
    DoublyLinkedList<PerformanceData> scoreList;

    // ファイルからスコアを読み取り、ダブルリンクリストに保存
    readScoresFromFile("Scores.txt", scoreList);

    // ダブルリンクリストに保存されたスコアを表示
    displayList(scoreList);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
