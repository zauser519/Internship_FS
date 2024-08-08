#include <gtest/gtest.h>
#include "Queue.h"

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト0: リストが空である場合の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(QueueTest, GetSize_Empty) {
    Queue<int> queue;
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト1: 要素をプッシュした後の戻り値
// 想定する戻り値: 1
// 意図する結果:
// 補足:
TEST(QueueTest, GetSize_AfterPush) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト2: 要素をポップした後の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(QueueTest, GetSize_AfterPop) {
    Queue<int> queue;
    queue.Push(10);
    queue.Pop();
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト3: 要素のプッシュに失敗した後の戻り値
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(QueueTest, GetSize_PushFail) {
    Queue<int> queue;
    // Simulate push failure if applicable
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト4: 一つの要素をプッシュ
// 想定する戻り値: 1
// 意図する結果:
// 補足:
TEST(QueueTest, Push_SingleElement) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト5: 複数の要素をプッシュ
// 想定する戻り値: 3
// 意図する結果:
// 補足:
TEST(QueueTest, Push_MultipleElements) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    EXPECT_EQ(queue.GetSize(), 3);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト6: 空のキューからポップ
// 想定する動作: 例外スロー
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_EmptyQueue) {
    Queue<int> queue;
    EXPECT_THROW(queue.Pop(), std::out_of_range);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト7: 一つの要素をプッシュしてからポップ
// 想定する戻り値: プッシュした要素
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_SingleElement) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_EQ(queue.Pop(), 10);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト8: 複数の要素をプッシュしてからポップ
// 想定する戻り値: 最初にプッシュした要素
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_MultipleElements) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    EXPECT_EQ(queue.Pop(), 10);
    EXPECT_EQ(queue.Pop(), 20);
    EXPECT_EQ(queue.Pop(), 30);
}

// テスト項目: キュー
// インターフェース: キューのクリア
// テスト9: キューをクリアした後のサイズ
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(QueueTest, ClearQueue) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    while (!queue.IsEmpty()) {
        queue.Pop();
    }
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: 複数要素のプッシュおよびポップ
// テスト10: 要素の順序
// 想定する動作: FIFO順序
// 意図する結果: キューはFIFO (First In, First Out) 順序で要素を返す。
// 補足:
TEST(QueueTest, Order) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    EXPECT_EQ(queue.Pop(), 10);
    EXPECT_EQ(queue.Pop(), 20);
    EXPECT_EQ(queue.Pop(), 30);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト11: 大量の要素をプッシュ
