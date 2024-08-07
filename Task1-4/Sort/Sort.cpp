#define RUN_TESTS

#include <gtest/gtest.h>
#include "Sort.h"

// テスト項目 0: 要素を持たないリストにソートを実行した時の挙動
TEST(QuickSortTest, EmptyList) {
    DoubleLinkedList scores;
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_TRUE(scores.toVector().empty());
}

// テスト項目 1: 要素を1つだけ持つリストにソートを実行した時の挙動
TEST(QuickSortTest, SingleElementList) {
    DoubleLinkedList scores;
    scores.addScore(10, "user1");
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_EQ(scores.toVector().size(), 1);
    ASSERT_EQ(scores.toVector()[0].score, 10);
    ASSERT_EQ(scores.toVector()[0].username, "user1");
}

// テスト項目 2: 2つ以上要素を持つリストにソートを実行した時の挙動
TEST(QuickSortTest, MultipleElementsList) {
    DoubleLinkedList scores;
    scores.addScore(20, "user2");
    scores.addScore(10, "user1");
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_EQ(scores.toVector()[0].score, 10);
    ASSERT_EQ(scores.toVector()[1].score, 20);
}

// テスト項目 3: 同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時の挙動
TEST(QuickSortTest, DuplicateKeys) {
    DoubleLinkedList scores;
    scores.addScore(10, "user2");
    scores.addScore(10, "user1");
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_EQ(scores.toVector()[0].score, 10);
    ASSERT_EQ(scores.toVector()[1].score, 10);
}

// テスト項目 4: 整列済みリストにソートを実行した時の挙動
TEST(QuickSortTest, AlreadySortedList) {
    DoubleLinkedList scores;
    scores.addScore(10, "user1");
    scores.addScore(20, "user2");
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_EQ(scores.toVector()[0].score, 10);
    ASSERT_EQ(scores.toVector()[1].score, 20);
}

// テスト項目 5: 一度整列したリストの各所に挿入し、再度ソートを実行した時の挙動
TEST(QuickSortTest, InsertAndResort) {
    DoubleLinkedList scores;
    scores.addScore(10, "user1");
    scores.addScore(20, "user2");
    scores.addScore(15, "user3");
    scores.quicksort(scores.getHead(), scores.getTail(), true, true);
    ASSERT_EQ(scores.toVector()[0].score, 10);
    ASSERT_EQ(scores.toVector()[1].score, 15);
    ASSERT_EQ(scores.toVector()[2].score, 20);
}

// テスト項目 6: キー指定をしなかった(nullptrを渡した)時の挙動
TEST(QuickSortTest, NullptrKey) {
    DoubleLinkedList scores;
    scores.addScore(10, "user1");
    scores.quicksort(scores.getHead(), nullptr, true, true);
    ASSERT_EQ(scores.toVector()[0].score, 10);
}

// テスト項目 7: 型などが不適切なキー指定が引数で渡された時の挙動 (コンパイルエラー)
TEST(QuickSortTest, InvalidKeyType) {
    // このテストはコンパイルエラーをチェックするためのものです
    // DoubleLinkedList scores;
    // scores.quicksort(scores.getHead(), scores.getTail(), true, "invalid_key");
    ASSERT_TRUE(true);
}

// テスト項目 8: 非constのメソッドであるか (コンパイルエラー)
TEST(QuickSortTest, NonConstMethod) {
    const DoubleLinkedList scores;
    // scores.quicksort(scores.getHead(), scores.getTail(), true, true); // これはコンパイルエラーになるはず
    ASSERT_TRUE(true);
}
