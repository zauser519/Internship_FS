#include "gtest/gtest.h"
#include "DLL.h"
#include <utility>
#include <string>

using PerformanceData = std::pair<int, std::string>;

// GetSize 関数のテスト: リストが空の場合
// 期待結果: リストのサイズが 0 であることを確認
TEST(GetSizeTest, TestGetSizeWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    EXPECT_EQ(0, list.GetSize());
}

// GetSize 関数のテスト: 末尾に挿入した後
// 期待結果: リストのサイズが 1 であることを確認
TEST(GetSizeTest, TestGetSizeAfterInsertAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    EXPECT_EQ(1, list.GetSize());
}

// GetSize 関数のテスト: 挿入が失敗した場合
// 期待結果: リストのサイズが変わらないことを確認
TEST(GetSizeTest, TestGetSizeAfterPushFailed) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1 = { 10, "User" };
    list1.Insert(list1.end(), data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2 = { 20, "User1" };
    list2.Insert(list2.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list2.end();
    PerformanceData data3 = { 30, "User2" };
    list1.Insert(it, data3);

    EXPECT_EQ(1, list1.GetSize());
}

// GetSize 関数のテスト: 先頭に挿入した後
// 期待結果: リストのサイズが 1 であることを確認
TEST(GetSizeTest, TestGetSizeAfterInsert) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.begin(), data);
    EXPECT_EQ(1, list.GetSize());
}

// GetSize 関数のテスト: 挿入が失敗した場合
// 期待結果: リストのサイズが変わらないことを確認
TEST(GetSizeTest, TestGetSizeAfterInsertFailed) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1 = { 10, "User" };
    list1.Insert(list1.end(), data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2 = { 20, "User1" };
    list2.Insert(list2.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list2.begin();
    PerformanceData data3 = { 30, "User2" };
    list1.Insert(it, data3);

    EXPECT_EQ(1, list1.GetSize());
}

// GetSize 関数のテスト: 削除した後
// 期待結果: リストのサイズが 0 であることを確認
TEST(GetSizeTest, TestGetSizeAfterDelete) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    list.Delete(list.begin());
    EXPECT_EQ(0, list.GetSize());
}

// GetSize 関数のテスト: 削除が失敗した場合
// 期待結果: リストのサイズが変わらないことを確認
TEST(GetSizeTest, TestGetSizeAfterDeleteFailed) {
    DoublyLinkedList<PerformanceData> list;
    list.Delete(list.begin());
    EXPECT_EQ(0, list.GetSize());
}

// GetSize 関数のテスト: 空のリストから削除した場合
// 期待結果: リストのサイズが変わらないことを確認
TEST(GetSizeTest, TestGetSizeWhenDeleteEmpty) {
    DoublyLinkedList<PerformanceData> list;
    list.Delete(list.begin());
    EXPECT_EQ(0, list.GetSize());
}

// GetSize 関数のテスト: const の場合
// 期待結果: リストのサイズが 0 であることを確認
TEST(GetSizeTest, TestGetSizeWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    EXPECT_EQ(0, list.GetSize());
#endif 
    SUCCEED();
}

// Insert 関数のテスト: 空のリストに挿入
// 期待結果: 挿入に成功し、true を返すことを確認
TEST(InsertTest, TestInsertToEmpty) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    bool successBegin = list.Insert(list.begin(), data);
    bool successEnd = list.Insert(list.end(), data);
    EXPECT_TRUE(successBegin);
    EXPECT_TRUE(successEnd);
}

// Insert 関数のテスト: 先頭に挿入
// 期待結果: 挿入に成功し、true を返すことを確認
TEST(InsertTest, TestInsertAtBegin) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    bool success = list.Insert(list.begin(), data2);
    EXPECT_TRUE(success);
}

// Insert 関数のテスト: 末尾に挿入
// 期待結果: 挿入に成功し、true を返すことを確認
TEST(InsertTest, TestInsertAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    bool success = list.Insert(list.end(), data2);
    EXPECT_TRUE(success);
}

