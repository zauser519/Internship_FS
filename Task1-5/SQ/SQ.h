#ifndef SQ_H
#define SQ_H

#include <stdexcept>
#include "DLL.h"

/**
 * @brief スタッククラス
 */
template<typename T>
class Stack {
private:
    DoublyLinkedList<T> list; // 内部リストとして二重連結リストを使用

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
    DoublyLinkedList<T> list; // 内部リストとして二重連結リストを使用

public:
    Queue(); // コンストラクタ

    void Push(const T& data); // データをキューにプッシュ
    T Pop(); // キューからデータをポップ
    bool IsEmpty() const; // キューが空かどうかを判定
    int GetSize() const; // キューのサイズを取得
};

#include "SQ.inl"

#endif // SQ_H
