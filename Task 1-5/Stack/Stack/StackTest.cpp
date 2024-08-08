#include <gtest/gtest.h>
#include "Stack.h"

// テスト0: リストが空である場合の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
TEST(StackTest, EmptyListSize) {
    Stack<int> stack;
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト1: 要素をプッシュした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
TEST(StackTest, PushOneElement) {
    Stack<int> stack;
    stack.Push(1);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト2: 要素をポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
TEST(StackTest, PopOneElement) {
    Stack<int> stack;
    stack.Push(1);
    stack.Pop();
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト3: 要素のプッシュに失敗した後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
TEST(StackTest, PushFail) {
    Stack<int> stack;
    // プッシュが失敗するケースがないため、スタックが空の場合をテスト
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト4: プッシュを2回行った後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 2
TEST(StackTest, PushTwoElements) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    EXPECT_EQ(stack.GetSize(), 2);
}

// テスト5:プッシュを2回行った後、１回ポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
TEST(StackTest, PushTwoPopOneElement) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Pop();
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト6: リストが空である場合に、ポップを行った後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
TEST(StackTest, PopEmptyList) {
    Stack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト7: constのメソッドであるか
// インターフェース:データ数の取得
// 想定する戻り値: 
// 意図する結果:
// 補足: constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
#ifndef SKIP_TEST7
TEST(StackTest, ConstMethod) {
    const Stack<int> stack;
    EXPECT_NO_THROW(stack.GetSize());
}
#endif

// テスト8: リストが空である場合に、プッシュした際の挙動
// インターフェース:プッシュ
// 想定する戻り値: TRUE
// 意図する結果:リストの末尾に要素が追加される
TEST(StackTest, PushToEmptyList) {
    Stack<int> stack;
    EXPECT_NO_THROW(stack.Push(1));
}

// テスト9: リストに複数の要素がある場合に、プッシュした際の挙動
// インターフェース:プッシュ
// 想定する戻り値: TRUE
// 意図する結果: リストの末尾に要素が追加される
TEST(StackTest, PushToNonEmptyList) {
    Stack<int> stack;
    stack.Push(1);
    EXPECT_NO_THROW(stack.Push(2));
}

// テスト10: 非constのメソッドであるか
// インターフェース:プッシュ
// 想定する戻り値: 
// 意図する結果: 
// 補足: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
#ifndef SKIP_TEST10
TEST(StackTest, NonConstPushMethod) {
    const Stack<int> stack;
    // コンパイルエラーになるためコメントアウト
    // stack.Push(1);
}
#endif

// テスト11: リストが空である場合に、ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: FALSE
// 意図する結果: 何も起こらない
TEST(StackTest, PopFromEmptyList) {
    Stack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

// テスト12: リストに複数の要素がある場合に、ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: TRUE
// 意図する結果: 末尾要素が引数経由で渡され、その要素がリストから削除される
TEST(StackTest, PopFromNonEmptyList) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    EXPECT_NO_THROW({
        int value = stack.Pop();
        EXPECT_EQ(value, 2);
        });
}

// テスト13: リストに複数の要素がある場合に、複数回ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: TRUE
// 意図する結果: 最後に追加した要素から順に引数経由で渡される
// 補足:追加した順の逆順に取り出されるかチェックし、リストが空になるまで取り出す。
TEST(StackTest, PopMultipleElements) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    EXPECT_NO_THROW({
        EXPECT_EQ(stack.Pop(), 3);
        EXPECT_EQ(stack.Pop(), 2);
        EXPECT_EQ(stack.Pop(), 1);
        });
}

// テスト14: 非constのメソッドであるか
// インターフェース:ポップ
// 想定する戻り値: 
// 意図する結果:
// 補足: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
#ifndef SKIP_TEST14
TEST(StackTest, NonConstPopMethod) {
    const Stack<int> stack;
    // コンパイルエラーになるためコメントアウト
    // stack.Pop();
}
#endif
