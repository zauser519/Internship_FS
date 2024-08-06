#ifndef DLL_INL
#define DLL_INL

// コンストラクタの実装
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::function<bool()> failureSimulation) noexcept
    : head(nullptr), tail(nullptr), size(0), simulateFailure(failureSimulation) {}

// デストラクタの実装
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// 新しいノードをリストの末尾に追加
template <typename T>
bool DoublyLinkedList<T>::addNode(const T& data) noexcept {
    if (simulateFailure && simulateFailure()) {
        return false; // 挿入失敗をシミュレート
    }
    return insert(end(), data);
}

// リストのサイズを取得
template <typename T>
size_t DoublyLinkedList<T>::getSize() const noexcept {
    return size;
}

// 指定されたイテレータのノードを削除
template <typename T>
bool DoublyLinkedList<T>::deleteNode(Iterator pos) {
    if (!pos.getCurrent()) {
        return false;
    }

    Node<T>* current = pos.getCurrent();
    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }
    if (current == head) {
        head = current->next;
    }
    if (current == tail) {
        tail = current->prev;
    }
    delete current;
    --size;
    return true;
}

// ConstIteratorを受け取るdeleteNode
template <typename T>
bool DoublyLinkedList<T>::deleteNode(ConstIterator pos) {
    Iterator it(const_cast<Node<T>*>(pos.getCurrent()), tail);
    return deleteNode(it);
}

// リストをクリア
template <typename T>
void DoublyLinkedList<T>::clear() noexcept {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

// リストの先頭を指すイテレータを取得
template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head, tail);
}

// リストの終端を指すイテレータを取得
template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr, tail);
}

// リストの先頭を指す定数イテレータを取得
template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::begin() const {
    return ConstIterator(head);
}

// リストの終端を指す定数イテレータを取得
template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::end() const {
    return ConstIterator(nullptr);
}

// 指定された位置にノードを挿入
template <typename T>
bool DoublyLinkedList<T>::insert(Iterator pos, const T& data) {
    if (pos.tailRef != tail) {
        return false; // 挿入失敗をシミュレート
    }

    if (pos == end()) {
        Node<T>* newNode = new (std::nothrow) Node<T>{ data, nullptr, nullptr };
        if (!newNode) return false;
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
        return true;
    }

    if (!pos.getCurrent() || pos.tailRef != tail) {
        return false;
    }

    Node<T>* newNode = new (std::nothrow) Node<T>{ data, nullptr, nullptr };
    if (!newNode) return false;

    Node<T>* prevNode = pos.getCurrent()->prev;

    newNode->next = pos.getCurrent();
    newNode->prev = prevNode;
    pos.getCurrent()->prev = newNode;

    if (prevNode) {
        prevNode->next = newNode;
    }
    else {
        head = newNode;
    }

    ++size;
    return true;
}

// ConstIteratorを受け取るinsert
template <typename T>
bool DoublyLinkedList<T>::insert(ConstIterator pos, const T& data) {
    Iterator it(const_cast<Node<T>*>(pos.getCurrent()), tail);
    return insert(it, data);
}

// コピーコンストラクタ: 他のリストをコピー
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    for (Node<T>* current = other.head; current != nullptr; current = current->next) {
        addNode(current->data);
    }
}

// 代入演算子: 他のリストをコピー
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        clear();
        for (Node<T>* current = other.head; current != nullptr; current = current->next) {
            addNode(current->data);
        }
    }
    return *this;
}

// Iteratorクラスのメソッドの定義
template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node<T>* node, Node<T>* tail) : current(node), tailRef(tail) {}

template <typename T>
T& DoublyLinkedList<T>::Iterator::operator*() {
    if (!current) throw std::invalid_argument("Dereferencing null iterator");
    return current->data;
}

template <typename T>
T* DoublyLinkedList<T>::Iterator::operator->() {
    if (!current) throw std::invalid_argument("Dereferencing null iterator");
    return &(current->data);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    if (current) current = current->next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() {
    if (!current) {
        current = tailRef;
    }
    else if (current->prev) {
        current = current->prev;
    }
    else {
        throw std::runtime_error("Decrementing null iterator");
    }
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template <typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::Iterator::getCurrent() const {
    return current;
}

// ConstIteratorクラスのメソッドの定義
template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const Node<T>* node) : current(node) {}

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const Iterator& it) : current(it.getCurrent()) {}

template <typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const {
    if (!current) throw std::invalid_argument("Dereferencing null const iterator");
    return current->data;
}

template <typename T>
const T* DoublyLinkedList<T>::ConstIterator::operator->() const {
    if (!current) throw std::invalid_argument("Dereferencing null const iterator");
    return &(current->data);
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() {
    if (current) current = current->next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() {
    if (current && current->prev) {
        current = current->prev;
    }
    else {
        throw std::runtime_error("Decrementing null const iterator");
    }
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int) {
    ConstIterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

template <typename T>
const Node<T>* DoublyLinkedList<T>::ConstIterator::getCurrent() const {
    return current;
}

#endif // DLL_INL
