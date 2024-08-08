#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include "Stack.h"

/**
 * @brief 結果データ構造体
 */
struct ResultData {
    int score;        
    std::string username;

    /**
     * @brief ResultDataのストリーム挿入演算子
     * @param os 出力ストリーム
     * @param rd ResultDataオブジェクト
     * @return 出力ストリーム
     */
    friend std::ostream& operator<<(std::ostream& os, const ResultData& rd) {
        os << rd.score << '\t' << rd.username;
        return os;
    }
};

int main(int argc, char** argv) {
    Stack<ResultData> stack;

    // ファイルを開く
    std::ifstream file("Scores.txt");

    // ファイルが正常に開かれたか確認
    if (!file.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return -1;
    }

    ResultData data;

    // ファイルからデータを読み込む
    while (file >> data.score >> data.username) {
        // データをスタックにプッシュ
        stack.Push(data);
    }

    // スタックからデータをポップして表示
    while (!stack.IsEmpty()) {
        ResultData topData = stack.Pop();
        std::cout << topData << std::endl;
    }

    // ファイルを閉じる
    file.close();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}