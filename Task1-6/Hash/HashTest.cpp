#include <iostream>
#include <string>
#include <cassert>
#include "gtest/gtest.h"
#include "Hash.h"

// モックハッシュ関数（テスト用）
// 目的: テスト用のモックハッシュ関数を定義します。特に、BadHashFunctionは意図的に全てのキーに対して同じハッシュ値を返す不適切なハッシュ関数です。
struct BadHashFunction {
    size_t operator()(int key) const {
        return 0;  // 意図的に不適切なハッシュ関数
    }
};

// 目的: 有効なハッシュ関数を2つ定義します。これらはテストでハッシュテーブルの動作を確認するために使用されます。
struct GoodHashFunction1 {
    size_t operator()(int key) const {
        return key % 10;
    }
};

struct GoodHashFunction2 {
    size_t operator()(int key) const {
        return key % 7;
    }
};

//テスト0:不適切なハッシュ関数がテンプレート引数で渡された時
//テスト項目:ハッシュテーブル
//インターフェース:クラスの挙動
//想定する戻り値:
//意図する結果:
//補足:コンパイルエラーをチェック。自動テスト化しない
TEST(HashBehavior, TestEmpty) {
#if defined SKIP_TEST
    HashTable<int, std::string, BadHashFunction> hashTable(10); // Should cause a compilation error
#endif //SKIP_TEST
    SUCCEED();
}

//テスト1:算出方法の異なる適切なハッシュ関数を渡したときのそれぞれの挙動
//テスト項目:ハッシュテーブル
//インターフェース:クラスの挙動
//想定する戻り値:
//意図する結果:
//補足:挿入、検索、削除を行い、全ての戻り値がTRUEになるかチェック
TEST(HashBehavior, CorrectHash) {
    HashTable<int, std::string> hashTable1(10);
    HashTable<int, std::string, GoodHashFunction2> hashTable2(10);

    assert(hashTable1.Insert(1, "One"));
    std::string value1;
    assert(hashTable1.Search(1, value1));
    assert(hashTable1.Delete(1));

    assert(hashTable2.Insert(2, "Two"));
    std::string value2;
    assert(hashTable2.Search(2, value2));
    assert(hashTable2.Delete(2));
}

//テスト2:リストが空である場合の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:0
//意図する結果:
//補足:
TEST(HashGet, EmptyGet) {
    HashTable<int, std::string> hashTable(10);
    assert(hashTable.Size() == 0);
}

//テスト3:要素を挿入した後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:1
//意図する結果:
//補足:
TEST(HashGet, InsertValue) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    assert(hashTable.Size() == 1);
}

//テスト4:要素を挿入し、そのキーで削除した後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:0
//意図する結果:
//補足:
TEST(HashGet, InsertDelete) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Delete(1);
    assert(hashTable.Size() == 0);
}

//テスト5:既に存在するキーで要素の挿入をし失敗した後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:1
//意図する結果:
//補足:１回挿入した後、そのキーで再度挿入する
TEST(HashGet, ExistedInsertFail) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    bool inserted = hashTable.Insert(1, "One");  // Attempt to insert the same key again
    assert(!inserted);
    assert(hashTable.Size() == 1);
}

//テスト6:リストに要素がある時に存在しないキーを指定し要素の削除に失敗した際の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:1
//意図する結果:
//補足:１回挿入した後、異なるキーで削除する

TEST(HashGet, DeleteFailed) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    bool Deleted = hashTable.Delete(2);  // Attempt to Delete a non-existent key
    assert(!Deleted);
    assert(hashTable.Size() == 1);
}

//テスト7:リストが空である場合に、削除を行った後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:0
//意図する結果:
//補足:
TEST(HashGet, EmtyDelete) {
    HashTable<int, std::string> hashTable(10);
    bool Deleted = hashTable.Delete(1);  // Attempt to Delete from an empty list
    assert(!Deleted);
    assert(hashTable.Size() == 0);
}

//テスト8:要素２つが内部でチェインになっていない時の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:2
//意図する結果:
//補足:チェインによって要素数処理が変化しないことをチェック
TEST(HashGet, Element2CheckInsideNone) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    assert(hashTable.Size() == 2);
}

//テスト9:要素２つが内部でチェインになっていない時に一方を削除した後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:1
//意図する結果:
//補足:
TEST(HashGet, Element2CheckInsodeAfterDelete) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    hashTable.Delete(1);
    assert(hashTable.Size() == 1);
}

