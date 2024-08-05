#ifndef DOUBLYLINKEDLIST_INL
#define DOUBLYLINKEDLIST_INL

// コンストラクタ
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept : head(nullptr), tail(nullptr) {}

// デストラクタ
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() noexcept {
    clear(); // リストをクリア
}

// ノードを追加
template<typename T>
bool DoublyLinkedList<T>::addNode(const T& data) noexcept {
    try {
        Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
        if (!head) {
            head = tail = newNode; // 最初のノード
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        return true;
    }
    catch (std::bad_alloc&) {
        return false; // メモリ確保エラー
    }
}

// リストを表示
template<typename T>
void DoublyLinkedList<T>::displayList() const noexcept {
    Node<T>* current = head;
    while (current) {
        std::cout << "Data: " << current->data << std::endl;
        current = current->next;
    }
}

// リストのサイズを取得
template<typename T>
size_t DoublyLinkedList<T>::getSize() const noexcept {
    size_t size = 0;
    Node<T>* current = head;
    while (current) {
        ++size;
        current = current->next;
    }
    return size;
}

// ノードを削除
template<typename T>
bool DoublyLinkedList<T>::deleteNode(const T& data) {
    Node<T>* current = head;
    while (current) {
        if (current->data == data) {
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
            return true;
        }
        current = current->next;
    }
    return false; // ノードが見つからない場合
}

// リストをクリア
template<typename T>
void DoublyLinkedList<T>::clear() noexcept {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

// イテレータの実装
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head, tail);
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr, tail, true); // 終端イテレータを true でマーク
}

template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node<T>* node, Node<T>* tail, bool end) : current(node), tailRef(tail), isEnd(end) {}

template<typename T>
T& DoublyLinkedList<T>::Iterator::operator*() {
    if (!current) {
        throw std::invalid_argument("Dereferencing null iterator");
    }
    return current->data;
}

template<typename T>
T* DoublyLinkedList<T>::Iterator::operator->() {
    if (!current) {
        throw std::invalid_argument("Dereferencing null iterator");
    }
    return &current->data;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    if (current) current = current->next;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
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

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template<typename T>
Node<T>* DoublyLinkedList<T>::Iterator::getCurrent() const {
    return current;
}

// ConstIterator の実装
template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::begin() const {
    return ConstIterator(head, tail);
}

template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::end() const {
    return ConstIterator(nullptr, tail, true); // 終端イテレータを true でマーク
}

template<typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(const Node<T>* node, const Node<T>* tail, bool end) : current(node), tailRef(tail), isEnd(end) {}

template<typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const {
    return current->data;
}

template<typename T>
const T* DoublyLinkedList<T>::ConstIterator::operator->() const {
    return &current->data;
}

template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() {
    if (current) current = current->next;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() {
    if (!current) {
        current = tailRef;
    }
    else if (current->prev) {
        current = current->prev;
    }
    else {
        throw std::runtime_error("Decrementing null const iterator");
    }
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int) {
    ConstIterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

template<typename T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

template<typename T>
const Node<T>* DoublyLinkedList<T>::ConstIterator::getCurrent() const {
    return current;
}

// ノードを挿入
template<typename T>
bool DoublyLinkedList<T>::insert(Iterator pos, const T& data) {
    std::cout << "Insert called." << std::endl;

    // イテレータ位置が無効（現在のノードが null）かつ終端イテレータでない場合
    if (!pos.getCurrent() && !pos.isEndIterator()) {
        std::cout << "Invalid iterator position detected: null current and not end." << std::endl;
        throw std::invalid_argument("Invalid iterator position");
    }

    // イテレータがこのリストに属しているかを先頭と末尾ノードで確認
    bool valid = pos.isEndIterator(); // 終端イテレータなら有効
    for (Node<T>* node = head; node != nullptr; node = node->next) {
        if (node == pos.getCurrent()) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        std::cout << "Iterator does not belong to this list." << std::endl;
        throw std::invalid_argument("Iterator does not belong to this list");
    }

    // 終端に挿入を許可
    if (pos.isEndIterator()) {
        std::cout << "Attempting to insert at end iterator." << std::endl;
        return addNode(data); // リストの末尾に挿入
    }

    std::cout << "Inserting at valid position." << std::endl;
    Node<T>* current = pos.getCurrent();
    Node<T>* newNode = new Node<T>{ data, nullptr, nullptr };
    Node<T>* prevNode = current->prev;

    newNode->next = current;
    newNode->prev = prevNode;
    current->prev = newNode;

    if (prevNode) {
        prevNode->next = newNode;
    }
    else {
        head = newNode;
    }

    return true;
}

// コピーコンストラクタ
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
    for (Node<T>* current = other.head; current != nullptr; current = current->next) {
        addNode(current->data);
    }
}

// 代入演算子
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    if (this != &other) {
        clear();
        for (Node<T>* current = other.head; current != nullptr; current = current->next) {
            addNode(current->data);
        }
    }
    return *this;
}

#endif // DOUBLYLINKEDLIST_INL
