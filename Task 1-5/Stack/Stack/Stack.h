/**
 * @brief 二重連結リストノード
 */
    template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

/**
 * @brief 二重連結リスト
 */
template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int dataNum;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), dataNum(0) {}
    ~DoublyLinkedList();

    void Insert(Node<T>* position, const T& data); // データを挿入する関数
    void Erase(Node<T>* position); // データを削除する関数
    Node<T>* GetBegin() const { return head; } // リストの先頭を取得する関数
    Node<T>* GetEnd() const { return tail; } // リストの末尾を取得する関数
    int GetDataNum() const { return dataNum; } // データ数を取得する関数
};

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    // リストの全ノードを削除
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void DoublyLinkedList<T>::Insert(Node<T>* position, const T& data) {
    // 新しいノードを作成して挿入
    Node<T>* newNode = new Node<T>(data);
    if (position == nullptr) { // 末尾に挿入
        if (tail == nullptr) { // 空のリストの場合
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    else { // 指定位置の前に挿入
        newNode->next = position;
        newNode->prev = position->prev;
        if (position->prev) {
            position->prev->next = newNode;
        }
        else {
            head = newNode;
        }
        position->prev = newNode;
    }
    dataNum++;
}

template<typename T>
void DoublyLinkedList<T>::Erase(Node<T>* position) {
    if (position == nullptr) return;

    // ノードを削除し、ポインタを更新
    if (position->prev) {
        position->prev->next = position->next;
    }
    else {
        head = position->next;
    }

    if (position->next) {
        position->next->prev = position->prev;
    }
    else {
        tail = position->prev;
    }

    delete position;
    dataNum--;
}

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

#include "Stack.inl"