//テスト10:要素２つが内部でチェインになった後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:2
//意図する結果:
//補足:チェインを辿れていない場合は1が返ってくるはず。同じハッシュ値の別キーを挿入
TEST(HashGet, Element2CheckInside) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    assert(hashTable.Size() == 2);
}

//テスト11:要素２つが内部でチェインになっている時に一方を削除した後の戻り値
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:1
//意図する結果:
//補足:
TEST(HashGet, Element2AfterDelete) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    hashTable.Delete(10);
    assert(hashTable.Size() == 1);
}

//テスト12:constのメソッドであるか
//テスト項目:ハッシュテーブル
//インターフェース:データ数の取得
//想定する戻り値:
//意図する結果:
//補足:constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい
TEST(HashGet, NonConstMethod) {
#if defined SKIP_TEST
    const HashTable<int, std::string> hashTable(10);
    size_t size = hashTable.Size();  // This should not cause a compilation error
#endif //SKIP_TEST
    SUCCEED();
}

//テスト13:リストが空である場合に、挿入した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:TRUE
//意図する結果:リストに要素が追加される
//補足:
TEST(HashInsert, EmptyInsert) {
    HashTable<int, std::string> hashTable(10);
    bool inserted = hashTable.Insert(1, "One");
    assert(inserted);
    assert(hashTable.Size() == 1);
}

//テスト14:リストに複数の要素がある場合に、キーが重複しないで挿入した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:TRUE
//意図する結果:リストに要素が追加される
//補足:
TEST(HashInsert, KeyInsertAgain) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    assert(hashTable.Size() == 2);
}

//テスト15:リストに複数の要素がある場合に、キーが重複して挿入しようとした際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:
TEST(HashInsert, MultipleInsertAfain) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    bool inserted = hashTable.Insert(1, "One");  // Attempt to insert a duplicate key
    assert(!inserted);
    assert(hashTable.Size() == 1);
}

//テスト16:既にリストにある要素とハッシュ値が同じになるキーで挿入した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:TRUE
//意図する結果:リストに要素が挿入される
//補足:チェインが内部で作成される。
TEST(HashInsert, InsertExistedKey) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    bool inserted = hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    assert(inserted);
    assert(hashTable.Size() == 2);
}

//テスト17:一度挿入し、削除した後再度同じキーで挿入した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:TRUE
//意図する結果:リストに要素が挿入される
//補足:削除漏れとか例外処理が変に動いていないか確認
TEST(HashInsert, InserDeleteSameKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Delete(1);
    bool inserted = hashTable.Insert(1, "One");
    assert(inserted);
    assert(hashTable.Size() == 1);
}

//テスト18:非constのメソッドであるか
//テスト項目:ハッシュテーブル
//インターフェース:データの挿入
//想定する戻り値:
//意図する結果:
//補足:constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
TEST(HashInsert, NonConstMethod) {
#if defined SKIP_TEST
    const HashTable<int, std::string> hashTable(10);
    bool inserted = hashTable.Insert(1, "One");  // This should cause a compilation error
#endif //SKIP_TEST
    SUCCEED();
}

//テスト19:リストが空である場合に、削除操作をしようとした際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:
TEST(HashDelete, EmptyDelete) {
    HashTable<int, std::string> hashTable(10);
    bool Deleted = hashTable.Delete(1);  // Attempt to Delete from an empty list
    assert(!Deleted);
    assert(hashTable.Size() == 0);
}

//テスト20:リストに複数の要素がある場合に、存在するキーで指定して削除した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:TRUE
//意図する結果:要素が削除される
//補足:
TEST(HashDelete, MultipleElementDelete) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    bool Deleted = hashTable.Delete(2);
    assert(Deleted);
    assert(hashTable.Size() == 1);
}

//テスト21:リストに複数の要素がある場合に、存在しないキーで指定して削除しようとした際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:
TEST(HashDelete, DeleteNoneExistedKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    bool Deleted = hashTable.Delete(3);  // Attempt to Delete a non-existent key
    assert(!Deleted);
    assert(hashTable.Size() == 2);
}

//テスト22:一度削除したキーで再度削除しようとした際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:削除漏れ等のミスがないかチェック
TEST(HashDelete, DeleteKeyAgain) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Delete(1);
    bool Deleted = hashTable.Delete(1);  // Attempt to Delete a key that has already been Deleted
    assert(!Deleted);
    assert(hashTable.Size() == 0);
}

//テスト23:チェインになっている要素うちの1つのキーを指定して削除した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:TRUE
//意図する結果:指定した要素だけが削除され、チェインが繋ぎなおされる
//補足:
TEST(HashDelete, DeleteSingleKey) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    bool Deleted = hashTable.Delete(10);
    assert(Deleted);
    assert(hashTable.Size() == 1);
}