// Insert 関数のテスト: 指定位置に挿入
// 期待結果: 挿入に成功し、true を返すことを確認
TEST(InsertTest, TestInsert) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    ++it;

    PerformanceData data3 = { 30, "User2" };
    bool success = list.Insert(it, data3);
    EXPECT_TRUE(success);

    it = list.begin();
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
    ++it;
    EXPECT_EQ(data3.first, (*it).first);
    EXPECT_EQ(data3.second, (*it).second);
    ++it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// Insert 関数のテスト: const イテレータで挿入
// 期待結果: 挿入に成功し、true を返すことを確認
TEST(InsertTest, TestInsertWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();

    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    PerformanceData data = { 10, "User" };
    bool success = list.Insert(it, data);
    EXPECT_TRUE(success);
}

// Insert 関数のテスト: 無効な位置に挿入
// 期待結果: 挿入に失敗し、false を返すことを確認
TEST(InsertTest, TestInsertInvalid) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1 = { 10, "User" };
    list1.Insert(list1.end(), data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2 = { 20, "User1" };
    list2.Insert(list2.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list2.begin();
    PerformanceData data3 = { 30, "User2" };
    bool success = list1.Insert(it, data3);
    EXPECT_TRUE(!success);
}

// const リストへの挿入テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestInsertWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
#endif 
    SUCCEED();
}

// Delete 関数のテスト: 空のリストから削除
// 期待結果: 削除に失敗し、false を返すことを確認
TEST(DeleteTest, TestDeleteFromEmpty) {
    DoublyLinkedList<PerformanceData> list;
    bool successBegin = list.Delete(list.begin());
    bool successEnd = list.Delete(list.end());
    EXPECT_TRUE(!successBegin);
    EXPECT_TRUE(!successEnd);
}

// Delete 関数のテスト: 先頭のノードを削除
// 期待結果: 削除に成功し、true を返すことを確認
TEST(DeleteTest, TestDeleteAtBegin) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    bool success = list.Delete(list.begin());
    EXPECT_TRUE(success);
}

// Delete 関数のテスト: 末尾のノードを削除
// 期待結果: 削除に失敗し、false を返すことを確認
TEST(DeleteTest, TestDeleteAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    bool success = list.Delete(list.end());
    EXPECT_TRUE(!success);
}

// Delete 関数のテスト: 指定位置のノードを削除
// 期待結果: 削除に成功し、true を返すことを確認
TEST(DeleteTest, TestDelete) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    ++it;

    bool success = list.Delete(it);
    EXPECT_TRUE(success);
}

// Delete 関数のテスト: const イテレータで削除
// 期待結果: 削除に成功し、true を返すことを確認
TEST(DeleteTest, TestDeleteWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);

    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();

    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();

    bool success = list.Delete(it);
    EXPECT_TRUE(success);
}

// Delete 関数のテスト: 無効な位置のノードを削除
// 期待結果: 削除に失敗し、false を返すことを確認
TEST(DeleteTest, TestDeleteInvalid) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1 = { 10, "User" };
    list1.Insert(list1.end(), data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2 = { 20, "User1" };
    list2.Insert(list2.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list2.begin();
    bool success = list1.Delete(it);
    EXPECT_TRUE(!success);
}

// const リストの削除テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestDeleteWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    list.Delete(list.end());
#endif 
    SUCCEED();
}

// イテレータの begin 関数テスト: リストが空の場合
// 期待結果: begin と end が等しいことを確認
TEST(BeginIteratorTest, TestBeginWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    EXPECT_EQ(it, list.end());
}

// イテレータの begin 関数テスト: リストに要素が一つの場合
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginWhenOneElement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// イテレータの begin 関数テスト: リストに複数の要素がある場合
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginWhenMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
}

// イテレータの begin 関数テスト: 挿入後
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginAfterInsert) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// イテレータの begin 関数テスト: 削除後
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginAfterDelete) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    list.Delete(list.begin());
    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// const イテレータの begin 関数テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestBeginWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::Iterator it = list.begin();
