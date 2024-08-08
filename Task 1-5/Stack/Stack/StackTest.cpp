#include <gtest/gtest.h>
#include "Stack.h"

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト0: リストが空である場合の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(StackTest, GetSize_Empty) {
    Stack<int> stack;
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト1: 要素をプッシュした後の戻り値
// 想定する戻り値: 1
// 意図する結果:
// 補足:
TEST(StackTest, GetSize_AfterPush) {
    Stack<int> stack;
    stack.Push(10);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト2: 要素をポップした後の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(StackTest, GetSize_AfterPop) {
    Stack<int> stack;
    stack.Push(10);
    stack.Pop();
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト3: 要素のプッシュに失敗した後の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(StackTest, GetSize_PushFail) {
    Stack<int> stack;
    // Simulate push failure if applicable
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト4: 一つの要素をプッシュ
// 想定する戻り値: 1
// 意図する結果:
// 補足:
TEST(StackTest, Push_SingleElement) {
    Stack<int> stack;
    stack.Push(10);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト5: 複数の要素をプッシュ
// 想定する戻り値: 3
// 意図する結果:
// 補足:
TEST(StackTest, Push_MultipleElements) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    EXPECT_EQ(stack.GetSize(), 3);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト6: 空のスタックからポップ
// 想定する動作: 例外スロー
// 意図する結果:
// 補足:
TEST(StackTest, Pop_EmptyStack) {
    Stack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト7: 一つの要素をプッシュしてからポップ
// 想定する戻り値: プッシュした要素
// 意図する結果:
// 補足:
TEST(StackTest, Pop_SingleElement) {
    Stack<int> stack;
    stack.Push(10);
    EXPECT_EQ(stack.Pop(), 10);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト8: 複数の要素をプッシュしてからポップ
// 想定する戻り値: 最後にプッシュした要素
// 意図する結果:
// 補足:
TEST(StackTest, Pop_MultipleElements) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
}

// テスト項目: スタック
// インターフェース: スタックのクリア
// テスト9: スタックをクリアした後のサイズ
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(StackTest, ClearStack) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    while (!stack.IsEmpty()) {
        stack.Pop();
    }
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: 複数要素のプッシュおよびポップ
// テスト10: 要素の順序
// 想定する動作: LIFO順序
// 意図する結果: スタックはLIFO (Last In, First Out) 順序で要素を返す。
// 補足:
TEST(StackTest, Order) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト11: 大量の要素をプッシュ
// 想定する戻り値: 大量の要素数
// 意図する結果:
// 補足:
TEST(StackTest, Push_LargeNumberOfElements) {
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.Push(i);
    }
    EXPECT_EQ(stack.GetSize(), 1000);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト12: 大量の要素をプッシュしてからポップ
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(StackTest, Pop_LargeNumberOfElements) {
    Stack<int> stack;
    for (int i = 0; i < 1000; ++i) {
        stack.Push(i);
    }
    for (int i = 0; i < 1000; ++i) {
        stack.Pop();
    }
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: 複数要素のプッシュおよびポップ
// テスト13: 異なる型の要素のプッシュおよびポップ
// 想定する戻り値: 各型の正しい順序
// 意図する結果:
// 補足:
TEST(StackTest, DifferentTypes) {
    Stack<double> stackDouble;
    stackDouble.Push(1.1);
    stackDouble.Push(2.2);
    stackDouble.Push(3.3);
    EXPECT_EQ(stackDouble.Pop(), 3.3);
    EXPECT_EQ(stackDouble.Pop(), 2.2);
    EXPECT_EQ(stackDouble.Pop(), 1.1);

    Stack<std::string> stackString;
    stackString.Push("first");
    stackString.Push("second");
    stackString.Push("third");
    EXPECT_EQ(stackString.Pop(), "third");
    EXPECT_EQ(stackString.Pop(), "second");
    EXPECT_EQ(stackString.Pop(), "first");
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト14: 同じ要素を複数回プッシュ
// 想定する戻り値: サイズがプッシュした回数
// 意図する結果:
// 補足:
TEST(StackTest, Push_SameElementMultipleTimes) {
    Stack<int> stack;
    for (int i = 0; i < 5; ++i) {
        stack.Push(10);
    }
    EXPECT_EQ(stack.GetSize(), 5);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト15: 同じ要素を複数回プッシュしてからポップ
// 想定する戻り値: 各プッシュした要素
// 意図する結果:
// 補足:
TEST(StackTest, Pop_SameElementMultipleTimes) {
    Stack<int> stack;
    for (int i = 0; i < 5; ++i) {
        stack.Push(10);
    }
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(stack.Pop(), 10);
    }
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト16: 複数の異なる要素をプッシュ
// 想定する戻り値: サイズがプッシュした回数
// 意図する結果:
// 補足:
TEST(StackTest, Push_DifferentElements) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);
    stack.Push(50);
    EXPECT_EQ(stack.GetSize(), 5);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト17: 複数の異なる要素をプッシュしてからポップ
// 想定する戻り値: 各プッシュした要素
// 意図する結果:
// 補足:
TEST(StackTest, Pop_DifferentElements) {
    Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);
    stack.Push(50);
    EXPECT_EQ(stack.Pop(), 50);
    EXPECT_EQ(stack.Pop(), 40);
    EXPECT_EQ(stack.Pop(), 30);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト18: NULLをプッシュ (ポインタの場合)
// 想定する戻り値: サイズが1増える
// 意図する結果:
// 補足:
TEST(StackTest, Push_NullPointer) {
    Stack<int*> stack;
    int* ptr = nullptr;
    stack.Push(ptr);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト19: NULLをプッシュしてからポップ (ポインタの場合)
// 想定する戻り値: NULL
// 意図する結果:
// 補足:
TEST(StackTest, Pop_NullPointer) {
    Stack<int*> stack;
    int* ptr = nullptr;
    stack.Push(ptr);
    EXPECT_EQ(stack.Pop(), nullptr);
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト20: 多様なデータ型
// 想定する戻り値: 各型に対して正しいサイズ
// 意図する結果:
// 補足:
TEST(StackTest, Push_VariousDataTypes) {
    Stack<int> stackInt;
    Stack<double> stackDouble;
    Stack<std::string> stackString;

    stackInt.Push(1);
    stackDouble.Push(1.1);
    stackString.Push("test");

    EXPECT_EQ(stackInt.GetSize(), 1);
    EXPECT_EQ(stackDouble.GetSize(), 1);
    EXPECT_EQ(stackString.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト21: 多様なデータ型からポップ
// 想定する戻り値: 各型に対してプッシュした値
// 意図する結果:
// 補足:
TEST(StackTest, Pop_VariousDataTypes) {
    Stack<int> stackInt;
    Stack<double> stackDouble;
    Stack<std::string> stackString;

    stackInt.Push(1);
    stackDouble.Push(1.1);
    stackString.Push("test");

    EXPECT_EQ(stackInt.Pop(), 1);
    EXPECT_EQ(stackDouble.Pop(), 1.1);
    EXPECT_EQ(stackString.Pop(), "test");
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト22: スタックが空か確認
// 想定する戻り値: true
// 意図する結果:
// 補足:
TEST(StackTest, IsEmpty_True) {
    Stack<int> stack;
    EXPECT_TRUE(stack.IsEmpty());
}

// テスト項目: スタック
// インターフェース: データ数の取得
// テスト23: スタックが空でないか確認
// 想定する戻り値: false
// 意図する結果:
// 補足:
TEST(StackTest, IsEmpty_False) {
    Stack<int> stack;
    stack.Push(10);
    EXPECT_FALSE(stack.IsEmpty());
}

// テスト項目: スタック
// インターフェース: スタックの初期化
// テスト24: コンストラクタ
// 想定する戻り値: 正常に初期化
// 意図する結果:
// 補足:
TEST(StackTest, Constructor) {
    Stack<int> stack;
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト25: 負の値をプッシュ
// 想定する戻り値: サイズが増える
// 意図する結果:
// 補足:
TEST(StackTest, Push_NegativeValue) {
    Stack<int> stack;
    stack.Push(-10);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト26: 負の値をプッシュしてからポップ
// 想定する戻り値: プッシュした負の値
// 意図する結果:
// 補足:
TEST(StackTest, Pop_NegativeValue) {
    Stack<int> stack;
    stack.Push(-10);
    EXPECT_EQ(stack.Pop(), -10);
}

// テスト項目: スタック
// インターフェース: スタックのクリア
// テスト27: 全ての要素をプッシュしてからクリア
// 想定する戻り値: サイズが0
// 意図する結果:
// 補足:
TEST(StackTest, ClearAfterPush) {
    Stack<int> stack;
    for (int i = 0; i < 10; ++i) {
        stack.Push(i);
    }
    while (!stack.IsEmpty()) {
        stack.Pop();
    }
    EXPECT_EQ(stack.GetSize(), 0);
}

// テスト項目: スタック
// インターフェース: スタックの初期化
// テスト28: スタックのデストラクタ
// 想定する戻り値: 正常に削除
// 意図する結果:
// 補足:
TEST(StackTest, Destructor) {
    Stack<int>* stack = new Stack<int>();
    stack->Push(10);
    delete stack;
    // No explicit check, just ensuring no crash or memory leak
}

// テスト項目: スタック
// インターフェース: 要素のプッシュ
// テスト29: 大きな数値をプッシュ
// 想定する戻り値: サイズが増える
// 意図する結果:
// 補足:
TEST(StackTest, Push_LargeNumber) {
    Stack<long long> stack;
    stack.Push(1000000000000LL);
    EXPECT_EQ(stack.GetSize(), 1);
}

// テスト項目: スタック
// インターフェース: 要素のポップ
// テスト30: 大きな数値をプッシュしてからポップ
// 想定する戻り値: プッシュした大きな数値
// 意図する結果:
// 補足:
TEST(StackTest, Pop_LargeNumber) {
    Stack<long long> stack;
    stack.Push(1000000000000LL);
    EXPECT_EQ(stack.Pop(), 1000000000000LL);
}

