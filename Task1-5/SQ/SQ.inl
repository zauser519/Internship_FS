#ifndef SQ_INL
#define SQ_INL

// DoublyLinkedList メソッドの実装

// Node コンストラクタ
template<typename T>
DoublyLinkedList<T>::Node::Node(const T& rd) : data(rd), prev(nullptr), next(nullptr) {}

// DoublyLinkedList コンストラクタ
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

// リストのサイズを取得するメソッド
template<typename T>
int DoublyLinkedList<T>::Getsize() const {
    return size;
}

// リストにノードを挿入するメソッド
template<typename T>
bool DoublyLinkedList<T>::Insert(const Iterator& iter, const T& data) {
    Node* newNode = new Node(data);
    if (iter.current == nullptr) { // 末尾に挿入
        if (tail == nullptr) { // リストが空の場合
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    else { // iter.current の前に挿入
        newNode->next = iter.current;
        newNode->prev = iter.current->prev;
        if (iter.current->prev) {
            iter.current->prev->next = newNode;
        }
        else {
            head = newNode;
        }
        iter.current->prev = newNode;
    }
    size++;
    return true;
}

// リストからノードを削除するメソッド
template<typename T>
bool DoublyLinkedList<T>::Delete(const Iterator& iter) {
    if (iter.current == nullptr) return false;

    if (iter.current->prev) {
        iter.current->prev->next = iter.current->next;
    }
    else {
        head = iter.current->next;
    }

    if (iter.current->next) {
        iter.current->next->prev = iter.current->prev;
    }
    else {
        tail = iter.current->prev;
    }

    delete iter.current;
    size--;
    return true;
}

// リストの先頭を指すイテレータを取得するメソッド
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head, this);
}

// リストの先頭を指す定数イテレータを取得するメソッド
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::beginConst() const {
    return ConstIterator(head, this);
}

// リストの末尾を指すイテレータを取得するメソッド
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr, this);
}

// リストの末尾を指す定数イテレータを取得するメソッド
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::endConst() const {
    return ConstIterator(nullptr, this);
}

// リストをソートするメソッド
template<typename T>
void DoublyLinkedList<T>::Sort(const std::function<bool(const T&, const T&)>& comp) {
    if (size <= 1) return;
    quickSort(head, tail, comp);
}

// クイックソートを行うメソッド
template<typename T>
void DoublyLinkedList<T>::quickSort(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp) {
    if (left != right && left != right->next) {
        Node* pivot = partition(left, right, comp);
        quickSort(left, pivot->prev, comp);
        quickSort(pivot->next, right, comp);
    }
}

// パーティション分割を行うメソッド
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

// データを交換するメソッド
template<typename T>
void DoublyLinkedList<T>::swap(T& data1, T& data2) {
    T temp = data1;
    data1 = data2;
    data2 = temp;
}

// DoublyLinkedList デストラクタ
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// ConstIterator コンストラクタ
template<typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(Node* node, const DoublyLinkedList* list)
    : current(node), list(list) {}

// ConstIterator コピーコンストラクタ
template<typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const ConstIterator& other)
    : current(other.current), list(other.list) {}

// 前のノードを指すようにイテレータを進める（デクリメント）
template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() {
    if (current) {
        current = current->prev;
    }
    else {
        current = list->tail;
    }
    return *this;
}

// 前のノードを指すようにイテレータを進める（ポストデクリメント）
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int) {
    ConstIterator temp = *this;
    --(*this);
    return temp;
}

// 次のノードを指すようにイテレータを進める（インクリメント）
template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() {
    if (current) {
        current = current->next;
    }
    else {
        current = list->head;
    }
    return *this;
}

// 次のノードを指すようにイテレータを進める（ポストインクリメント）
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

// イテレータが指しているデータを取得
template<typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const {
    return current->data;
}

// イテレータの代入演算子
template<typename T>
void DoublyLinkedList<T>::ConstIterator::operator=(const ConstIterator& other) {
    current = other.current;
    list = other.list;
}

// イテレータの等価比較演算子
template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

// イテレータの非等価比較演算子
template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

// Iterator コンストラクタ
template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList* list)
    : ConstIterator(node, list) {}

// 前のノードを指すようにイテレータを進める（デクリメント）
template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() {
    ConstIterator::operator--();
    return *this;
}

// 前のノードを指すようにイテレータを進める（ポストデクリメント）
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

// 次のノードを指すようにイテレータを進める（インクリメント）
template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    ConstIterator::operator++();
    return *this;
}

// 次のノードを指すようにイテレータを進める（ポストインクリメント）
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

// イテレータが指しているデータを取得
template<typename T>
T& DoublyLinkedList<T>::Iterator::operator*() {
    return const_cast<T&>(ConstIterator::operator*());
}

// Stack implementation

// スタックのコンストラクタ
template<typename T>
Stack<T>::Stack() : list() {}

// スタックにデータをプッシュするメソッド
template<typename T>
void Stack<T>::Push(const T& data) {
    list.Insert(list.end(), data);
}

// スタックからデータをポップするメソッド
template<typename T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    T data = *--list.end();
    list.Delete(--list.end());
    return data;
}

// スタックが空かどうかを判定するメソッド
template<typename T>
bool Stack<T>::IsEmpty() const {
    return list.Getsize() == 0;
}

// スタックのサイズを取得するメソッド
template<typename T>
int Stack<T>::GetSize() const {
    return list.Getsize();
}

// Queue implementation

// キューのコンストラクタ
template<typename T>
Queue<T>::Queue() : list() {}

// キューにデータをプッシュするメソッド
template<typename T>
void Queue<T>::Push(const T& data) {
    list.Insert(list.end(), data);
}

// キューからデータをポップするメソッド
template<typename T>
T Queue<T>::Pop() {
    if (IsEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    T data = *list.begin();
    list.Delete(list.begin());
    return data;
}

// キューが空かどうかを判定するメソッド
template<typename T>
bool Queue<T>::IsEmpty() const {
    return list.Getsize() == 0;
}

// キューのサイズを取得するメソッド
template<typename T>
int Queue<T>::GetSize() const {
    return list.Getsize();
}

#endif // SQ_INL
