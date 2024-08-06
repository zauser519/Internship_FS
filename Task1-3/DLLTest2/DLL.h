#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>

// ノード構造体
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

// 双方向リストクラス
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
    std::function<bool()> simulateFailure;

public:
    // コンストラクタ: 空のリストを作成
    DoublyLinkedList(std::function<bool()> failureSimulation = nullptr) noexcept;

    // デストラクタ: リストを解放
    ~DoublyLinkedList();

    // 新しいノードをリストの末尾に追加
    bool addNode(const T& data) noexcept;

    // リストのサイズを取得
    size_t getSize() const noexcept;

    // イテレータクラスの宣言
    class ConstIterator;
    class Iterator;

    // 指定されたイテレータのノードを削除
    bool deleteNode(Iterator pos);
    bool deleteNode(ConstIterator pos);

    // リストをクリア
    void clear() noexcept;

    // リストの先頭を指すイテレータを取得
    Iterator begin();
    ConstIterator begin() const;

    // リストの終端を指すイテレータを取得
    Iterator end();
    ConstIterator end() const;

    // 指定された位置にノードを挿入
    bool insert(Iterator pos, const T& data);
    bool insert(ConstIterator pos, const T& data);

    // コピーコンストラクタ: 他のリストをコピー
    DoublyLinkedList(const DoublyLinkedList& other);

    // 代入演算子: 他のリストをコピー
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
};

// イテレータクラスの定義
template <typename T>
class DoublyLinkedList<T>::Iterator {
private:
    Node<T>* current;
    Node<T>* tailRef;

public:
    // コンストラクタ: イテレータの初期化
    explicit Iterator(Node<T>* node = nullptr, Node<T>* tail = nullptr);

    // デリファレンス演算子: 現在のデータを取得
    T& operator*();

    // ポインタ演算子: 現在のデータへのポインタを取得
    T* operator->();

    // 前置インクリメント演算子: 次のノードに進む
    Iterator& operator++();

    // 後置インクリメント演算子: 次のノードに進む（古い値を返す）
    Iterator operator++(int);

    // 前置デクリメント演算子: 前のノードに戻る
    Iterator& operator--();

    // 後置デクリメント演算子: 前のノードに戻る（古い値を返す）
    Iterator operator--(int);

    // 等価演算子: イテレータの比較
    bool operator==(const Iterator& other) const;

    // 非等価演算子: イテレータの比較
    bool operator!=(const Iterator& other) const;

    // 現在のノードを取得
    Node<T>* getCurrent() const;

    // DoublyLinkedListクラスにprivateメンバーへのアクセスを許可
    friend class DoublyLinkedList<T>;
};

// ConstIteratorクラスの定義
template <typename T>
class DoublyLinkedList<T>::ConstIterator {
private:
    const Node<T>* current;

public:
    // コンストラクタ: 定数イテレータの初期化
    explicit ConstIterator(const Node<T>* node = nullptr);

    // Iteratorを受け取るコンストラクタ
    ConstIterator(const Iterator& it);

    // デリファレンス演算子: 現在のデータを取得（定数）
    const T& operator*() const;

    // ポインタ演算子: 現在のデータへのポインタを取得（定数）
    const T* operator->() const;

    // 前置インクリメント演算子: 次のノードに進む
    ConstIterator& operator++();

    // 後置インクリメント演算子: 次のノードに進む（古い値を返す）
    ConstIterator operator++(int);

    // 前置デクリメント演算子: 前のノードに戻る
    ConstIterator& operator--();

    // 後置デクリメント演算子: 前のノードに戻る（古い値を返す）
    ConstIterator operator--(int);

    // 等価演算子: イテレータの比較
    bool operator==(const ConstIterator& other) const;

    // 非等価演算子: イテレータの比較
    bool operator!=(const ConstIterator& other) const;

    // 現在のノードを取得
    const Node<T>* getCurrent() const;
};

// インラインファイルをインクルード
#include "DLL.inl"

#endif // DOUBLYLINKEDLIST_H
