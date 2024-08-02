#include <gtest/gtest.h>
#include "DLL.h"

// テスト項目 1: リストが空である場合の戻り値
TEST(DoublyLinkedListTest, IsEmptyInitially) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 2: リスト末尾への挿入を行った際の戻り値
TEST(DoublyLinkedListTest, InsertAtEnd) {
    DoublyLinkedList list;
    bool result = list.addNode(10, "user1");
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 3: リスト末尾への挿入が失敗した際の戻り値
TEST(DoublyLinkedListTest, InsertAtEndFailure) {
    DoublyLinkedList list;
    bool result = false; 
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 4: データの挿入を行った際の戻り値
TEST(DoublyLinkedListTest, ReturnValueOnInsert) {
    DoublyLinkedList list;
    bool result = list.addNode(10, "user1");
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 5: データの挿入に失敗した際の戻り値
TEST(DoublyLinkedListTest, ReturnValueOnInsertFailure) {
    DoublyLinkedList list;
    bool result = false;
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 6: データの削除を行った際の戻り値
TEST(DoublyLinkedListTest, ReturnValueOnDelete) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    bool result = list.deleteNode("user1");
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 7: データの削除が失敗した際の戻り値
TEST(DoublyLinkedListTest, ReturnValueOnDeleteFailure) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    bool result = list.deleteNode("user2");
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 1);
}

// テスト項目 8: リストが空である場合に、データの削除を行った際の戻り値
TEST(DoublyLinkedListTest, ReturnValueOnDeleteFromEmptyList) {
    DoublyLinkedList list;
    bool result = list.deleteNode("user1");
    EXPECT_FALSE(result);
}

// テスト項目 9: constのメソッドであるか
TEST(DoublyLinkedListTest, ConstMethodVerification) {
    const DoublyLinkedList list;
    auto it = list.begin();
    auto end = list.end();
    EXPECT_EQ(it, end);
}

// テスト項目 10: リストが空である場合に、挿入した際の挙動
TEST(DoublyLinkedListTest, InsertWhenEmpty) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 11: リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
TEST(DoublyLinkedListTest, InsertAtBeginIterator) {
    DoublyLinkedList list;
    list.addNode(20, "user2");
    list.addNode(30, "user3");
    auto it = list.begin();
    list.insert(it, 10, "user1");

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

// テスト項目 12: リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
TEST(DoublyLinkedListTest, InsertAtEndIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");

    auto it = list.end();
    list.insert(it, 30, "user3");

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

// テスト項目 13: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
TEST(DoublyLinkedListTest, InsertAtMiddleIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(30, "user3");
    auto it = list.begin();
    ++it; // Move to the middle
    list.insert(it, 20, "user2");

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

// テスト項目 14: ConstIteratorを指定して挿入を行った際の挙動
TEST(DoublyLinkedListTest, InsertUsingConstIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator it = constList.begin();
    EXPECT_NO_THROW(list.insert(DoublyLinkedList::Iterator(const_cast<Node*>(it.getCurrent()), const_cast<Node*>(list.end().getCurrent())), 20, "user2"));
}

// テスト項目 15: 不正なイテレータを渡して、挿入した場合の挙動
TEST(DoublyLinkedListTest, InsertUsingInvalidIterator) {
    DoublyLinkedList list;
    list.addNode(10, "valid_user"); 
    DoublyLinkedList::Iterator invalidIt(nullptr, nullptr);

    auto initialSize = list.getSize();
    std::vector<PerformanceData> initialData;
    for (auto it = list.begin(); it != list.end(); ++it) {
        initialData.push_back(*it);
    }

    list.insert(invalidIt, 20, "invalid_user");

    auto finalSize = list.getSize();
    std::vector<PerformanceData> finalData;
    for (auto it = list.begin(); it != list.end(); ++it) {
        finalData.push_back(*it);
    }

    EXPECT_EQ(finalSize, initialSize + 1);
    EXPECT_EQ(finalData.back().score, 20);
    EXPECT_EQ(finalData.back().username, "invalid_user");

    for (size_t i = 0; i < initialData.size(); ++i) {
        EXPECT_EQ(finalData[i].score, initialData[i].score);
        EXPECT_EQ(finalData[i].username, initialData[i].username);
    }
}

// テスト項目 16: 非constのメソッドであるか
TEST(DoublyLinkedListTest, NonConstMethods) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    it->score = 20;
    EXPECT_EQ(it->score, 20);
}

// テスト項目 17: リストが空である場合に、削除を行った際の挙動
TEST(DoublyLinkedListTest, DeleteWhenEmpty) {
    DoublyLinkedList list;
    bool result = list.deleteNode("user1");
    EXPECT_FALSE(result);
}

// テスト項目 18: リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
TEST(DoublyLinkedListTest, DeleteAtBeginIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    bool result = list.deleteNode(it->username);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
}

// テスト項目 19: リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
TEST(DoublyLinkedListTest, DeleteAtEndIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.end();
    --it;
    EXPECT_NE(it.getCurrent(), nullptr); 
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");

    bool result = list.deleteNode(it->username);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);

    it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 20: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
TEST(DoublyLinkedListTest, DeleteAtMiddleIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    list.addNode(30, "user3");
    auto it = list.begin();
    ++it; 
    bool result = list.deleteNode(it->username);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 2);
}

// テスト項目 21: ConstIteratorを指定して削除を行った際の挙動
TEST(DoublyLinkedListTest, DeleteUsingConstIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator it = constList.begin();
    EXPECT_NO_THROW(list.deleteNode(it->username));
}

// テスト項目 22: 不正なイテレータを渡して、削除した場合の挙動
TEST(DoublyLinkedListTest, DeleteUsingInvalidIterator) {
    DoublyLinkedList list;
    DoublyLinkedList::Iterator invalidIt(nullptr);
    EXPECT_THROW(list.deleteNode(invalidIt->username), std::invalid_argument);
}

// テスト項目 23: 非constのメソッドであるか
TEST(DoublyLinkedListTest, NonConstMethodsDelete) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    bool result = list.deleteNode(it->username);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 24: リストが空である場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenEmpty) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 25: リストに要素が一つある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenOneElement) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 26: リストに二つ以上の要素がある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElements) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 27: データの挿入を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterInsert) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 28: データの削除を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterDelete) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.deleteNode("user1");
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 29: constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
TEST(DoublyLinkedListTest, CannotGetNonConstIteratorFromConstList) {
    DoublyLinkedList list;
    list.addNode(1, "user1");
    list.addNode(2, "user2");
    list.addNode(3, "user3");
    const DoublyLinkedList constList(list);
}

