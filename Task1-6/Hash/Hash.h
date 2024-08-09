#pragma once
#include <vector>
#include <functional>

// ペア構造体
// キーと値を格納するための構造体
template<typename KeyType, typename ValueType>
struct Pair {
    KeyType key;
    ValueType value;
};

// ノード構造体
// ダブルリンクリストのノードを表す構造体
template<typename KeyType, typename ValueType>
struct Node {
    Pair<KeyType, ValueType> data;
    Node* prev;
    Node* next;
    Node(const Pair<KeyType, ValueType>& data) : data(data), prev(nullptr), next(nullptr) {}
};

// ダブルリンクリストクラス
// 入力: キーと値のペアを格納するダブルリンクリストの実装
template<typename KeyType, typename ValueType>
class DoublyLinkedList {
private:
    Node<KeyType, ValueType>* head;  // リストの先頭ノード
    Node<KeyType, ValueType>* tail;  // リストの末尾ノード
    size_t size;  // リストのサイズ

public:
    DoublyLinkedList();  // コンストラクタ
    ~DoublyLinkedList();  // デストラクタ
    size_t GetSize() const;  // リストのサイズを取得
    void Insert(const Pair<KeyType, ValueType>& data);  // ノードを挿入
    bool Delete(const KeyType& key);  // ノードを削除
    Node<KeyType, ValueType>* Search(const KeyType& key) const;  // ノードを検索

    Node<KeyType, ValueType>* begin() const { return head; }  // リストの先頭ノードを取得
    Node<KeyType, ValueType>* end() const { return nullptr; }  // リストの末尾ノードを取得
};

// ハッシュテーブルクラス
// ハッシュ関数を使用してキーと値を格納するテーブルの実装
template<typename KeyType, typename ValueType, typename HashFunction = std::hash<KeyType>>
class HashTable {
private:
    std::vector<DoublyLinkedList<KeyType, ValueType>> table;  // ハッシュテーブルのバケット
    HashFunction hashFunction;  // ハッシュ関数
    size_t bucketCount;  // バケットの数

public:
    HashTable(size_t bucketCount);  // コンストラクタ
    bool Insert(const KeyType& key, const ValueType& value);  // キーと値を挿入
    bool Delete(const KeyType& key);  // キーと値を削除
    bool Search(const KeyType& key, ValueType& value) const;  // 値を検索
    size_t Size() const;  // ハッシュテーブルのサイズを取得
};

#include "Hash.inl"
