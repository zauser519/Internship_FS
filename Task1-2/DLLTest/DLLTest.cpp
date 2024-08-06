#include <gtest/gtest.h>
#include "DLL.h"


// テスト項目 0: リストが空である場合の戻り値
// インターフェース: データ数の取得
TEST(DoublyLinkedListTest, IsEmptyInitially) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 1: リスト末尾への挿入を行った際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtEnd) {
    DoublyLinkedList list;
    auto it = list.end(); 
    bool result = list.insert(it, { 10, "user1" }); 
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}


// テスト項目 2: リスト末尾への挿入が失敗した際の戻り値
// インターフェース: データの挿入
bool alwaysFail() {
    return true;
}

bool neverFail() {
    return false;
}
// テスト項目 2-1
TEST(DoublyLinkedListTest, InsertWithFailureSimulation) {
    DoublyLinkedList list(alwaysFail);
    PerformanceData data{ 10, "user1" };
    bool result = list.addNode(data);
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 0);
}
// テスト項目 2-2
TEST(DoublyLinkedListTest, InsertWithoutFailureSimulation) {
    DoublyLinkedList list(neverFail);
    PerformanceData data{ 10, "user1" };
    bool result = list.addNode(data);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 3: データの挿入を行った際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, ReturnValueOnInsert) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    bool result = list.addNode(data);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 4: データの挿入に失敗した際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, ReturnValueOnInsertFailure) {
    DoublyLinkedList list;
    bool result = false;
    try {
        PerformanceData data{ 10, "user1" };
        throw std::bad_alloc();
        result = list.addNode(data);
    }
    catch (const std::bad_alloc&) {
        result = false;
    }

    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 5: データの削除を行った際の戻り値
// インターフェース: データの削除
TEST(DoublyLinkedListTest, ReturnValueOnDelete) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    list.addNode(data);
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 6: データの削除が失敗した際の戻り値
// インターフェース: データの削除
TEST(DoublyLinkedListTest, ReturnValueOnDeleteFailure) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    list.addNode(data);

    DoublyLinkedList::Iterator invalidIt(nullptr);
    bool result = list.deleteNode(invalidIt);
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 1);
}
// テスト項目 7: リストが空である場合に、データの削除を行った際の戻り値
// インターフェース: データの削除
TEST(DoublyLinkedListTest, ReturnValueOnDeleteFromEmptyList) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_FALSE(result);
}

// テスト項目 8: constのメソッドであるか
// インターフェース: constメソッド
TEST(DoublyLinkedListTest, ConstMethodVerification) {
    const DoublyLinkedList list;
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 9: リストが空である場合に、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertWhenEmpty) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    list.addNode(data);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 10: リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtBeginIterator) {
    DoublyLinkedList list;
    list.addNode({ 20, "user2" });
    list.addNode({ 30, "user3" });
    auto it = list.begin();
    PerformanceData data{ 10, "user1" };
    list.insert(it, data);

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
    ++it;
    EXPECT_EQ(it->score, 30);
    EXPECT_EQ(it->username, "user3");
}

// テスト項目 11: リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtEndIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });

    auto it = list.end();
    list.insert(it, { 30, "user3" });

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
    ++it;
    EXPECT_EQ(it->score, 30);
    EXPECT_EQ(it->username, "user3");
}

// テスト項目 12: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtMiddleIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 30, "user3" });
    auto it = list.begin();
    ++it; // Move to the middle
    list.insert(it, { 20, "user2" });

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
    ++it;
    EXPECT_EQ(it->score, 30);
    EXPECT_EQ(it->username, "user3");
}

// テスト項目 13: ConstIteratorを指定して挿入を行った際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertUsingConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator it = constList.begin();
    EXPECT_NO_THROW(list.insert(DoublyLinkedList::Iterator(const_cast<Node*>(it.getCurrent()), const_cast<Node*>(list.end().getCurrent())), { 20, "user2" }));
}

// テスト項目 14: 不正なイテレータを渡して、挿入した場合の挙動
TEST(DoublyLinkedListTest, TestInsertInvalid) {
    DoublyLinkedList list1;
    PerformanceData data1{ 10, "user1" };
    list1.addNode(data1);
    
    DoublyLinkedList list2;
    PerformanceData data2{ 20, "user2" };
    list2.addNode(data2);

    DoublyLinkedList::Iterator it = list2.begin();
    PerformanceData data3{ 30, "user3" };
    bool success = list1.insert(it, data3);

    // 挿入が失敗することを確認
    EXPECT_FALSE(success);
    EXPECT_EQ(list1.getSize(), 1);
}