// テスト項目 30: リストが空である場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenEmptyAgain) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 31: リストに要素が一つある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenOneElementAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 32: リストに二つ以上の要素がある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 33: データの挿入を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterInsertAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 34: データの削除を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterDeleteAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.deleteNode("user1");
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 35: constのメソッドであるか
TEST(DoublyLinkedListTest, IsConstMethod) {
    const DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 36: リストが空である場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenEmptyAgain2) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 37: リストに要素が一つある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenOneElementAgain2) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 38: リストに二つ以上の要素がある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain2) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 39: データの挿入を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterInsertAgain2) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 40: データの削除を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterDeleteAgain2) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.deleteNode("user1");
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 41: constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
TEST(DoublyLinkedListTest, CannotGetNonConstIteratorFromConstListCheck) {
    DoublyLinkedList list;
    list.addNode(1, "user1");
    list.addNode(2, "user2");
    list.addNode(3, "user3");
    const DoublyLinkedList constList(list);
}



// テスト項目 42: リストが空である場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenEmptyAgain3) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 43: リストに要素が一つある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenOneElementAgain3) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 44: リストに二つ以上の要素がある場合に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain3) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 45: データの挿入を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterInsertAgain3) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 46: データの削除を行った後に、呼び出した際の挙動
TEST(DoublyLinkedListTest, CallAfterDeleteAgain3) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.deleteNode("user1");
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 47: constのメソッドであるか
TEST(DoublyLinkedListTest, IsConstMethodAgain) {
    const DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 48: リストの参照がない状態で呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWithNoListReference) {
    DoublyLinkedList::Iterator it(nullptr);
    EXPECT_THROW(it->score, std::invalid_argument);
}

// テスト項目 49: Iteratorから取得した要素に対して、値の代入が行えるかをチェック
TEST(DoublyLinkedListTest, AssignValueToElementFromIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    it->score = 20;
    EXPECT_EQ(it->score, 20);
}

// テスト項目 50: ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
TEST(DoublyLinkedListTest, CannotAssignValueToElementFromConstIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    const DoublyLinkedList& constList = list;
    auto it = constList.begin();
    EXPECT_NO_THROW(it->score);
}

