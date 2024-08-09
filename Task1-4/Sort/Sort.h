#pragma once
#include <functional>

// テンプレートクラス DoublyLinkedList
// ダブルリンクリストの実装
template<typename T>
class DoublyLinkedList {
private:
    // ノードの定義
    struct Node {
        T data;
        Node* prev;
        Node* next;

        // コンストラクタ
        // 入力: ノードに格納するデータ (const T&)
        // 期待結果: ノードが生成され、データが格納される
        Node(const T& rd);
    };

    Node* head; // リストの先頭ノード
    Node* tail; // リストの末尾ノード
    int size;   // リストのサイズ

    // クイックソートを実行する関数
    // 入力: 左端のノード (Node* left), 右端のノード (Node* right), 比較関数 (const std::function<bool(const T&, const T&)>& comp)
    // 期待結果: リストがソートされる
    void quickSort(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp);

    // パーティションを実行する関数
    // 入力: 左端のノード (Node* left), 右端のノード (Node* right), 比較関数 (const std::function<bool(const T&, const T&)>& comp)
    // 期待結果: ピボットを基準に要素が分割される
    // 戻り値: ピボットの位置のノード
    Node* partition(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comp);

    // データを交換する関数
    // 入力: データ1 (T& data1), データ2 (T& data2)
    // 期待結果: データ1とデータ2が交換される
    void swap(T& data1, T& data2);

public:
    // 定数イテレータクラス
    class ConstIterator {
    private:
        Node* current;                      // 現在のノード
        const DoublyLinkedList* list;       // 所属するリスト

        friend class DoublyLinkedList;

    public:
        // コンストラクタ
        // 入力: ノード (Node*), リスト (const DoublyLinkedList*)
        // 期待結果: 定数イテレータが生成される
        ConstIterator(Node* node, const DoublyLinkedList* list);

        // コピーコンストラクタ
        // 入力: 既存のConstIterator
        // 期待結果: 新しいConstIteratorが既存のものと同じ位置を指す
        ConstIterator(const ConstIterator& other);

        // イテレータを前に進める
        // 期待結果: イテレータが一つ前のノードを指すようになる
        ConstIterator& operator--();

        // イテレータを前に進める（ポストデクリメント）
        // 期待結果: イテレータが一つ前のノードを指し、以前の状態のコピーが返される
        ConstIterator operator--(int);

        // イテレータを次に進める
        // 期待結果: イテレータが一つ次のノードを指すようになる
        ConstIterator& operator++();

        // イテレータを次に進める（ポストインクリメント）
        // 期待結果: イテレータが一つ次のノードを指し、以前の状態のコピーが返される
        ConstIterator operator++(int);

        // イテレータが指しているデータを取得
        // 期待結果: ノードのデータが返される
        const T& operator*() const;

        // イテレータの代入
        // 入力: 既存のConstIterator
        // 期待結果: イテレータが既存のものと同じ位置を指すようになる
        void operator=(const ConstIterator& other);

        // イテレータの等価比較
        // 入力: 既存のConstIterator
        // 期待結果: イテレータが同じ位置を指している場合は true、それ以外は false が返される
        bool operator==(const ConstIterator& other) const;

        // イテレータの非等価比較
        // 入力: 既存のConstIterator
        // 期待結果: イテレータが異なる位置を指している場合は true、それ以外は false が返される
        bool operator!=(const ConstIterator& other) const;
    };

    // 非定数イテレータクラス
    class Iterator : public ConstIterator {
    public:
        // コンストラクタ
        // 入力: ノード (Node*), リスト (const DoublyLinkedList*)
        // 期待結果: イテレータが生成される
        Iterator(Node* node, const DoublyLinkedList* list);

        // イテレータを前に進める
        // 期待結果: イテレータが一つ前のノードを指すようになる
        Iterator& operator--();

        // イテレータを前に進める（ポストデクリメント）
        // 期待結果: イテレータが一つ前のノードを指し、以前の状態のコピーが返される
        Iterator operator--(int);

        // イテレータを次に進める
        // 期待結果: イテレータが一つ次のノードを指すようになる
        Iterator& operator++();

        // イテレータを次に進める（ポストインクリメント）
        // 期待結果: イテレータが一つ次のノードを指し、以前の状態のコピーが返される
        Iterator operator++(int);

        // イテレータが指しているデータを取得
        // 期待結果: ノードのデータが返される
        T& operator*();
    };

    // コンストラクタ
    // 期待結果: 空のダブルリンクリストが生成される
    DoublyLinkedList();

    // リストのサイズを取得
    // 期待結果: リストのサイズが返される
    int Getsize() const;

    // ノードを挿入
    // 入力: 挿入位置のイテレータ (const Iterator&), 挿入するデータ (const T&)
    // 戻り値: 挿入が成功した場合は true、失敗した場合は false
    bool Insert(const Iterator& iter, const T& data);

    // ノードを削除
    // 入力: 削除する位置のイテレータ (const Iterator&)
    // 戻り値: 削除が成功した場合は true、失敗した場合は false
    bool Delete(const Iterator& iter);

    // リストの先頭を指すイテレータを取得
    // 期待結果: 先頭ノードを指すイテレータが返される
    Iterator begin();

    // リストの先頭を指す定数イテレータを取得
    // 期待結果: 先頭ノードを指す定数イテレータが返される
    ConstIterator beginConst() const;

    // リストの末尾を指すイテレータを取得
    // 期待結果: nullptrを指すイテレータが返される
    Iterator end();

    // リストの末尾を指す定数イテレータを取得
    // 期待結果: nullptrを指す定数イテレータが返される
    ConstIterator endConst() const;

    // リストをソートする関数
    // 入力: const std::function<bool(const T&, const T&)>& comp - 比較関数
    // 期待結果: リストがソートされる
    void Sort(const std::function<bool(const T&, const T&)>& comp);

    // デストラクタ
    // 期待結果: リストの全ノードが解放される
    ~DoublyLinkedList();
};

#include "Sort.inl"
