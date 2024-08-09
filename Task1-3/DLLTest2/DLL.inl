#include <cassert>

// ノードのコンストラクタ
// 引数: const T& rd - ノードのデータ
// 期待結果: ノードが初期化される
template<typename T>
DoublyLinkedList<T>::Node::Node(const T& rd) : data(rd), prev(nullptr), next(nullptr) {}

// ConstIterator のコンストラクタ
// 引数: Node* node - 現在のノード
//       const DoublyLinkedList* list - 関連するリスト
// 期待結果: ConstIterator が初期化される
template<typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(Node* node, const DoublyLinkedList* list) : current(node), list(list) {}

// ConstIterator のコピーコンストラクタ
// 引数: const ConstIterator& other - コピー元のイテレータ
// 期待結果: ConstIterator がコピーされる
template<typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const ConstIterator& other) : current(other.current), list(other.list) {}

// 前置デクリメント演算子
// 期待結果: イテレータが前のノードに移動する
// 戻り値: 自身の参照
template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() {
    assert(list != nullptr);
    assert(list->tail != nullptr);

    if (current == nullptr) {
        current = list->tail;
    }
    else {
        current = current->prev;
    }
    return *this;
}

// 後置デクリメント演算子
// 期待結果: イテレータが前のノードに移動する
// 戻り値: 移動前のイテレータのコピー
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int) {
    assert(list != nullptr);
    assert(list->tail != nullptr);

    ConstIterator temp = *this;
    --(*this);
    return temp;
}

// 前置インクリメント演算子
// 期待結果: イテレータが次のノードに移動する
// 戻り値: 自身の参照
template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() {
    assert(list != nullptr);
    assert(list->tail != nullptr);

    if (current == nullptr) {
        current = list->head;
    }
    else {
        current = current->next;
    }
    return *this;
}

// 後置インクリメント演算子
// 期待結果: イテレータが次のノードに移動する
// 戻り値: 移動前のイテレータのコピー
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int) {
    assert(list != nullptr);
    assert(list->tail != nullptr);

    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

// デリファレンス演算子
// 期待結果: 現在のノードのデータを返す
// 戻り値: 現在のノードのデータの参照
template<typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const {
    assert(current != nullptr);
    return current->data;
}

// アロー演算子
// 期待結果: 現在のノードのデータへのポインタを返す
// 戻り値: 現在のノードのデータへのポインタ
template<typename T>
const T* DoublyLinkedList<T>::ConstIterator::operator->() const {
    assert(current != nullptr);
    return &(current->data);
}

// 代入演算子
// 期待結果: イテレータの状態をコピーする
// 引数: const ConstIterator& other - コピー元のイテレータ
template<typename T>
void DoublyLinkedList<T>::ConstIterator::operator=(const ConstIterator& other) {
    current = other.current;
    list = other.list;
}

// 等価比較演算子
// 期待結果: イテレータが指しているノードが同じ場合に true を返す
// 引数: const ConstIterator& other - 比較対象のイテレータ
// 戻り値: 等しい場合は true, それ以外は false
template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

// 非等価比較演算子
// 期待結果: イテレータが指しているノードが異なる場合に true を返す
// 引数: const ConstIterator& other - 比較対象のイテレータ
// 戻り値: 異なる場合は true, それ以外は false
template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

// Iterator のコンストラクタ
// 引数: Node* node - 現在のノード
//       const DoublyLinkedList* list - 関連するリスト
// 期待結果: Iterator が初期化される
template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList* list) : ConstIterator(node, list) {}

// 前置デクリメント演算子
// 期待結果: イテレータが前のノードに移動する
// 戻り値: 自身の参照
template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() {
    assert(this->list != nullptr);
    assert(this->list->tail != nullptr);
    assert(this->current != this->list->head);

    if (this->current == nullptr) {
        this->current = this->list->tail;
    }
    else {
        this->current = this->current->prev;
    }
    return *this;
}