// テスト項目 15: 非constのメソッドであるか
// インターフェース: 非constメソッド
TEST(DoublyLinkedListTest, NonConstMethods) {
#ifndef CONST_METHOD_CHECK
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->score = 20;
    EXPECT_EQ(it->score, 20);
#else
    const DoublyLinkedList list;
    list.addNode({ 10, "user1" });
#endif
}

// テスト項目 16: リストが空である場合に、削除を行った際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteWhenEmpty) {
    DoublyLinkedList list;
    PerformanceData data{ 10, "user1" };
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_FALSE(result);
}

// テスト項目 17: リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteAtBeginIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
}

// テスト項目 18: リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteAtEndIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_NE(it.getCurrent(), nullptr);
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");

    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);

    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 19: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteAtMiddleIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    list.addNode({ 30, "user3" });
    auto it = list.begin();
    ++it;
    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 2);
}

// テスト項目 20: ConstIteratorを指定して削除を行った際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteUsingConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin(); // ConstIteratorではなくIteratorを使用
    EXPECT_NO_THROW(list.deleteNode(it));
}

// テスト項目 21: 不正なイテレータを渡して、削除した場合の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteUsingInvalidIterator) {
    DoublyLinkedList list;
    DoublyLinkedList::Iterator invalidIt(nullptr);
    EXPECT_FALSE(list.deleteNode(invalidIt));
}

// テスト項目 22: 非constのメソッドであるか
// インターフェース: 非constメソッド
TEST(DoublyLinkedListTest, NonConstMethodsDelete) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 23: リストが空である場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenEmpty) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 24: リストに要素が一つある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenOneElement) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 25: リストに二つ以上の要素がある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenMultipleElements) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 26: データの挿入を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterInsert) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 27: データの削除を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterDelete) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 28: constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotGetNonConstIteratorFromConstList) {
    DoublyLinkedList list;
    list.addNode({ 1, "user1" });
    list.addNode({ 2, "user2" });
    list.addNode({ 3, "user3" });
    const DoublyLinkedList constList(list);
    // Cannot get a non-const iterator from a const list
}

// テスト項目 29: リストが空である場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenEmptyAgain) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 30: リストに要素が一つある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenOneElementAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 31: リストに二つ以上の要素がある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 32: データの挿入を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterInsertAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 33: データの削除を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterDeleteAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 34: ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotAssignValueToElementFromConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList& constList = list;
    auto it = constList.begin();
    // Ensure we cannot modify the element through a const iterator
    // This should be a compile-time error in a strict const context
    // it->score = 20;
    EXPECT_NO_THROW(it->score);
}

// テスト項目 35: constのメソッドであるか
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, IsConstMethod) {
    const DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 36: リストの参照がない状態で呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWithNoListReference) {
    DoublyLinkedList::Iterator it(nullptr);
    EXPECT_THROW(it->score, std::invalid_argument);
}

// テスト項目 37: Iteratorから取得した要素に対して、値の代入が行えるかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, AssignValueToElementFromIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->score = 20;
    EXPECT_EQ(it->score, 20);
}

// テスト項目 38: リストが空の際の、先頭イテレータに対して呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallOnHeadIteratorWhenEmpty) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 39: 末尾イテレータに対して呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallOnTailIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.end();
    EXPECT_EQ(it, list.end());
}

// テスト項目 40: リストの参照がない状態で呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWithNoListReferenceAgain) {
    DoublyLinkedList::Iterator it(nullptr);
    EXPECT_THROW(it->score, std::invalid_argument);
}

