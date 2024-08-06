#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>

// スコアデータを保持する構造体
struct Score {
    int score;
    std::string username;
    Score(int s = 0, std::string u = "") : score(s), username(u) {} // メンバーを初期化
};

// 2つのScoreオブジェクトを交換する関数
void swap(Score& a, Score& b) noexcept;

// クイックソートのためのパーティション関数
int partition(std::vector<Score>& scores, int low, int high, bool byScore, bool ascending);

// クイックソート関数
void quicksort(std::vector<Score>& scores, int low, int high, bool byScore, bool ascending);

// ファイルからスコアを読み込む関数
std::vector<Score> loadScores(const std::string& filename);

// スコアを出力する関数
void printScores(const std::vector<Score>& scores);

#endif // SORT_H
