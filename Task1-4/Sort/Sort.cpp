#include "Sort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

// 2つのScoreオブジェクトを交換する関数
void swap(Score& a, Score& b) noexcept {
    Score temp = a;
    a = b;
    b = temp;
}

// クイックソートのためのパーティション関数
int partition(std::vector<Score>& scores, int low, int high, bool byScore, bool ascending) {
    Score pivot = scores[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        bool condition = byScore ? (scores[j].score < pivot.score) : (scores[j].username < pivot.username);
        if (!ascending) condition = !condition;

        if (condition) {
            i++;
            swap(scores[i], scores[j]);
        }
    }
    swap(scores[i + 1], scores[high]);
    return (i + 1);
}

// クイックソート関数
void quicksort(std::vector<Score>& scores, int low, int high, bool byScore, bool ascending) {
    if (low < high) {
        int pi = partition(scores, low, high, byScore, ascending);
        quicksort(scores, low, pi - 1, byScore, ascending);
        quicksort(scores, pi + 1, high, byScore, ascending);
    }
}

// ファイルからスコアを読み込む関数
std::vector<Score> loadScores(const std::string& filename) {
    std::vector<Score> scores;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            int score;
            std::string username;
            ss >> score >> username;
            scores.emplace_back(score, username);
        }
        file.close();
    }
    return scores;
}

// スコアを出力する関数
void printScores(const std::vector<Score>& scores) {
    for (const auto& score : scores) {
        std::cout << score.score << "\t" << score.username << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string filename = "Scores.txt";
    std::vector<Score> scores = loadScores(filename);
    std::cout << "Original scores:" << std::endl;
    printScores(scores);

    // スコアを昇順にソート
    quicksort(scores, 0, scores.size() - 1, true, true);
    std::cout << "\nScores sorted in ascending order:" << std::endl;
    printScores(scores);

    // スコアを降順にソート
    quicksort(scores, 0, scores.size() - 1, true, false);
    std::cout << "\nScores sorted in descending order:" << std::endl;
    printScores(scores);

    // ユーザー名を昇順にソート
    quicksort(scores, 0, scores.size() - 1, false, true);
    std::cout << "\nUser names sorted in ascending order:" << std::endl;
    printScores(scores);

    // ユーザー名を降順にソート
    quicksort(scores, 0, scores.size() - 1, false, false);
    std::cout << "\nUser names sorted in descending order:" << std::endl;
    printScores(scores);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