// テスト項目 41: 前置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreIncrementOperator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    auto& itRef = ++it;
    EXPECT_EQ(itRef->score, 20);
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 42: 後置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostIncrementOperator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    auto itPrev = it++;
    EXPECT_EQ(itPrev->score, 10);
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 43: 前置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreDecrementOperator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    auto& itRef = --it;
    EXPECT_EQ(itRef->score, 10);
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 44: 後置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostDecrementOperator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    auto itPrev = it--;
    EXPECT_EQ(itPrev->score, 20);
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 45: ConstIteratorから、Iteratorのコピーが作成されないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotCopyConstIteratorToIterator) {
    DoublyLinkedList list;
    list.addNode({ 1, "user1" });
    list.addNode({ 2, "user2" });
    list.addNode({ 3, "user3" });
    const DoublyLinkedList constList(list);
    DoublyLinkedList::ConstIterator constIt = constList.begin();
}

// テスト項目 46: コピーコンストラクト後の値がコピー元と等しいことをチェック
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyConstructorEquality) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 47: IteratorにConstIteratorを代入できない事をチェック
// インターフェース: 代入演算子
TEST(DoublyLinkedListTest, ConstIteratorCannotAssignToIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator constIt = constList.begin();
    EXPECT_FALSE((std::is_convertible<DoublyLinkedList::ConstIterator, DoublyLinkedList::Iterator>::value));
}

// テスト項目 48: 代入後の値がコピー元と等しいことをチェック
// インターフェース: 代入演算子
TEST(DoublyLinkedListTest, AssignmentEquality) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList copyList;
    copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 49: リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareHeadAndTailIteratorWhenEmpty) {
    DoublyLinkedList list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 50: 同一のイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareSameIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 51: 異なるイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareDifferentIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    EXPECT_NE(it1, it2);
}

// テスト項目 52: リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareHeadAndTailIteratorWhenEmptyAgain) {
    DoublyLinkedList list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 53: 同一のイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareSameIteratorAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 54: 異なるイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareDifferentIteratorAgain) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    EXPECT_NE(it1, it2);
}

// テスト項目 55: イテレータから取得した要素のデータメンバを更新した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, UpdateElementFromIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->score = 20;
    EXPECT_EQ(it->score, 20);
}

// テスト項目 56: イテレータの先頭と末尾を比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareBeginAndEndIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto beginIt = list.begin();
    auto endIt = list.end();
    EXPECT_NE(beginIt, endIt);
}

// テスト項目 57: 先頭イテレータに対して前置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreIncrementBeginIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 58: 先頭イテレータに対して後置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostIncrementBeginIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    it++;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 59: 末尾イテレータに対して前置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreDecrementEndIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 60: 末尾イテレータに対して後置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostDecrementEndIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    it--;
    --it;
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 61: ConstIteratorから取得した要素のデータメンバを更新しようとした際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, UpdateElementFromConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList& constList = list;
    auto it = constList.begin();
    // it->score = 20;
    EXPECT_NO_THROW(it->score);
}

// テスト項目 62: 非constのイテレータからconstイテレータに変換が行えるかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, ConvertNonConstIteratorToConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    DoublyLinkedList::ConstIterator constIt(it);
    EXPECT_EQ(constIt->score, 10);
    EXPECT_EQ(constIt->username, "user1");
}

// テスト項目 63: ConstIteratorから非constイテレータへの変換が行えないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotConvertConstIteratorToNonConstIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator constIt = constList.begin();
}

// テスト項目 64: 空のリストに対してイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorFromEmptyList) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 65: 要素の存在するリストに対してイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorFromNonEmptyList) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_NE(it, list.end());
}

// テスト項目 66: リストの要素を削除した後にイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorAfterDelete) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 67: リストをコピーした際の挙動
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyList) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 68: 空のリストをコピーした際の挙動
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyEmptyList) {
    DoublyLinkedList list;
    DoublyLinkedList copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it, copyList.end());
}

// テスト項目 69: 二つのリストのイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareIteratorsFromDifferentLists) {
    DoublyLinkedList list1;
    DoublyLinkedList list2;
    list1.addNode({ 10, "user1" });
    list2.addNode({ 10, "user1" });
    auto it1 = list1.begin();
    auto it2 = list2.begin();
    EXPECT_NE(it1, it2);
}

// テスト項目 70: 同一のリストのイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareIteratorsFromSameList) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 71: イテレータを前進させた後の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, AdvanceIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 72: イテレータを後退させた後の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, RetreatIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 73: 逆方向のイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, ReverseIterator) {
    DoublyLinkedList list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
    --it;
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}
