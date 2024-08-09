#include <iostream>

// DoublyLinkedList クラスのコンストラクタ
// 期待結果: 空のダブルリンクリストが生成される
template<typename KeyType, typename ValueType>
DoublyLinkedList<KeyType, ValueType>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// DoublyLinkedList クラスのデストラクタ
// 期待結果: リストの全ノードが削除される
template<typename KeyType, typename ValueType>
DoublyLinkedList<KeyType, ValueType>::~DoublyLinkedList() {
    Node<KeyType, ValueType>* current = head;
    while (current) {
        Node<KeyType, ValueType>* next = current->next;
        delete current;
        current = next;
    }
}

// リストのサイズを取得する関数
// 戻り値: リストのサイズ
template<typename KeyType, typename ValueType>
size_t DoublyLinkedList<KeyType, ValueType>::GetSize() const {
    return size;
}

// ノードをリストに挿入する関数
// 引数: 挿入するデータ (Pair)
// 期待結果: ノードがリストに追加される
template<typename KeyType, typename ValueType>
void DoublyLinkedList<KeyType, ValueType>::Insert(const Pair<KeyType, ValueType>& data) {
    Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(data);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// キーでノードを削除する関数
// 引数: 削除するキー
// 戻り値: 削除に成功した場合は true, それ以外は false
template<typename KeyType, typename ValueType>
bool DoublyLinkedList<KeyType, ValueType>::Delete(const KeyType& key) {
    Node<KeyType, ValueType>* current = head;
    while (current) {
        if (current->data.key == key) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }
            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// キーでノードを検索する関数
// 引数: 検索するキー
// 戻り値: 検索に成功した場合はノードへのポインタを返す、それ以外は nullptr を返す
template<typename KeyType, typename ValueType>
Node<KeyType, ValueType>* DoublyLinkedList<KeyType, ValueType>::Search(const KeyType& key) const {
    Node<KeyType, ValueType>* current = head;
    while (current) {
        if (current->data.key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// HashTable クラスのコンストラクタ
// 期待結果: 指定されたバケット数でハッシュテーブルが初期化される
template<typename KeyType, typename ValueType, typename HashFunction>
HashTable<KeyType, ValueType, HashFunction>::HashTable(size_t bucketCount) : bucketCount(bucketCount) {
    table.resize(bucketCount);
}

// キーと値をハッシュテーブルに挿入する関数
// 引数: 挿入するキーと値
// 戻り値: 挿入に成功した場合は true, キーが既に存在する場合は false
template<typename KeyType, typename ValueType, typename HashFunction>
bool HashTable<KeyType, ValueType, HashFunction>::Insert(const KeyType& key, const ValueType& value) {
    size_t index = hashFunction(key) % bucketCount;
    if (table[index].Search(key)) {
        return false;  // キーが既に存在する場合
    }
    table[index].Insert({ key, value });
    return true;
}

// キーと値をハッシュテーブルから削除する関数
// 引数: 削除するキー
// 戻り値: 削除に成功した場合は true, それ以外は false
template<typename KeyType, typename ValueType, typename HashFunction>
bool HashTable<KeyType, ValueType, HashFunction>::Delete(const KeyType& key) {
    size_t index = hashFunction(key) % bucketCount;
    return table[index].Delete(key);
}

// ハッシュテーブルでキーに対応する値を検索する関数
// 引数: 検索するキー
// 戻り値: 検索に成功した場合は true, それ以外は false
template<typename KeyType, typename ValueType, typename HashFunction>
bool HashTable<KeyType, ValueType, HashFunction>::Search(const KeyType& key, ValueType& value) const {
    size_t index = hashFunction(key) % bucketCount;
    Node<KeyType, ValueType>* node = table[index].Search(key);
    if (node) {
        value = node->data.value;
        return true;
    }
    return false;
}

// ハッシュテーブルのサイズを取得する関数
// 戻り値: ハッシュテーブルに含まれる要素数
template<typename KeyType, typename ValueType, typename HashFunction>
size_t HashTable<KeyType, ValueType, HashFunction>::Size() const {
    size_t size = 0;
    for (const auto& list : table) {
        size += list.GetSize();
    }
    return size;
}