#endif 
    SUCCEED();
}

// const イテレータの begin 関数テスト: リストが空の場合
// 期待結果: begin と end が等しいことを確認
TEST(BeginIteratorTest, TestBeginWhenEmptyWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
    EXPECT_EQ(cit, list.end());
}

// const イテレータの begin 関数テスト: リストに要素が一つの場合
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginWhenOneElementWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
    EXPECT_EQ(data.first, (*cit).first);
    EXPECT_EQ(data.second, (*cit).second);
}

// const イテレータの begin 関数テスト: リストに複数の要素がある場合
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginWhenMultipleElementsWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
    EXPECT_EQ(data1.first, (*cit).first);
    EXPECT_EQ(data1.second, (*cit).second);
}

// const イテレータの begin 関数テスト: 挿入後
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginAfterInsertWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
    EXPECT_EQ(data.first, (*cit).first);
    EXPECT_EQ(data.second, (*cit).second);
}

// const イテレータの begin 関数テスト: 削除後
// 期待結果: 先頭のデータが正しいことを確認
TEST(BeginIteratorTest, TestBeginAfterDeleteWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    list.Delete(list.begin());
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
    EXPECT_EQ(data2.first, (*cit).first);
    EXPECT_EQ(data2.second, (*cit).second);
}

// const イテレータの begin 関数テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestBeginWhenConstWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.begin();
#endif 
    SUCCEED();
}

// イテレータの end 関数テスト: リストが空の場合
// 期待結果: end と begin が等しいことを確認
TEST(EndIteratorTest, TestEndWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
    EXPECT_EQ(it, list.begin());
}

// イテレータの end 関数テスト: リストに要素が一つの場合
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndWhenOneElement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
    --it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// イテレータの end 関数テスト: リストに複数の要素がある場合
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndWhenMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
    --it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// イテレータの end 関数テスト: 挿入後
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndAfterInsert) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
    --it;
    EXPECT_EQ(data.first, (*it).first);
    EXPECT_EQ(data.second, (*it).second);
}

// イテレータの end 関数テスト: 削除後
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndAfterDelete) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    list.Delete(list.begin());
    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
    --it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// const イテレータの end 関数テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestEndWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::Iterator it = list.end();
#endif 
    SUCCEED();
}

// const イテレータの end 関数テスト: リストが空の場合
// 期待結果: end と begin が等しいことを確認
TEST(EndIteratorTest, TestEndWhenEmptyWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
    EXPECT_EQ(cit, list.begin());
}

// const イテレータの end 関数テスト: リストに要素が一つの場合
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndWhenOneElementWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
    --cit;
    EXPECT_EQ(data.first, (*cit).first);
    EXPECT_EQ(data.second, (*cit).second);
}

// const イテレータの end 関数テスト: リストに複数の要素がある場合
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndWhenMultipleElementsWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
    --cit;
    EXPECT_EQ(data2.first, (*cit).first);
    EXPECT_EQ(data2.second, (*cit).second);
}

// const イテレータの end 関数テスト: 挿入後
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndAfterInsertWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
    --cit;
    EXPECT_EQ(data.first, (*cit).first);
    EXPECT_EQ(data.second, (*cit).second);
}

// const イテレータの end 関数テスト: 削除後
// 期待結果: 末尾のデータが正しいことを確認
TEST(EndIteratorTest, TestEndAfterDeleteWhenConst) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    list.Delete(list.begin());
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
    --cit;
    EXPECT_EQ(data2.first, (*cit).first);
    EXPECT_EQ(data2.second, (*cit).second);
}

// const イテレータの end 関数テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestEndWhenConstWhenConst) {
#if defined Macro
    const DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.end();
#endif 
    SUCCEED();
}

// イテレータのデリファレンス演算子テスト: 無効なイテレータの場合
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorDereferenceTest, TestDereferenceWhenInvalid) {
    DoublyLinkedList<PerformanceData>::ConstIterator it(nullptr, nullptr);
    ASSERT_DEATH(*it, ".*");
}

