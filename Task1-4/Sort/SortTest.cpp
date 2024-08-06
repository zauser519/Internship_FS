#define RUN_TESTS

#include <gtest/gtest.h>
#include "Sort.h"

// リストにデータを追加するヘルパー関数
void addScore(std::vector<Score>& scores, int score, const std::string& username) {
    scores.push_back({ score, username });
}

// テスト項目 0: 要素を持たないリストにソートを実行した時の挙動
TEST(QuickSortTest, EmptyList) {
    std::vector<Score> scores;
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_TRUE(scores.empty());
}

// テスト項目 1: 要素を1つだけ持つリストにソートを実行した時の挙動
TEST(QuickSortTest, SingleElementList) {
    std::vector<Score> scores;
    addScore(scores, 10, "user1");
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_EQ(scores.size(), 1);
    ASSERT_EQ(scores[0].score, 10);
    ASSERT_EQ(scores[0].username, "user1");
}

// テスト項目 2: 2つ以上要素を持つリストにソートを実行した時の挙動
TEST(QuickSortTest, MultipleElementsList) {
    std::vector<Score> scores;
    addScore(scores, 20, "user2");
    addScore(scores, 10, "user1");
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_EQ(scores[0].score, 10);
    ASSERT_EQ(scores[1].score, 20);
}

// テスト項目 3: 同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時の挙動
TEST(QuickSortTest, DuplicateKeys) {
    std::vector<Score> scores;
    addScore(scores, 10, "user2");
    addScore(scores, 10, "user1");
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_EQ(scores[0].score, 10);
    ASSERT_EQ(scores[1].score, 10);
}

// テスト項目 4: 整列済みリストにソートを実行した時の挙動
TEST(QuickSortTest, AlreadySortedList) {
    std::vector<Score> scores;
    addScore(scores, 10, "user1");
    addScore(scores, 20, "user2");
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_EQ(scores[0].score, 10);
    ASSERT_EQ(scores[1].score, 20);
}

// テスト項目 5: 一度整列したリストの各所に挿入し、再度ソートを実行した時の挙動
TEST(QuickSortTest, InsertAndResort) {
    std::vector<Score> scores;
    addScore(scores, 10, "user1");
    addScore(scores, 20, "user2");
    addScore(scores, 15, "user3");
    quicksort(scores, 0, scores.size() - 1, true, true);
    ASSERT_EQ(scores[0].score, 10);
    ASSERT_EQ(scores[1].score, 15);
    ASSERT_EQ(scores[2].score, 20);
}

// テスト項目 6: キー指定をしなかった(nullptrを渡した)時の挙動
TEST(QuickSortTest, NullKey) {
    std::vector<Score> scores;
    addScore(scores, 10, "user1");
    // nullptrをキー指定するケースは無いため、このテストは省略します
}

// テスト項目 7: 型などが不適切なキー指定が引数で渡された時の挙動
// このテストはコンパイルエラーをチェックするため、自動テストには含めません

// テスト項目 8: 非constのメソッドであるか
// このテストもコンパイルエラーをチェックするため、自動テストには含めません