//テスト24:チェインになっている要素とハッシュ値が同じだが、存在しないキーを指定して削除した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:ハッシュ値とキーによる二重検索が機能しているかチェック
TEST(HashDelete, SameElementDeleteNonExistedKey) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    bool Deleted = hashTable.Delete(30);  // Attempt to Delete a non-existent key with same hash value
    assert(!Deleted);
    assert(hashTable.Size() == 2);
}

//テスト25:チェインになっている要素を順に削除していった際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:TRUE
//意図する結果:全て正常に要素が削除される。
//補足:チェインが外れたりして削除できない状態にならないかどうか
TEST(HashDelete, ChainDeletedInOrder) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  // This should chain internally due to same hash
    bool Deleted1 = hashTable.Delete(10);
    bool Deleted2 = hashTable.Delete(20);
    assert(Deleted1);
    assert(Deleted2);
    assert(hashTable.Size() == 0);
}

//テスト26:非constのメソッドであるか
//テスト項目:ハッシュテーブル
//インターフェース:データの削除
//想定する戻り値:
//意図する結果:
//補足:constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
TEST(HashDelete, FindNonConst) {
#if defined SKIP_TEST
    const HashTable<int, std::string> hashTable(10);
    bool Deleted = hashTable.Delete(1);  // This should cause a compilation error
#endif //SKIP_TEST
    SUCCEED();
}

//テスト27:リストが空である場合に、キーを指定して検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:
TEST(HashFind, EmptyFindKey) {
    HashTable<int, std::string> hashTable(10);
    std::string value;
    bool found = hashTable.Search(1, value);  // Attempt to search in an empty list
    assert(!found);
}

//テスト28:リストに複数の要素がある場合に、存在するキーで指定して検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:TRUE
//意図する結果:指定したキーの要素が引数経由で渡される
//補足:
TEST(HashFind, FindExistedMultipleKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    std::string value;
    bool found = hashTable.Search(2, value);
    assert(found && value == "Two");
}

//テスト29:リストに複数の要素がある場合に、存在しないキーで指定して検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:
TEST(HashFind, FindNotExistKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    std::string value;
    bool found = hashTable.Search(3, value);  // Attempt to search a non-existent key
    assert(!found);
}

//テスト30:リストに複数の要素がある場合に、同じキーで2連続で検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:TRUE
//意図する結果:同じ要素が2回とも引数経由で渡される
//補足:変に削除されていたりしないかチェック
TEST(HashFind, FindSameKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    std::string value;
    bool found1 = hashTable.Search(1, value);
    bool found2 = hashTable.Search(1, value);  
    assert(found1 && found2 && value == "One");
}

//テスト31:既に削除されたキーで検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:FALSE
//意図する結果:何も起こらない
//補足:ハッシュ値とキーによる二重検索が機能しているかチェック
TEST(HashFind, FindDeletedKey) {
    HashTable<int, std::string> hashTable(10);
    hashTable.Insert(1, "One");
    hashTable.Delete(1);
    std::string value;
    bool found = hashTable.Search(1, value);  
    assert(!found);
}

//テスト32:チェインになっている要素の内の1つのキーを指定して検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:TRUE
//意図する結果:指定したキーの要素が引数経由で渡される
//補足:
TEST(HashFind, SingleElementFindCheck) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty"); 
    std::string value;
    bool found = hashTable.Search(20, value);
    assert(found && value == "Twenty");
}

//テスト33:チェインになっている要素うちの1つの削除した後に、残っている要素を検索した際の挙動
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:TRUE
//意図する結果:指定したキーの要素が引数経由で渡される
//補足:
TEST(HashFind, SingleElementDeleteCheck) {
    HashTable<int, std::string, GoodHashFunction1> hashTable(10);
    hashTable.Insert(10, "Ten");
    hashTable.Insert(20, "Twenty");  
    hashTable.Delete(10);
    std::string value;
    bool found = hashTable.Search(20, value);
    assert(found && value == "Twenty");
}

//テスト34:constメソッドであるか
//テスト項目:ハッシュテーブル
//インターフェース:データの検索
//想定する戻り値:
//意図する結果:
//補足:constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
TEST(HashFind, TestConst) {
#if defined SKIP_TEST
    const HashTable<int, std::string> hashTable(10);
    std::string value;
    bool found = hashTable.Search(1, value); 
#endif //SKIP_TEST
    SUCCEED();
}
