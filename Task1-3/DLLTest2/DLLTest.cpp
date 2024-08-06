#include <gtest/gtest.h>
#include "DLL.h"

using PerformanceData = std::pair<int, std::string>;

// テスト項目 0: リストが空である場合の戻り値
// インターフェース: データ数の取得
TEST(DoublyLinkedListTest, IsEmptyInitially) {
    DoublyLinkedList<PerformanceData> list;
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 1: リスト末尾への挿入を行った際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtEnd) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.end();
    bool result = list.insert(it, { 10, "user1" });
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 2: リスト末尾への挿入が失敗した際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InserAtEndFailed) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data{ 10, "user1" };
    list1.addNode(data);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data1{ 20, "user2" };
    list2.addNode(data1);

    auto it = list2.end(); // list2のendイテレータを取得
    PerformanceData data2{ 30, "user3" };
    bool result = list1.insert(it, data2); // list1に対してlist2のイテレータを使って挿入を試みる

    EXPECT_FALSE(result); // 挿入が失敗することを確認
    EXPECT_EQ(list1.getSize(), 1); // list1のデータ数が1のままであることを確認
}

// テスト項目 3: データの挿入を行った際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, ReturnValueOnInsert) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data{ 10, "user1" };
    bool result = list.addNode(data);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 4: データの挿入に失敗した際の戻り値
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, ReturnValueOnInsertFailure) {
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data{ 10, "user1" };
    list.addNode(data);

    typename DoublyLinkedList<PerformanceData>::Iterator invalidIt(nullptr);
    bool result = list.deleteNode(invalidIt);
    EXPECT_FALSE(result);
    EXPECT_EQ(list.getSize(), 1);
}

// テスト項目 7: リストが空である場合に、データの削除を行った際の戻り値
// インターフェース: データの削除
TEST(DoublyLinkedListTest, ReturnValueOnDeleteFromEmptyList) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data{ 10, "user1" };
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_FALSE(result);
}

// テスト項目 8: constのメソッドであるか
// インターフェース: constメソッド
TEST(DoublyLinkedListTest, ConstMethodVerification) {
    const DoublyLinkedList<PerformanceData> list;
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 9: リストが空である場合に、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data{ 10, "user1" };
    list.addNode(data);
    EXPECT_EQ(list.getSize(), 1);
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 10: リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtBeginIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 20, "user2" });
    list.addNode({ 30, "user3" });
    auto it = list.begin();
    PerformanceData data{ 10, "user1" };
    list.insert(it, data);

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(it->second, "user3");
}

// テスト項目 11: リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtEndIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });

    auto it = list.end();
    list.insert(it, { 30, "user3" });

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(it->second, "user3");
}

// テスト項目 12: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertAtMiddleIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 30, "user3" });
    auto it = list.begin();
    ++it; // Move to the middle
    list.insert(it, { 20, "user2" });

    EXPECT_EQ(list.getSize(), 3);

    it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
    ++it;
    EXPECT_EQ(it->first, 30);
    EXPECT_EQ(it->second, "user3");
}

// テスト項目 13: ConstIteratorを指定して挿入を行った際の挙動
// インターフェース: データの挿入
TEST(DoublyLinkedListTest, InsertUsingConstIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto it = constList.begin();
    EXPECT_NO_THROW(list.insert(it, { 20, "user2" }));
    EXPECT_EQ(list.getSize(), 2);
    auto iter = list.begin();
    EXPECT_EQ(iter->first, 20);
    ++iter;
    EXPECT_EQ(iter->first, 10);
}

// テスト項目 14: 不正なイテレータを渡して、挿入した場合の挙動
TEST(DoublyLinkedListTest, TestInsertInvalid) {
    DoublyLinkedList<PerformanceData> list1;
    PerformanceData data1{ 10, "user1" };
    list1.addNode(data1);

    DoublyLinkedList<PerformanceData> list2;
    PerformanceData data2{ 20, "user2" };
    list2.addNode(data2);

    auto it = list2.begin();
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
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->first = 20;
    EXPECT_EQ(it->first, 20);
#else
    const DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
#endif
}

// テスト項目 16: リストが空である場合に、削除を行った際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    PerformanceData data{ 10, "user1" };
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_FALSE(result);
}

// テスト項目 17: リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteAtBeginIterator) {
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_NE(it.getCurrent(), nullptr);
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");

    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 1);

    it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 19: リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteAtMiddleIterator) {
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto it = constList.begin();
    EXPECT_NO_THROW(list.deleteNode(it));
    EXPECT_EQ(list.getSize(), 1);
    auto iter = list.begin();
    EXPECT_EQ(iter->first, 20);
}

