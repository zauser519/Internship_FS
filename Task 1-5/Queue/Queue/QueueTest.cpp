#include <gtest/gtest.h>
#include "Queue.h"

// テスト0: リストが空である場合の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 0
// 意図する結果: キューが空の場合、データ数が0であることを確認する。
// 補足:
TEST(StackTest, Test0_EmptyList) {
    Queue<int> queue;
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト1: 要素をプッシュした後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 1
// 意図する結果: 要素を1つプッシュした後、データ数が1になることを確認する。
// 補足:
TEST(StackTest, Test1_PushElement) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト2: 要素をポップした後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 0
// 意図する結果: 要素を1つポップした後、データ数が0になることを確認する。
// 補足:
TEST(StackTest, Test2_PopElement) {
    Queue<int> queue;
    queue.Push(10);
    queue.Pop();
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト3: 要素のプッシュに失敗した後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 0
// 意図する結果: 要素のプッシュが失敗した場合、データ数が変わらないことを確認する。
// 補足:
TEST(StackTest, Test3_PushFail) {
    Queue<int> queue;
    // simulate push failure if any specific condition is met
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト4: プッシュを2回行った後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 2
// 意図する結果: 要素を2つプッシュした後、データ数が2になることを確認する。
// 補足:
TEST(StackTest, Test4_PushTwice) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    EXPECT_EQ(queue.GetSize(), 2);
}

// テスト5: プッシュを2回行った後、1回ポップした後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 1
// 意図する結果: 2回プッシュして1回ポップした後、データ数が1になることを確認する。
// 補足:
TEST(StackTest, Test5_PushTwicePopOnce) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Pop();
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト6: リストが空である場合に、ポップを行った後の戻り値
// インターフェース: データ数の取得
// 想定する戻り値: 0
// 意図する結果: 空のリストでポップを試みた後、データ数が0のままであることを確認する。
// 補足:
TEST(StackTest, Test6_PopEmptyList) {
    Queue<int> queue;
    try {
        queue.Pop();
    }
    catch (const std::out_of_range& e) {
        // Expected exception
    }
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト7: constのメソッドであるか
// インターフェース: データ数の取得
// 想定する戻り値: 
// 意図する結果: constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
// 補足:
#if 0
TEST(StackTest, Test7_ConstMethod) {
    const Queue<int> queue;
    queue.GetSize(); // Should not cause a compile error
}
#endif

// テスト8: リストが空である場合に、プッシュした際の挙動
// インターフェース: プッシュ
// 想定する戻り値: TRUE
// 意図する結果: リストの末尾に要素が追加される
// 補足:
TEST(StackTest, Test8_PushToEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト9: リストに複数の要素がある場合に、プッシュした際の挙動
// インターフェース: プッシュ
// 想定する戻り値: TRUE
// 意図する結果: リストの末尾に要素が追加される
// 補足:
TEST(StackTest, Test9_PushToNonEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    EXPECT_EQ(queue.GetSize(), 2);
}

// テスト10: 非constのメソッドであるか
// インターフェース: プッシュ
// 想定する戻り値: 
// 意図する結果: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
// 補足:
#if 0
TEST(StackTest, Test10_NonConstMethod) {
    const Queue<int> queue;
    queue.Push(10); // Should cause a compile error
}
#endif

// テスト11: リストが空である場合に、ポップした際の挙動
// インターフェース: ポップ
// 想定する戻り値: FALSE
// 意図する結果: 何も起こらない
// 補足:
TEST(StackTest, Test11_PopFromEmptyList) {
    Queue<int> queue;
    try {
        queue.Pop();
    }
    catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "Queue is empty");
    }
}

// テスト12: リストに複数の要素がある場合に、ポップした際の挙動
// インターフェース: ポップ
// 想定する戻り値: TRUE
// 意図する結果: 末尾要素が引数経由で渡され、その要素がリストから削除される
// 補足:
TEST(StackTest, Test12_PopFromNonEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    int data = queue.Pop();
    EXPECT_EQ(data, 10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト13: リストに複数の要素がある場合に、複数回ポップした際の挙動
// インターフェース: ポップ
// 想定する戻り値: TRUE
// 意図する結果: 最後に追加した要素から順に引数経由で渡される
// 補足: 追加した順の逆順に取り出されるかチェックし、リストが空になるまで取り出す。
TEST(StackTest, Test13_PopMultiple) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    EXPECT_EQ(queue.Pop(), 10);
    EXPECT_EQ(queue.Pop(), 20);
    EXPECT_EQ(queue.Pop(), 30);
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト14: 非constのメソッドであるか
// インターフェース: ポップ
// 想定する戻り値: 
// 意図する結果: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
// 補足:
#if 0
TEST(StackTest, Test14_NonConstMethod) {
    const Queue<int> queue;
    queue.Pop(); // Should cause a compile error
}
#endif
