#include <gtest/gtest.h>
#include "SQ.h"

// Stack tests
// テスト0: リストが空である場合の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: スタックが空の場合、データ数が0であることを確認する。
// 補足:
TEST(StackTest, EmptyListSize) {
    Stack<int> stack;
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト1: 要素をプッシュした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
// 意図する結果: 要素を1つプッシュした後、データ数が1になることを確認する。
// 補足:
TEST(StackTest, PushOneElement) {
    Stack<int> stack;
    stack.Push(1);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト2: 要素をポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: 要素を1つポップした後、データ数が0になることを確認する。
// 補足:
TEST(StackTest, PopOneElement) {
    Stack<int> stack;
    stack.Push(1);
    stack.Pop();
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト3: 要素のプッシュに失敗した後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: プッシュが失敗した場合、データ数が変わらないことを確認する。
// 補足:
TEST(StackTest, PushFail) {
    Stack<int> stack;
    // simulate push failure if any specific condition is met
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト4: プッシュを2回行った後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 2
// 意図する結果: 要素を2つプッシュした後、データ数が2になることを確認する。
// 補足:
TEST(StackTest, PushTwoElements) {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    EXPECT_EQ(stack.GetSize(), 2);
}

// テスト5: プッシュを2回行った後、１回ポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
// 意図する結果: 2回プッシュして1回ポップした後、データ数が1になることを確認する。
// 補足:
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
// 意図する結果: 空のリストでポップを試みた後、データ数が0のままであることを確認する。
// 補足:
TEST(StackTest, PopEmptyList) {
    Stack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト7: constのメソッドであるか
// インターフェース:データ数の取得
// 想定する戻り値: 
// 意図する結果: constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
// 補足:
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
// 補足:
TEST(StackTest, PushToEmptyList) {
    Stack<int> stack;
    EXPECT_NO_THROW(stack.Push(1));
}

// テスト9: リストに複数の要素がある場合に、プッシュした際の挙動
// インターフェース:プッシュ
// 想定する戻り値: TRUE
// 意図する結果: リストの末尾に要素が追加される
// 補足:
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
// 補足:
TEST(StackTest, PopFromEmptyList) {
    Stack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

// テスト12: リストに複数の要素がある場合に、ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: TRUE
// 意図する結果: 末尾要素が引数経由で渡され、その要素がリストから削除される
// 補足:
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

// Queue tests
// テスト0: リストが空である場合の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: キューが空の場合、データ数が0であることを確認する。
// 補足:
TEST(QueueTest, EmptyListSize) {
    Queue<int> queue;
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト1: 要素をプッシュした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
// 意図する結果: 要素を1つプッシュした後、データ数が1になることを確認する。
// 補足:
TEST(QueueTest, PushOneElement) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト2: 要素をポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: 要素を1つポップした後、データ数が0になることを確認する。
// 補足:
TEST(QueueTest, PopOneElement) {
    Queue<int> queue;
    queue.Push(10);
    queue.Pop();
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト3: 要素のプッシュに失敗した後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: プッシュが失敗した場合、データ数が変わらないことを確認する。
// 補足:
TEST(QueueTest, PushFail) {
    Queue<int> queue;
    // simulate push failure if any specific condition is met
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト4: プッシュを2回行った後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 2
// 意図する結果: 要素を2つプッシュした後、データ数が2になることを確認する。
// 補足:
TEST(QueueTest, PushTwoElements) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    EXPECT_EQ(queue.GetSize(), 2);
}

// テスト5: プッシュを2回行った後、１回ポップした後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 1
// 意図する結果: 2回プッシュして1回ポップした後、データ数が1になることを確認する。
// 補足:
TEST(QueueTest, PushTwoPopOneElement) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Pop();
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト6: リストが空である場合に、ポップを行った後の戻り値
// インターフェース:データ数の取得
// 想定する戻り値: 0
// 意図する結果: 空のリストでポップを試みた後、データ数が0のままであることを確認する。
// 補足:
TEST(QueueTest, PopEmptyList) {
    Queue<int> queue;
    EXPECT_THROW(queue.Pop(), std::out_of_range);
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト7: constのメソッドであるか
// インターフェース:データ数の取得
// 想定する戻り値: 
// 意図する結果: constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
// 補足:
#ifndef SKIP_TEST7
TEST(QueueTest, ConstMethod) {
    const Queue<int> queue;
    EXPECT_NO_THROW(queue.GetSize());
}
#endif

// テスト8: リストが空である場合に、プッシュした際の挙動
// インターフェース:プッシュ
// 想定する戻り値: TRUE
// 意図する結果:リストの末尾に要素が追加される
// 補足:
TEST(QueueTest, PushToEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト9: リストに複数の要素がある場合に、プッシュした際の挙動
// インターフェース:プッシュ
// 想定する戻り値: TRUE
// 意図する結果: リストの末尾に要素が追加される
// 補足:
TEST(QueueTest, PushToNonEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_NO_THROW(queue.Push(20));
}

// テスト10: 非constのメソッドであるか
// インターフェース:プッシュ
// 想定する戻り値: 
// 意図する結果: 
// 補足: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
#ifndef SKIP_TEST10
TEST(QueueTest, NonConstPushMethod) {
    const Queue<int> queue;
    // コンパイルエラーになるためコメントアウト
    //queue.Push(10);
}
#endif

// テスト11: リストが空である場合に、ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: FALSE
// 意図する結果: 何も起こらない
// 補足:
TEST(QueueTest, PopFromEmptyList) {
    Queue<int> queue;
    EXPECT_THROW(queue.Pop(), std::out_of_range);
}

// テスト12: リストに複数の要素がある場合に、ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: TRUE
// 意図する結果: 末尾要素が引数経由で渡され、その要素がリストから削除される
// 補足:
TEST(QueueTest, PopFromNonEmptyList) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    int data = queue.Pop();
    EXPECT_EQ(data, 10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト13: リストに複数の要素がある場合に、複数回ポップした際の挙動
// インターフェース:ポップ
// 想定する戻り値: TRUE
// 意図する結果: 最後に追加した要素から順に引数経由で渡される
// 補足:追加した順の逆順に取り出されるかチェックし、リストが空になるまで取り出す。
TEST(QueueTest, PopMultiple) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    EXPECT_NO_THROW({
        EXPECT_EQ(queue.Pop(), 10);
        EXPECT_EQ(queue.Pop(), 20);
        EXPECT_EQ(queue.Pop(), 30);
        });
}

// テスト14: 非constのメソッドであるか
// インターフェース:ポップ
// 想定する戻り値: 
// 意図する結果:
// 補足: constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
#ifndef SKIP_TEST14
TEST(QueueTest, NonConstPopMethod) {
    const Queue<int> queue;
    // コンパイルエラーになるためコメントアウト
    // queue.Pop();
}
#endif