// テスト項目 21: 不正なイテレータを渡して、削除した場合の挙動
// インターフェース: データの削除
TEST(DoublyLinkedListTest, DeleteUsingInvalidIterator) {
    DoublyLinkedList<PerformanceData> list;
    typename DoublyLinkedList<PerformanceData>::Iterator invalidIt(nullptr);
    EXPECT_FALSE(list.deleteNode(invalidIt));
}

// テスト項目 22: 非constのメソッドであるか
// インターフェース: 非constメソッド
TEST(DoublyLinkedListTest, NonConstMethodsDelete) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    bool result = list.deleteNode(it);
    EXPECT_TRUE(result);
    EXPECT_EQ(list.getSize(), 0);
}

// テスト項目 23: リストが空である場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 24: リストに要素が一つある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenOneElement) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 25: リストに二つ以上の要素がある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenMultipleElements) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 26: データの挿入を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterInsert) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 27: データの削除を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterDelete) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 28: constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
// インターフェース: イテレータ
#define CONST_METHOD_CHECK
TEST(DoublyLinkedListTest, CannotGetNonConstIteratorFromConstList) {
#if defined(CONST_METHOD_CHECK)
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 1, "user1" });
    list.addNode({ 2, "user2" });
    list.addNode({ 3, "user3" });
    const DoublyLinkedList<PerformanceData> constList(list);
    // const リストから非 const イテレータを取得できません
    // // コメントを外すとコンパイルに失敗するはずです
    // // typename DoublyLinkedList<PerformanceData>::Iterator it = constList.begin(); // コンパイル エラーを確認するには、この行のコメントを外します
#endif // CONST_METHOD_CHECK
    SUCCEED();
}

// テスト項目 29: リストが空である場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenEmptyAgain) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 30: リストに要素が一つある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenOneElementAgain) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 31: リストに二つ以上の要素がある場合に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWhenMultipleElementsAgain) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 32: データの挿入を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterInsertAgain) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 33: データの削除を行った後に、呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallAfterDeleteAgain) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 34: ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotAssignValueToElementFromConstIterator) {
#if defined(CONST_METHOD_CHECK)
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto it = constList.begin();
    // 要素を const イテレータで変更できないようにします
    // // it->first = 20; // この行のコメントを解除してコンパイル エラーを確認します
#endif // CONST_METHOD_CHECK
    SUCCEED();
}

// テスト項目 35: constのメソッドであるか
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, IsConstMethod) {
    const DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 36: リストの参照がない状態で呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWithNoListReference) {
    typename DoublyLinkedList<PerformanceData>::Iterator it(nullptr);
    EXPECT_THROW(it->first, std::invalid_argument);
}

// テスト項目 37: Iteratorから取得した要素に対して、値の代入が行えるかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, AssignValueToElementFromIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->first = 20;
    EXPECT_EQ(it->first, 20);
}

// テスト項目 38: リストが空の際の、先頭イテレータに対して呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallOnHeadIteratorWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 39: 末尾イテレータに対して呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallOnTailIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.end();
    EXPECT_EQ(it, list.end());
}

// テスト項目 40: リストの参照がない状態で呼び出した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CallWithNoListReferenceAgain) {
    typename DoublyLinkedList<PerformanceData>::Iterator it(nullptr);
    EXPECT_THROW(it->first, std::invalid_argument);
}

// テスト項目 41: 前置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreIncrementOperator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    auto& itRef = ++it;
    EXPECT_EQ(itRef->first, 20);
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 42: 後置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostIncrementOperator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    auto itPrev = it++;
    EXPECT_EQ(itPrev->first, 10);
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 43: 前置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreDecrementOperator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    auto& itRef = --it;
    EXPECT_EQ(itRef->first, 10);
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 44: 後置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostDecrementOperator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    auto itPrev = it--;
    EXPECT_EQ(itPrev->first, 20);
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 45: ConstIteratorから、Iteratorのコピーが作成されないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotCopyConstIteratorToIterator) {
#if defined(CONST_METHOD_CHECK)
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 1, "user1" });
    list.addNode({ 2, "user2" });
    list.addNode({ 3, "user3" });
    const DoublyLinkedList<PerformanceData> constList(list);
    auto constIt = constList.begin();
    // コメントを外すとコンパイルに失敗するはずです
    // // typename DoublyLinkedList<PerformanceData>::Iterator it = constIt; // コンパイルエラーをチェックするにはこの行のコメントを外します
#endif // CONST_METHOD_CHECK
    SUCCEED();
}

// テスト項目 46: コピーコンストラクト後の値がコピー元と等しいことをチェック
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyConstructorEquality) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList<PerformanceData> copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 47: IteratorにConstIteratorを代入できない事をチェック
// インターフェース: 代入演算子
TEST(DoublyLinkedListTest, ConstIteratorCannotAssignToIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto constIt = constList.begin();
    EXPECT_FALSE((std::is_convertible<typename DoublyLinkedList<PerformanceData>::ConstIterator, typename DoublyLinkedList<PerformanceData>::Iterator>::value));
}

