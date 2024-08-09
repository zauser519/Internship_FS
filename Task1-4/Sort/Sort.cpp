#include "Sort.h"
#include <fstream>
#include <iostream>
#include <string>
#include <gtest/gtest.h>

using PerformanceData = std::pair<int, std::string>;

// スコアをファイルから読み取り、リストに挿入する関数
// 入力: ファイル名 (std::string), DoublyLinkedList<PerformanceData>& 型のリスト
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
            list.Insert(list.end(), PerformanceData{ score, username });
        }
    }
    file.close();
}

// 昇順でスコアを比較する関数
// 入力: PerformanceData 型の a と b
inline bool SA(const PerformanceData& a, const PerformanceData& b) {
    return a.first < b.first;
}

// 降順でスコアを比較する関数
// 入力: PerformanceData 型の a と b
inline bool SD(const PerformanceData& a, const PerformanceData& b) {
    return a.first > b.first;
}

// 昇順で名前を比較する関数
// 入力: PerformanceData 型の a と b
inline bool NameA(const PerformanceData& a, const PerformanceData& b) {
    return a.second < b.second;
}

// 降順で名前を比較する関数
// 入力: PerformanceData 型の a と b
inline bool NameD(const PerformanceData& a, const PerformanceData& b) {
    return a.second > b.second;
}

// リストの内容を表示する関数
// 入力: DoublyLinkedList<PerformanceData>& 型のリスト
// 期待結果: リストの全要素をコンソールに表示する
void DisplayList(DoublyLinkedList<PerformanceData>& list) {
    auto it = list.begin();
    while (it != list.end()) {
        std::cout << (*it).first << "\t" << (*it).second << std::endl;
        ++it;
    }
}

// メイン関数
// 入力: コマンドライン引数
// 期待結果: ファイルからスコアを読み込み、リストに挿入して表示し、Google Test を実行する
int main(int argc, char** argv) {
    DoublyLinkedList<PerformanceData> list;
    readScoresFromFile("Scores.txt", list);

    list.Sort(SA);
    std::cout << "Score After Sort (Ascend)" << std::endl;
    DisplayList(list);

    list.Sort(SD);
    std::cout << "Score After Sort (Descend)" << std::endl;
    DisplayList(list);

    list.Sort(NameA);
    std::cout << "Username After Sort (Ascend)" << std::endl;
    DisplayList(list);

    list.Sort(NameD);
    std::cout << "Username After Sort (Descend)" << std::endl;
    DisplayList(list);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