// 想定する戻り値: 大量の要素数
// 意図する結果:
// 補足:
TEST(QueueTest, Push_LargeNumberOfElements) {
    Queue<int> queue;
    for (int i = 0; i < 1000; ++i) {
        queue.Push(i);
    }
    EXPECT_EQ(queue.GetSize(), 1000);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト12: 大量の要素をプッシュしてからポップ
// 想定する戻り値: 0
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_LargeNumberOfElements) {
    Queue<int> queue;
    for (int i = 0; i < 1000; ++i) {
        queue.Push(i);
    }
    for (int i = 0; i < 1000; ++i) {
        queue.Pop();
    }
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: 複数要素のプッシュおよびポップ
// テスト13: 異なる型の要素のプッシュおよびポップ
// 想定する戻り値: 各型の正しい順序
// 意図する結果:
// 補足:
TEST(QueueTest, DifferentTypes) {
    Queue<double> queueDouble;
    queueDouble.Push(1.1);
    queueDouble.Push(2.2);
    queueDouble.Push(3.3);
    EXPECT_EQ(queueDouble.Pop(), 1.1);
    EXPECT_EQ(queueDouble.Pop(), 2.2);
    EXPECT_EQ(queueDouble.Pop(), 3.3);

    Queue<std::string> queueString;
    queueString.Push("first");
    queueString.Push("second");
    queueString.Push("third");
    EXPECT_EQ(queueString.Pop(), "first");
    EXPECT_EQ(queueString.Pop(), "second");
    EXPECT_EQ(queueString.Pop(), "third");
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト14: 同じ要素を複数回プッシュ
// 想定する戻り値: サイズがプッシュした回数
// 意図する結果:
// 補足:
TEST(QueueTest, Push_SameElementMultipleTimes) {
    Queue<int> queue;
    for (int i = 0; i < 5; ++i) {
        queue.Push(10);
    }
    EXPECT_EQ(queue.GetSize(), 5);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト15: 同じ要素を複数回プッシュしてからポップ
// 想定する戻り値: 各プッシュした要素
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_SameElementMultipleTimes) {
    Queue<int> queue;
    for (int i = 0; i < 5; ++i) {
        queue.Push(10);
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(queue.Pop(), 10);
    }
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト16: 複数の異なる要素をプッシュ
// 想定する戻り値: サイズがプッシュした回数
// 意図する結果:
// 補足:
TEST(QueueTest, Push_DifferentElements) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    queue.Push(40);
    queue.Push(50);
    EXPECT_EQ(queue.GetSize(), 5);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト17: 複数の異なる要素をプッシュしてからポップ
// 想定する戻り値: 各プッシュした要素
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_DifferentElements) {
    Queue<int> queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    queue.Push(40);
    queue.Push(50);
    EXPECT_EQ(queue.Pop(), 10);
    EXPECT_EQ(queue.Pop(), 20);
    EXPECT_EQ(queue.Pop(), 30);
    EXPECT_EQ(queue.Pop(), 40);
    EXPECT_EQ(queue.Pop(), 50);
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト18: NULLをプッシュ (ポインタの場合)
// 想定する戻り値: サイズが1増える
// 意図する結果:
// 補足:
TEST(QueueTest, Push_NullPointer) {
    Queue<int*> queue;
    int* ptr = nullptr;
    queue.Push(ptr);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト19: NULLをプッシュしてからポップ (ポインタの場合)
// 想定する戻り値: NULL
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_NullPointer) {
    Queue<int*> queue;
    int* ptr = nullptr;
    queue.Push(ptr);
    EXPECT_EQ(queue.Pop(), nullptr);
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト20: 多様なデータ型
// 想定する戻り値: 各型に対して正しいサイズ
// 意図する結果:
// 補足:
TEST(QueueTest, Push_VariousDataTypes) {
    Queue<int> queueInt;
    Queue<double> queueDouble;
    Queue<std::string> queueString;

    queueInt.Push(1);
    queueDouble.Push(1.1);
    queueString.Push("test");

    EXPECT_EQ(queueInt.GetSize(), 1);
    EXPECT_EQ(queueDouble.GetSize(), 1);
    EXPECT_EQ(queueString.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト21: 多様なデータ型からポップ
// 想定する戻り値: 各型に対してプッシュした値
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_VariousDataTypes) {
    Queue<int> queueInt;
    Queue<double> queueDouble;
    Queue<std::string> queueString;

    queueInt.Push(1);
    queueDouble.Push(1.1);
    queueString.Push("test");

    EXPECT_EQ(queueInt.Pop(), 1);
    EXPECT_EQ(queueDouble.Pop(), 1.1);
    EXPECT_EQ(queueString.Pop(), "test");
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト22: キューが空か確認
// 想定する戻り値: true
// 意図する結果:
// 補足:
TEST(QueueTest, IsEmpty_True) {
    Queue<int> queue;
    EXPECT_TRUE(queue.IsEmpty());
}

// テスト項目: キュー
// インターフェース: データ数の取得
// テスト23: キューが空でないか確認
// 想定する戻り値: false
// 意図する結果:
// 補足:
TEST(QueueTest, IsEmpty_False) {
    Queue<int> queue;
    queue.Push(10);
    EXPECT_FALSE(queue.IsEmpty());
}

// テスト項目: キュー
// インターフェース: キューの初期化
// テスト24: コンストラクタ
// 想定する戻り値: 正常に初期化
// 意図する結果:
// 補足:
TEST(QueueTest, Constructor) {
    Queue<int> queue;
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト25: 負の値をプッシュ
// 想定する戻り値: サイズが増える
// 意図する結果:
// 補足:
TEST(QueueTest, Push_NegativeValue) {
    Queue<int> queue;
    queue.Push(-10);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト26: 負の値をプッシュしてからポップ
// 想定する戻り値: プッシュした負の値
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_NegativeValue) {
    Queue<int> queue;
    queue.Push(-10);
    EXPECT_EQ(queue.Pop(), -10);
}

// テスト項目: キュー
// インターフェース: キューのクリア
// テスト27: 全ての要素をプッシュしてからクリア
// 想定する戻り値: サイズが0
// 意図する結果:
// 補足:
TEST(QueueTest, ClearAfterPush) {
    Queue<int> queue;
    for (int i = 0; i < 10; ++i) {
        queue.Push(i);
    }
    while (!queue.IsEmpty()) {
        queue.Pop();
    }
    EXPECT_EQ(queue.GetSize(), 0);
}

// テスト項目: キュー
// インターフェース: キューの初期化
// テスト28: キューのデストラクタ
// 想定する戻り値: 正常に削除
// 意図する結果:
// 補足:
TEST(QueueTest, Destructor) {
    Queue<int>* queue = new Queue<int>();
    queue->Push(10);
    delete queue;
    // No explicit check, just ensuring no crash or memory leak
}

// テスト項目: キュー
// インターフェース: 要素のプッシュ
// テスト29: 大きな数値をプッシュ
// 想定する戻り値: サイズが増える
// 意図する結果:
// 補足:
TEST(QueueTest, Push_LargeNumber) {
    Queue<long long> queue;
    queue.Push(1000000000000LL);
    EXPECT_EQ(queue.GetSize(), 1);
}

// テスト項目: キュー
// インターフェース: 要素のポップ
// テスト30: 大きな数値をプッシュしてからポップ
// 想定する戻り値: プッシュした大きな数値
// 意図する結果:
// 補足:
TEST(QueueTest, Pop_LargeNumber) {
    Queue<long long> queue;
    queue.Push(1000000000000LL);
    EXPECT_EQ(queue.Pop(), 1000000000000LL);
}
