#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
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
    bool simulateFailure; // 失敗をシミュレートする

public:
    // コンストラクタ: 空のリストを作成
    DoublyLinkedList() noexcept : head(nullptr), tail(nullptr), simulateFailure(false) {} 

    void setSimulateFailure(bool value) {
        simulateFailure = value;
    }

    // 新しいノードをリストの末尾に追加
    bool addNode(const PerformanceData& data) noexcept {
        if (simulateFailure) { 
            return false;
        }
        try {
            Node* newNode = new Node{ data, nullptr, nullptr };
            if (!head) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            return true;
        }
        catch (std::bad_alloc&) {
            return false;// メモリ割り当てエラーで挿入失敗をシミュレート
        }
    }

    // リストのサイズを取得
    size_t getSize() const noexcept {
        size_t size = 0;
        Node* current = head;
        while (current) {
            ++size;
            current = current->next;
        }
        return size;
    }

    // 指定されたユーザー名のノードを削除
    bool deleteNode(const PerformanceData& data) {
        Node* current = head;
        while (current) {
            if (current->data.username == data.username) {
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
        return false;
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

        // 後置デクリメント演算子: 前のノードに戻る（古い値を返す)
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

        // ConstIteratorにprivateメンバーへのアクセスを許可
        friend class ConstIterator;
    };

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
            return addNode(data);
        }

        // イテレータが無効またはこのリストに属していない場合、例外を投げる
        if (!pos.getCurrent()) {
            throw std::invalid_argument("Invalid iterator position");
        }

        // イテレータがこのリストに属しているか確認
        bool valid = false;
        for (Node* node = head; node != nullptr; node = node->next) {
            if (node == pos.getCurrent()) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            throw std::invalid_argument("Iterator does not belong to this list");
        }

        Node* current = pos.getCurrent();
        Node* newNode = new Node{ data, nullptr, nullptr };
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

        return true;
    }

    // コピーコンストラクタ: 他のリストをコピー
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
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
