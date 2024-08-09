#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include "SQ.h"

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
    // テスト用のスタックとキューの使用例
    Stack<ResultData> stack;
    Queue<ResultData> queue;

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
        // データをスタックとキューにプッシュ
        stack.Push(data);
        queue.Push(data);
    }

    // スタックからデータをポップして表示
    std::cout << "Stack contents:" << std::endl;
    while (!stack.IsEmpty()) {
        ResultData topData = stack.Pop();
        std::cout << topData << std::endl;
    }

    // キューからデータをポップして表示
    std::cout << "Queue contents:" << std::endl;
    while (!queue.IsEmpty()) {
        ResultData frontData = queue.Pop();
        std::cout << frontData << std::endl;
    }

    // ファイルを閉じる
    file.close();

    // Gtest
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