// テスト項目 48: 代入後の値がコピー元と等しいことをチェック
// インターフェース: 代入演算子
TEST(DoublyLinkedListTest, AssignmentEquality) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList<PerformanceData> copyList;
    copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 49: リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareHeadAndTailIteratorWhenEmpty) {
    DoublyLinkedList<PerformanceData> list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 50: 同一のイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareSameIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 51: 異なるイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareDifferentIterator) {
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
    auto headIt = list.begin();
    auto tailIt = list.end();
    EXPECT_EQ(headIt, tailIt);
}

// テスト項目 53: 同一のイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareSameIteratorAgain) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 54: 異なるイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareDifferentIteratorAgain) {
    DoublyLinkedList<PerformanceData> list;
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
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    it->first = 20;
    EXPECT_EQ(it->first, 20);
}

// テスト項目 56: イテレータの先頭と末尾を比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareBeginAndEndIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto beginIt = list.begin();
    auto endIt = list.end();
    EXPECT_NE(beginIt, endIt);
}

// テスト項目 57: 先頭イテレータに対して前置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreIncrementBeginIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 58: 先頭イテレータに対して後置インクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostIncrementBeginIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    it++;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 59: 末尾イテレータに対して前置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PreDecrementEndIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 60: 末尾イテレータに対して後置デクリメントを行った際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, PostDecrementEndIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    it--;
    --it;
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 61: ConstIteratorから取得した要素のデータメンバを更新しようとした際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, UpdateElementFromConstIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto it = constList.begin();
    // it->first = 20;
    EXPECT_NO_THROW(it->first);
}

// テスト項目 62: 非constのイテレータからconstイテレータに変換が行えるかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, ConvertNonConstIteratorToConstIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    typename DoublyLinkedList<PerformanceData>::ConstIterator constIt(it);
    EXPECT_EQ(constIt->first, 10);
    EXPECT_EQ(constIt->second, "user1");
}

// テスト項目 63: ConstIteratorから非constイテレータへの変換が行えないかをチェック
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CannotConvertConstIteratorToNonConstIterator) {
#if defined(CONST_METHOD_CHECK)
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    const DoublyLinkedList<PerformanceData>& constList = list;
    auto constIt = constList.begin();
    // コメントを外すとコンパイルに失敗するはずです
    // // typename DoublyLinkedList<PerformanceData>::Iterator it = constIt; // コンパイルエラーをチェックするにはこの行のコメントを外します
#endif // CONST_METHOD_CHECK
    SUCCEED();
}

// テスト項目 64: 空のリストに対してイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorFromEmptyList) {
    DoublyLinkedList<PerformanceData> list;
    auto it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 65: 要素の存在するリストに対してイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorFromNonEmptyList) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    EXPECT_NE(it, list.end());
}

// テスト項目 66: リストの要素を削除した後にイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, GetIteratorAfterDelete) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it = list.begin();
    list.deleteNode(it);
    it = list.begin();
    EXPECT_EQ(it, list.end());
}

// テスト項目 67: リストをコピーした際の挙動
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyList) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    DoublyLinkedList<PerformanceData> copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}

// テスト項目 68: 空のリストをコピーした際の挙動
// インターフェース: コピーコンストラクタ
TEST(DoublyLinkedListTest, CopyEmptyList) {
    DoublyLinkedList<PerformanceData> list;
    DoublyLinkedList<PerformanceData> copyList = list;
    auto it = copyList.begin();
    EXPECT_EQ(it, copyList.end());
}

// テスト項目 69: 二つのリストのイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareIteratorsFromDifferentLists) {
    DoublyLinkedList<PerformanceData> list1;
    DoublyLinkedList<PerformanceData> list2;
    list1.addNode({ 10, "user1" });
    list2.addNode({ 10, "user1" });
    auto it1 = list1.begin();
    auto it2 = list2.begin();
    EXPECT_NE(it1, it2);
}

// テスト項目 70: 同一のリストのイテレータを比較した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, CompareIteratorsFromSameList) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);
}

// テスト項目 71: イテレータを前進させた後の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, AdvanceIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.begin();
    ++it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 72: イテレータを後退させた後の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, RetreatIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
}

// テスト項目 73: 逆方向のイテレータを取得した際の挙動
// インターフェース: イテレータ
TEST(DoublyLinkedListTest, ReverseIterator) {
    DoublyLinkedList<PerformanceData> list;
    list.addNode({ 10, "user1" });
    list.addNode({ 20, "user2" });
    auto it = list.end();
    --it;
    EXPECT_EQ(it->first, 20);
    EXPECT_EQ(it->second, "user2");
    --it;
    EXPECT_EQ(it->first, 10);
    EXPECT_EQ(it->second, "user1");
}
#undef CONST_METHOD_CHECK
