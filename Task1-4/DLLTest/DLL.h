#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>

struct PerformanceData {
    int score;
    std::string username;
};

struct Node {
    PerformanceData data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;
    std::function<bool()> simulateFailure;

public:
    // コンストラクタ: 空のリストを作成
    DoublyLinkedList(std::function<bool()> failureSimulation = nullptr) noexcept
        : head(nullptr), tail(nullptr), size(0), simulateFailure(failureSimulation) {}

    // 新しいノードをリストの末尾に追加
    bool addNode(const PerformanceData& data) noexcept {
        if (simulateFailure && simulateFailure()) {
            return false; // 挿入失敗をシミュレート
        }
        return insert(end(), data);
    }

    // リストのサイズを取得
    size_t getSize() const noexcept {
        return size;
    }

    class ConstIterator;

    class Iterator {
    private:
        Node* current;
        Node* tailRef;

    public:
        // コンストラクタ: イテレータの初期化
        explicit Iterator(Node* node = nullptr, Node* tail = nullptr) : current(node), tailRef(tail) {}

        // デリファレンス演算子: 現在のデータを取得
        PerformanceData& operator*() {
            if (!current) throw std::invalid_argument("Dereferencing null iterator");
            return current->data;
        }

        // ポインタ演算子: 現在のデータへのポインタを取得
        PerformanceData* operator->() {
            if (!current) throw std::invalid_argument("Dereferencing null iterator");
            return &(current->data);
        }

        // 前置インクリメント演算子: 次のノードに進む
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        // 後置インクリメント演算子: 次のノードに進む（古い値を返す）
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // 前置デクリメント演算子: 前のノードに戻る
        Iterator& operator--() {
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

        // 後置デクリメント演算子: 前のノードに戻る（古い値を返す）
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // 等価演算子: イテレータの比較
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        // 非等価演算子: イテレータの比較
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // 現在のノードを取得
        Node* getCurrent() const {
            return current;
        }

        // DoublyLinkedListクラスにprivateメンバーへのアクセスを許可
        friend class DoublyLinkedList;
    };

    // 指定されたイテレータのノードを削除
    bool deleteNode(Iterator pos) {
        if (!pos.getCurrent()) {
            return false;
        }

        Node* current = pos.getCurrent();
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
        --size; // サイズをデクリメント
        return true;
    }

    // リストをクリア
    void clear() noexcept {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0; // サイズをリセット
    }

    class ConstIterator {
    private:
        const Node* current;

    public:
        // コンストラクタ: 定数イテレータの初期化
        explicit ConstIterator(const Node* node = nullptr) : current(node) {}

        // Iteratorを受け取るコンストラクタ
        ConstIterator(const Iterator& it) : current(it.getCurrent()) {}

        // デリファレンス演算子: 現在のデータを取得（定数）
        const PerformanceData& operator*() const {
            if (!current) throw std::invalid_argument("Dereferencing null const iterator");
            return current->data;
        }

        // ポインタ演算子: 現在のデータへのポインタを取得（定数）
        const PerformanceData* operator->() const {
            if (!current) throw std::invalid_argument("Dereferencing null const iterator");
            return &(current->data);
        }

        // 前置インクリメント演算子: 次のノードに進む
        ConstIterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        // 後置インクリメント演算子: 次のノードに進む（古い値を返す）
        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        // 前置デクリメント演算子: 前のノードに戻る
        ConstIterator& operator--() {
            if (current && current->prev) {
                current = current->prev;
            }
            else {
                throw std::runtime_error("Decrementing null const iterator");
            }
            return *this;
        }

        // 後置デクリメント演算子: 前のノードに戻る（古い値を返す）
        ConstIterator operator--(int) {
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        // 等価演算子: イテレータの比較
        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        // 非等価演算子: イテレータの比較
        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        // 現在のノードを取得
        const Node* getCurrent() const {
            return current;
        }
    };

    // リストの先頭を指すイテレータを取得
    Iterator begin() {
        return Iterator(head, tail);
    }

    // リストの終端を指すイテレータを取得
    Iterator end() {
        return Iterator(nullptr, tail);
    }

    // リストの先頭を指す定数イテレータを取得
    ConstIterator begin() const {
        return ConstIterator(head);
    }

    // リストの終端を指す定数イテレータを取得
    ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    // 指定された位置にノードを挿入
    bool insert(Iterator pos, const PerformanceData& data) {
        // 位置が終端の場合、ノードを末尾に追加
        if (pos == end()) {
            Node* newNode = new (std::nothrow) Node{ data, nullptr, nullptr };
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

        // イテレータが無効（null）またはこのリストに属していない場合、挿入失敗を返す
        if (!pos.getCurrent() || pos.tailRef != tail) {
            return false;
        }

        // イテレータがこのリストに属しているか確認
        Node* current = head;
        while (current != nullptr) {
            if (current == pos.getCurrent()) {
                break;
            }
            current = current->next;
        }
        if (current == nullptr) {
            return false;
        }

        Node* newNode = new (std::nothrow) Node{ data, nullptr, nullptr };
        if (!newNode) return false;

        Node* prevNode = current->prev;

        newNode->next = current;
        newNode->prev = prevNode;
        current->prev = newNode;

        if (prevNode) {
            prevNode->next = newNode;
        }
        else {
            head = newNode;
        }

        ++size; // サイズをインクリメント
        return true;
    }

    // コピーコンストラクタ: 他のリストをコピー
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        for (Node* current = other.head; current != nullptr; current = current->next) {
            addNode(current->data);
        }
    }

    // 代入演算子: 他のリストをコピー
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            for (Node* current = other.head; current != nullptr; current = current->next) {
                addNode(current->data);
            }
        }
        return *this;
    }
};

#endif // DOUBLYLINKEDLIST_H
