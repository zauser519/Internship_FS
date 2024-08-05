#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

// Node 構造体の定義
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

// DoublyLinkedList クラスの定義
template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head; // リストの先頭
    Node<T>* tail; // リストの末尾

public:
    DoublyLinkedList() noexcept; // コンストラクタ
    ~DoublyLinkedList() noexcept; // デストラクタ

    bool addNode(const T& data) noexcept; // ノードを追加
    void displayList() const noexcept; // リストを表示
    size_t getSize() const noexcept; // リストのサイズを取得
    bool deleteNode(const T& data); // ノードを削除
    void clear() noexcept; // リストをクリア

    // イテレータクラスの定義
    class Iterator {
    private:
        Node<T>* current; // 現在のノード
        Node<T>* tailRef; // リストの末尾の参照
        bool isEnd; // イテレータがリストの末尾かどうか

    public:
        explicit Iterator(Node<T>* node = nullptr, Node<T>* tail = nullptr, bool end = false);

        T& operator*();
        T* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Node<T>* getCurrent() const;
        bool isEndIterator() const { return isEnd; }
    };

    Iterator begin();
    Iterator end();

    // ConstIterator クラスの定義
    class ConstIterator {
    private:
        const Node<T>* current; // 現在のノード（定数）
        const Node<T>* tailRef; // リストの末尾の参照（定数）
        bool isEnd; // イテレータがリストの末尾かどうか

    public:
        explicit ConstIterator(const Node<T>* node = nullptr, const Node<T>* tail = nullptr, bool end = false);

        const T& operator*() const;
        const T* operator->() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
        const Node<T>* getCurrent() const;
        bool isEndIterator() const { return isEnd; }
    };

    ConstIterator begin() const;
    ConstIterator end() const;

    bool insert(Iterator pos, const T& data);
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
};

#include "DLL.inl"

#endif // DOUBLYLINKEDLIST_H
