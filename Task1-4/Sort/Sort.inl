#include <cassert>
#include <utility>

// ノードのコンストラクタ
// 引数: const T& rd - ノードのデータ
// 期待結果: ノードが初期化される
template<typename T>
DoublyLinkedList<T>::Node::Node(const T& rd) : data(rd), prev(nullptr), next(nullptr) {}

// クイックソートを実行する関数
// 引数: Node* left - 左端のノード
//       Node* right - 右端のノード
//       const std::function<bool(const T&, const T&)>& comp - 比較関数
// 期待結果: リストがソートされる
template<typename T>
void DoublyLinkedList<T>::quickSort(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp) {
    if (right != nullptr && left != right && left != right->next) {
        Node* pivot = partition(left, right, comp);
        quickSort(left, pivot->prev, comp);
        quickSort(pivot->next, right, comp);
    }
}

// パーティションを実行する関数
// 引数: Node* left - 左端のノード
//       Node* right - 右端のノード
//       const std::function<bool(const T&, const T&)>& comp - 比較関数
// 期待結果: ピボットを基準に要素が分割される
// 戻り値: ピボットの位置のノード
template<typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::partition(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp) {
    T pivot = right->data;
    Node* i = left->prev;

    for (Node* j = left; j != right; j = j->next) {
        if (comp(j->data, pivot)) {
            i = (i == nullptr) ? left : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? left : i->next;
    swap(i->data, right->data);
    return i;
}

// データを交換する関数
// 引数: T& data1 - データ1
//       T& data2 - データ2
// 期待結果: データ1とデータ2が交換される
template<typename T>
void DoublyLinkedList<T>::swap(T& data1, T& data2) {
    T temp = std::move(data1);
    data1 = std::move(data2);
    data2 = std::move(temp);
}

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

// 代入演算子
// 期待結果: イテレータの状態をコピーする
// 引数: const ConstIterator& other - コピー元のイテレータ
template<typename T>
void  DoublyLinkedList<T>::ConstIterator::operator=(const ConstIterator& other) {
    current = other.current;
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

// DoublyLinkedList のコンストラクタ
// 期待結果: 空のリストが初期化される
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// リストのサイズを取得する関数
// 期待結果: リストのサイズを返す
// 戻り値: リストのサイズ
template<typename T>
int DoublyLinkedList<T>::Getsize() const {
    return size;
}

// ノードを挿入
// 入力: 挿入位置のイテレータ (const Iterator&), 挿入するデータ (const T&)
// 戻り値: 挿入が成功した場合は true、失敗した場合は false
template<typename T>
bool DoublyLinkedList<T>::Insert(const Iterator& iter, const T& data) {
    Node* newNode = new Node(data);
    Node* current = iter.current;

    if (iter.list != this) return false;

    if (current == nullptr) {
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    else {
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev) {
            current->prev->next = newNode;
        }
        else {
            head = newNode;
        }
        current->prev = newNode;
    }

    size++;
    return true;
}

// ノードを削除
// 入力: 削除する位置のイテレータ (const Iterator&)
// 戻り値: 削除が成功した場合は true、失敗した場合は false
template<typename T>
bool DoublyLinkedList<T>::Delete(const Iterator& iter) {
    Node* current = iter.current;

    if (current == nullptr || iter.list != this) return false;

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

// リストの先頭を指すイテレータを取得
// 期待結果: 先頭ノードを指すイテレータが返される
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head, this);
}

// リストの先頭を指す定数イテレータを取得
// 期待結果: 先頭ノードを指す定数イテレータが返される
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::beginConst() const {
    return ConstIterator(head, this);
}

// リストの末尾を指すイテレータを取得
// 期待結果: nullptrを指すイテレータが返される
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr, this);
}

// リストの末尾を指す定数イテレータを取得
// 期待結果: nullptrを指す定数イテレータが返される
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::endConst() const {
    return ConstIterator(nullptr, this);
}

// リストをソートする関数
// 入力: const std::function<bool(const T&, const T&)>& comp - 比較関数
// 期待結果: リストがソートされる
template<typename T>
void DoublyLinkedList<T>::Sort(const std::function<bool(const T&, const T&)>& comp) {
    if (head == nullptr || head->next == nullptr || comp == nullptr) return;
    quickSort(head, tail, comp);
}

// DoublyLinkedList のデストラクタ
// 期待結果: リストの全ノードが削除される
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        Delete(begin());
    }
}