// イテレータの代入テスト
// 期待結果: イテレータが指すデータが変更されることを確認
TEST(IteratorDereferenceTest, TestIteratorAssignment) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it = list.begin();
    (*it).first = 40;
    (*it).second = "User3";
    EXPECT_EQ(40, (*it).first);
    EXPECT_EQ("User3", (*it).second);
}


// const イテレータの代入テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestIteratorAssignmentWhenConst) {
#if defined Macro
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.beginConst();
    (*it).first = 40;
    (*it).second = "User3";
#endif 
    SUCCEED();
}

// イテレータのデリファレンス演算子テスト: 空のリストの先頭
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorDereferenceTest, TestDereferenceAtBeginWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator it = list.begin();
    ASSERT_DEATH(*it, ".*");
}

// イテレータのデリファレンス演算子テスト: リストの末尾
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorDereferenceTest, TestDereferenceAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData>::ConstIterator it = list.end();
    ASSERT_DEATH(*it, ".*");
}

// イテレータのインクリメント演算子テスト: 無効なイテレータ
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestAdvanceWhenInvalid) {
    DoublyLinkedList<PerformanceData>::Iterator it(nullptr, nullptr);
    ASSERT_DEATH(++it, ".*");
}

// イテレータのインクリメント演算子テスト: 空のリスト
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestAdvanceWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    ASSERT_DEATH(++it, ".*");
}

// イテレータのインクリメント演算子テスト: リストの末尾
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestAdvanceAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it = list.end();
    ASSERT_DEATH(++it, ".*");
}

// イテレータのインクリメント演算子テスト: 複数の要素がある場合
// 期待結果: 次のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestAdvanceWhenMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it = list.begin();
    ++it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
}

// イテレータの前置インクリメント演算子テスト
// 期待結果: 次のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestPreIncrement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it = list.begin();
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    auto cit = ++it;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
    EXPECT_EQ(data2.first, (*cit).first);
    EXPECT_EQ(data2.second, (*cit).second);
}

// イテレータの後置インクリメント演算子テスト
// 期待結果: 次のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestPostIncrement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it = list.begin();
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);

    auto cit = it++;
    EXPECT_EQ(data2.first, (*it).first);
    EXPECT_EQ(data2.second, (*it).second);
    EXPECT_EQ(data1.first, (*cit).first);
    EXPECT_EQ(data1.second, (*cit).second);
}

// イテレータのデクリメント演算子テスト: 無効なイテレータ
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestBackwardWhenInvalid) {
    DoublyLinkedList<PerformanceData>::Iterator it(nullptr, nullptr);
    ASSERT_DEATH(--it, ".*");
}

// イテレータのデクリメント演算子テスト: 空のリストの末尾
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestBackwardFromEndWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.end();
    ASSERT_DEATH(--it, ".*");
}

// イテレータのデクリメント演算子テスト: リストの先頭
// 期待結果: プログラムが異常終了することを確認
TEST(IteratorAdvanceTest, TestBackwardFromBegin) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it = list.begin();
    ASSERT_DEATH(--it, ".*");
}

// イテレータのデクリメント演算子テスト: 複数の要素がある場合
// 期待結果: 前のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestBackwardWhenMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it = list.end();
    --it;
    --it;
    EXPECT_EQ(data1.first, (*it).first);
    EXPECT_EQ(data1.second, (*it).second);
}

// イテレータの前置デクリメント演算子テスト
// 期待結果: 前のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestPreDecrement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it1 = list.end();
    --it1;
    EXPECT_EQ(data2.first, (*it1).first);
    EXPECT_EQ(data2.second, (*it1).second);

    auto it2 = --it1;
    EXPECT_EQ(data1.first, (*it1).first);
    EXPECT_EQ(data1.second, (*it1).second);
    EXPECT_EQ(data1.first, (*it2).first);
    EXPECT_EQ(data1.second, (*it2).second);
}