// 後置デクリメント演算子
// 期待結果: イテレータが前のノードに移動する
// 戻り値: 移動前のイテレータのコピー
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    assert(this->list != nullptr);
    assert(this->list->tail != nullptr);
    assert(this->current != this->list->head);

    Iterator temp = *this;
    --(*this);
    return temp;
}

// 前置インクリメント演算子
// 期待結果: イテレータが次のノードに移動する
// 戻り値: 自身の参照
template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    assert(this->current != nullptr);
    this->current = this->current->next;
    return *this;
}

// 後置インクリメント演算子
// 期待結果: イテレータが次のノードに移動する
// 戻り値: 移動前のイテレータのコピー
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    assert(this->current != nullptr);

    Iterator temp = *this;
    ++(*this);
    return temp;
}

// デリファレンス演算子
// 期待結果: 現在のノードのデータを返す
// 戻り値: 現在のノードのデータの参照
template<typename T>
T& DoublyLinkedList<T>::Iterator::operator*() {
    assert(this->current != nullptr);
    return this->current->data;
}

// アロー演算子
// 期待結果: 現在のノードのデータへのポインタを返す
// 戻り値: 現在のノードのデータへのポインタ
template<typename T>
T* DoublyLinkedList<T>::Iterator::operator->() {
    assert(this->current != nullptr);
    return &(this->current->data);
}

// DoublyLinkedList のコンストラクタ
// 期待結果: 空のリストが初期化される
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// リストのサイズを取得する関数
// 期待結果: リストのサイズを返す
// 戻り値: リストのサイズ
template<typename T>
int DoublyLinkedList<T>::GetSize() const {
    return size;
}

// ノードを挿入
// 入力: 挿入位置のイテレータ (const Iterator& または ConstIterator&), 挿入するデータ (const T&)
// 戻り値: 挿入が成功した場合はtrue、失敗した場合はfalse
template<typename T>
template<typename Iter>
bool DoublyLinkedList<T>::Insert(const Iter& iter, const T& data) {
    Node* newNode = new Node(data);
    Node* current = iter.current;

    if (iter.list != this) return false;

    if (current == nullptr) { // Insert at end or empty list
        if (tail == nullptr) { // Empty list
            head = tail = newNode;
        }
        else { // Insert at end
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    else { // Insert before the current node
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev) {
            current->prev->next = newNode;
        }
        else {
            head = newNode; // Insert at beginning
        }
        current->prev = newNode;
    }

    size++;
    return true;
}

// 指定された位置のノードを削除する関数
// 引数: const Iterator& または ConstIterator& iter - 削除位置のイテレータ
// 期待結果: 指定された位置のノードが削除される
// 戻り値: 削除に成功した場合は true, それ以外は false
template<typename T>
template<typename Iter>
bool DoublyLinkedList<T>::Delete(const Iter& iter) {
    Node* current = iter.current;

    if (current == nullptr || iter.list != this) return false;

    if (current->prev) {
        current->prev->next = current->next;
    }
    else {
        head = current->next; // Deleting the first node
    }

    if (current->next) {
        current->next->prev = current->prev;
    }
    else {
        tail = current->prev; // Deleting the last node
    }

    delete current;
    size--;
    return true;
}

// リストの先頭のイテレータを返す関数
// 期待結果: リストの先頭のイテレータを返す
// 戻り値: リストの先頭のイテレータ
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head, this);
}

// リストの先頭のイテレータを返す関数（const版）
// 期待結果: リストの先頭のイテレータを返す
// 戻り値: リストの先頭のイテレータ
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::begin() const {
    return ConstIterator(head, this);
}

// リストの末尾のイテレータを返す関数
// 期待結果: リストの末尾のイテレータを返す
// 戻り値: リストの末尾のイテレータ
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr, this);
}

// リストの末尾のイテレータを返す関数（const版）
// 期待結果: リストの末尾のイテレータを返す
// 戻り値: リストの末尾のイテレータ
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::end() const {
    return ConstIterator(nullptr, this);
}

// DoublyLinkedList のデストラクタ
// 期待結果: リストの全ノードが削除される
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        Delete(begin());
    }
}