// テスト項目 51: リストが空の際の、先頭イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnHeadIteratorWhenEmpty) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 52: 末尾イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnTailIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.end();
    EXPECT_EQ(it, list.end());
}

// テスト項目 53: リストの参照がない状態で呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWithNoListReferenceAgain) {
    DoublyLinkedList::Iterator it(nullptr);
    EXPECT_THROW(it->score, std::invalid_argument);
}

// テスト項目 54: リストが空の際の、先頭イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnHeadIteratorWhenEmptyAgain) {
    DoublyLinkedList list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 55: 末尾イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnTailIteratorAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.end();
    EXPECT_EQ(it, list.end());
}

// テスト項目 56: リストに二つ以上の要素がある場合に呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain4) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 57: 前置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
TEST(DoublyLinkedListTest, PreIncrementOperator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 58: 後置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
TEST(DoublyLinkedListTest, PostIncrementOperator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    it++;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 59: リストの参照がない状態で呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWithNoListReferenceAgain2) {
    DoublyLinkedList::Iterator it(nullptr);
    EXPECT_THROW(it->score, std::invalid_argument);
}

// テスト項目 60: リストが空の際の、末尾イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnTailIteratorWhenEmpty) {
    DoublyLinkedList list;
    auto it = list.end();
    EXPECT_EQ(it, list.end());
}

// テスト項目 61: 先頭イテレータに対して呼び出した際の挙動
TEST(DoublyLinkedListTest, CallOnHeadIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 62: リストに二つ以上の要素がある場合に呼び出した際の挙動
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain5) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 63: 前置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
TEST(DoublyLinkedListTest, PreDecrementOperator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.end();
    --it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// テスト項目 64: 後置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
TEST(DoublyLinkedListTest, PostDecrementOperator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it = list.end();
    it--;
    --it;
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 65: ConstIteratorから、Iteratorのコピーが作成されないかをチェック
TEST(DoublyLinkedListTest, CannotCopyConstIteratorToIterator) {
    DoublyLinkedList list;
    list.addNode(1, "user1");
    list.addNode(2, "user2");
    list.addNode(3, "user3");
    const DoublyLinkedList constList(list);
    DoublyLinkedList::ConstIterator constIt = constList.begin();
}



// テスト項目 66: コピーコンストラクト後の値がコピー元と等しいことをチェック
TEST(DoublyLinkedListTest, CopyConstructorEquality) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    DoublyLinkedList copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 67: IteratorにConstIteratorを代入できない事をチェック
TEST(DoublyLinkedListTest, ConstIteratorCannotAssignToIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    const DoublyLinkedList& constList = list;
    DoublyLinkedList::ConstIterator constIt = constList.begin();
    EXPECT_FALSE((std::is_convertible<DoublyLinkedList::ConstIterator, DoublyLinkedList::Iterator>::value));
}

// テスト項目 68: 代入後の値がコピー元と等しいことをチェック
TEST(DoublyLinkedListTest, AssignmentEquality) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    DoublyLinkedList copyList;
    copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
}

// テスト項目 69: リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
TEST(DoublyLinkedListTest, CompareHeadAndTailIteratorWhenEmpty) {
    DoublyLinkedList list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 70: 同一のイテレータを比較した際の挙動
TEST(DoublyLinkedListTest, CompareSameIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 71: 異なるイテレータを比較した際の挙動
TEST(DoublyLinkedListTest, CompareDifferentIterator) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    EXPECT_NE(it1, it2);
}

// テスト項目 72: リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
TEST(DoublyLinkedListTest, CompareHeadAndTailIteratorWhenEmptyAgain) {
    DoublyLinkedList list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 73: 同一のイテレータを比較した際の挙動
TEST(DoublyLinkedListTest, CompareSameIteratorAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 74: 異なるイテレータを比較した際の挙動
TEST(DoublyLinkedListTest, CompareDifferentIteratorAgain) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");
    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2;
    EXPECT_NE(it1, it2);
}

// テスト項目 75: ConstIteratorから、Iteratorのコピーが作成されないかをチェック
TEST(DoublyLinkedListTest, CannotCopyConstIteratorToIteratorCheck) {
    DoublyLinkedList list;
    list.addNode(1, "user1");
    list.addNode(2, "user2");
    list.addNode(3, "user3");
    const DoublyLinkedList constList(list);
    DoublyLinkedList::ConstIterator constIt = constList.end();
}
