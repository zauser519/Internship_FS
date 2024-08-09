#ifndef SQ_H
#define SQ_H

#include <stdexcept>

/**
 * @brief テンプレートクラス DoublyLinkedList
 * ダブルリンクリストの実装
 */
template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& rd);
    };

    Node* head;
    Node* tail;
    int size;

    void quickSort(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp);
    Node* partition(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp);
    void swap(T& data1, T& data2);

public:
    class ConstIterator {
    private:
        Node* current;
        const DoublyLinkedList* list;
        friend class DoublyLinkedList;

    public:
        ConstIterator(Node* node, const DoublyLinkedList* list);
        ConstIterator(const ConstIterator& other);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        ConstIterator& operator++();
        ConstIterator operator++(int);
        const T& operator*() const;
        void operator=(const ConstIterator& other);
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
    };

    class Iterator : public ConstIterator {
    public:
        Iterator(Node* node, const DoublyLinkedList* list);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator& operator++();
        Iterator operator++(int);
        T& operator*();
    };

    DoublyLinkedList();
    int Getsize() const;
    bool Insert(const Iterator& iter, const T& data);
    bool Delete(const Iterator& iter);
    Iterator begin();
    ConstIterator beginConst() const;
    Iterator end();
    ConstIterator endConst() const;
    void Sort(const std::function<bool(const T&, const T&)>& comp);
    ~DoublyLinkedList();
};

/**
 * @brief スタッククラス
 */
template<typename T>
class Stack {
private:
    DoublyLinkedList<T> list; // 内部リストとして新しい二重連結リストを使用

public:
    Stack(); // コンストラクタ

    void Push(const T& data); // データをスタックにプッシュ
    T Pop(); // スタックからデータをポップ
    bool IsEmpty() const; // スタックが空かどうかを判定
    int GetSize() const; // スタックのサイズを取得
};

/**
 * @brief キュークラス
 */
template<typename T>
class Queue {
private:
    DoublyLinkedList<T> list; // 内部リストとして新しい二重連結リストを使用

public:
    Queue(); // コンストラクタ

    void Push(const T& data); // データをキューにプッシュ
    T Pop(); // キューからデータをポップ
    bool IsEmpty() const; // キューが空かどうかを判定
    int GetSize() const; // キューのサイズを取得
};

#include "SQ.inl"

#endif // SQ_H
