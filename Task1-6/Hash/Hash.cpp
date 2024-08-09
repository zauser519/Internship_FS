#include <iostream>
#include "gtest/gtest.h"
#include "Hash.h"

// メイン関数
// 入力: コマンドライン引数
// 期待結果: ハッシュテーブルにデータを挿入、検索、削除して結果を表示し、Google Testを実行する
int main(int argc, char** argv) {
    HashTable<int, std::string> hashTable(10);

    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    hashTable.Insert(3, "Three");

    std::string value;
    if (hashTable.Search(2, value)) {
        std::cout << "Key 2 has value: " << value << std::endl;
    }
    else {
        std::cout << "Key 2 not found" << std::endl;
    }

    hashTable.Delete(2);

    if (hashTable.Search(2, value)) {
        std::cout << "Key 2 has value: " << value << std::endl;
    }
    else {
        std::cout << "Key 2 not found" << std::endl;
    }

    std::cout << "HashTable size: " << hashTable.Size() << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
