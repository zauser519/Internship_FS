#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "Sort.h"

using PerformanceData = std::pair<int, std::string>;

// スコアを昇順で比較するための関数
inline bool SA(const PerformanceData& a, const PerformanceData& b) {
    return a.first < b.first;
}

// スコアを降順で比較するための関数
inline bool SD(const PerformanceData& a, const PerformanceData& b) {
    return a.first > b.first;
}

// 名前を昇順で比較するための関数
inline bool NameA(const PerformanceData& a, const PerformanceData& b) {
    return a.second < b.second;
}

// 名前を降順で比較するための関数
inline bool NameD(const PerformanceData& a, const PerformanceData& b) {
    return a.second > b.second;
}

// 無効な比較関数
bool compareInvalid(const std::string& a, const std::string& b) {
    return a < b;
}

// リストが空の場合のテスト
// 期待結果: ソート後もリストのサイズが0であること
TEST(SortTest, TestifEmpty) {
    DoublyLinkedList<PerformanceData> list;
    list.Sort(SA);
    EXPECT_EQ(0, list.Getsize());

    list.Sort(SD);
    EXPECT_EQ(0, list.Getsize());

    list.Sort(NameA);
    EXPECT_EQ(0, list.Getsize());

    list.Sort(NameD);
    EXPECT_EQ(0, list.Getsize());
}

// リストに一つの要素がある場合のテスト
// 期待結果: ソート後もリストのサイズが1であり、要素が変わらないこと
TEST(SortTest, TestSingleElement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it = list.begin();

    list.Sort(SA);
    EXPECT_EQ(1, list.Getsize());
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);

    list.Sort(SD);
    EXPECT_EQ(1, list.Getsize());
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);

    list.Sort(NameA);
    EXPECT_EQ(1, list.Getsize());
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);

    list.Sort(NameD);
    EXPECT_EQ(1, list.Getsize());
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// リストに複数の要素がある場合のテスト
// 期待結果: ソート後、リストが正しくソートされていること
TEST(SortTest, TestMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);

    auto it = list.begin();
    list.Sort(SA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(SD);
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);

    it = list.begin();
    list.Sort(NameA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(NameD);
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// 同じキーを持つ要素のテスト
// 期待結果: ソート後もリストの順序が正しいこと
TEST(SortTest, TestSameKey) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 10, "User1" }; // 同じキー
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);

    auto it = list.begin();
    list.Sort(SA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(SD);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(NameA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(NameD);
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}


// リストのソートテスト
// 期待結果: リストを再度ソートしても順序が維持されること
TEST(SortTest, TestList) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);

    auto it = list.begin();
    list.Sort(SA);
    list.Sort(SA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(SD);
    list.Sort(SD);
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);

    it = list.begin();
    list.Sort(NameA);
    list.Sort(NameA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    it = list.begin();
    list.Sort(NameD);
    list.Sort(NameD);
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// リストの再ソートテスト
// 期待結果: リストを再度ソートしても順序が正しく維持されること
// 読みやすいように4つのテストに分ける
//　リスト1を昇順にソートし、要素を挿入するテスト
TEST(SortTest, SortList1AscendingAndInsert) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    PerformanceData data2 = { 30, "User2" };
    list1.Insert(list1.end(), data);
    list1.Insert(list1.end(), data1);

    list1.Sort(SA);
    list1.Insert(list1.begin(), data2);

    auto it = list1.begin();
    list1.Sort(SA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// リスト2 を降順でソートし、要素を挿入するテスト
TEST(SortTest, SortList2DescendingAndInsert) {
    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    PerformanceData data2 = { 30, "User2" };
    list2.Insert(list2.end(), data);
    list2.Insert(list2.end(), data1);

    list2.Sort(SD);
    list2.Insert(list2.begin(), data2);

    auto it = list2.begin();
    list2.Sort(SD);
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// リスト3を名前の昇順でソートし、要素を挿入するテスト
TEST(SortTest, SortList3NameAscendingAndInsert) {
    DoublyLinkedList<PerformanceData> list3;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    PerformanceData data2 = { 30, "User2" };
    list3.Insert(list3.end(), data);
    list3.Insert(list3.end(), data1);

    list3.Sort(NameA);
    list3.Insert(list3.begin(), data2);

    auto it = list3.begin();
    list3.Sort(NameA);
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// list4 を名前の降順でソートし、要素を挿入するテスト
TEST(SortTest, SortList4NameDescendingAndInsert) {
    DoublyLinkedList<PerformanceData> list4;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    PerformanceData data2 = { 30, "User2" };
    list4.Insert(list4.end(), data);
    list4.Insert(list4.end(), data1);

    list4.Sort(NameD);
    list4.Insert(list4.begin(), data2);

    auto it = list4.begin();
    list4.Sort(NameD);
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
    ++it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}


// 無効な比較関数のテスト
// 期待結果: ソートが実行されず、リストが変更されないこと
TEST(SortTest, TestNullKey) {
    DoublyLinkedList<PerformanceData> list;

    // ソートされていない順序でデータを挿入する
    PerformanceData data = { 20, "User1" };
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);

    // リストの初期状態をキャプチャする
    auto it = list.begin();
    PerformanceData initialFirst = *it;
    ++it;
    PerformanceData initialSecond = *it;

    // null比較器を使用してソートする
    list.Sort(nullptr);

    // リストが変更されていないことを確認する
    it = list.begin();
    EXPECT_EQ(initialFirst.first, (*it).first);
    EXPECT_EQ(initialFirst.second, (*it).second);
    ++it;
    EXPECT_EQ(initialSecond.first, (*it).first);
    EXPECT_EQ(initialSecond.second, (*it).second);
}


// 無効な比較関数のテスト (無効な比較関数がコメントアウトされている場合)
// 期待結果: テストがスキップされること
TEST(SortTest, TestInvalid) {
#if defined SKIP_TEST
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);
    auto it = list.begin();
    list.Sort(compareInvalid);
#endif //SKIP_TEST
    SUCCEED();
}

// 定数リストのソートテスト (定数リストのためスキップされる場合)
// 期待結果: テストがスキップされること
TEST(SortTest, TestConst) {
#if defined SKIP_TEST
    const DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    PerformanceData data1 = { 20, "User1" };
    list.Insert(list.end(), data);
    list.Insert(list.end(), data1);
    list.Sort(SA);
#endif //SKIP_TEST
    SUCCEED();
}