// イテレータの後置デクリメント演算子テスト
// 期待結果: 前のノードに移動し、データが正しいことを確認
TEST(IteratorAdvanceTest, TestPostDecrement) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it1 = list.end();
    it1--;
    EXPECT_EQ(data2.first, (*it1).first);
    EXPECT_EQ(data2.second, (*it1).second);

    auto it2 = it1--;
    EXPECT_EQ(data1.first, (*it1).first);
    EXPECT_EQ(data1.second, (*it1).second);
    EXPECT_EQ(data2.first, (*it2).first);
    EXPECT_EQ(data2.second, (*it2).second);
}

// const リストのコピーコンストラクタテスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestCopyConstructorWhenConst) {
#if defined Macro
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.beginConst();
    DoublyLinkedList<PerformanceData>::Iterator it(cit);
#endif 
    SUCCEED();
}

// イテレータのコピーコンストラクタテスト
// 期待結果: コピー元と同じデータを指すことを確認
TEST(IteratorCopyTest, TestCopyConstructor) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it(list.begin());
    EXPECT_EQ((*it).first, data.first);
    EXPECT_EQ((*it).second, data.second);
}

// const イテレータの代入テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestAssignmentWhenConst) {
#if defined Macro
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    DoublyLinkedList<PerformanceData>::ConstIterator cit = list.beginConst();
    DoublyLinkedList<PerformanceData>::Iterator it = cit;
#endif 
    SUCCEED();
}

// イテレータの代入テスト
// 期待結果: コピー元と同じデータを指すことを確認
TEST(IteratorAssignmentTest, TestAssignment) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it = list.begin();
    EXPECT_EQ((*it).first, data.first);
    EXPECT_EQ((*it).second, data.second);
}

// イテレータの比較演算子テスト: 空のリストで begin と end を比較
// 期待結果: 等しいことを確認
TEST(IteratorComparisonTest, TestCompareBeginAndEndWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto it1 = list.begin();
    auto it2 = list.end();
    bool success = it1 == it2;
    EXPECT_TRUE(success);
}

// イテレータの比較演算子テスト: 同じイテレータを比較
// 期待結果: 等しいことを確認
TEST(IteratorComparisonTest, TestCompareSameIterator) {
    DoublyLinkedList<PerformanceData> list;
    auto it1 = list.begin();
    auto it2 = list.begin();
    bool success = it1 == it2;
    EXPECT_TRUE(success);
}

// イテレータの比較演算子テスト: 異なるイテレータを比較
// 期待結果: 等しくないことを確認
TEST(IteratorComparisonTest, TestCompareDifferentIterators) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data = { 10, "User" };
    list.Insert(list.end(), data);
    auto it1 = list.begin();
    auto it2 = list.end();
    bool success = it1 != it2;
    EXPECT_TRUE(success);
}

// イテレータの比較演算子テスト: インクリメント後のイテレータを比較
// 期待結果: 等しくないことを確認
TEST(IteratorComparisonTest, TestCompareAfterAdvance) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    bool success = it1 != it2;
    EXPECT_TRUE(success);
}

// const イテレータの比較テスト
// 期待結果: コンパイルエラーが発生しないことを確認
TEST(ListManualTest, TestConstIteratorComparison) {
#if defined Macro
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data1 = { 10, "User" };
    list.Insert(list.end(), data1);

    PerformanceData data2 = { 20, "User1" };
    list.Insert(list.end(), data2);

    const auto it1 = list.beginConst();
    auto it2 = list.beginConst();
    bool success = (it1 == it2);
    EXPECT_TRUE(success);
#endif 
    SUCCEED();
}

// 異なるリストのイテレータの比較テスト
// 期待結果: 等しくないことを確認
TEST(IteratorComparisonTest, TestDifferentListIterators) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1 = { 10, "User" };
    list1.Insert(list1.end(), data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2 = { 20, "User1" };
    list2.Insert(list2.end(), data2);

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    bool success = it1 != it2;
    EXPECT_TRUE(success);
}
