#ifndef SQ_INL
#define SQ_INL

// Stack implementation
template<typename T>
Stack<T>::Stack() : list() {} // スタックのコンストラクタ

template<typename T>
void Stack<T>::Push(const T& data) {
    list.Insert(nullptr, data); // 末尾にデータを挿入
}

template<typename T>
T Stack<T>::Pop() {
    if (IsEmpty()) {
        throw std::out_of_range("Stack is empty"); // スタックが空の場合、例外をスロー
    }
    T data = list.GetEnd()->data; // 末尾のデータを取得
    list.Erase(list.GetEnd()); // 末尾のノードを削除
    return data; // データを返す
}

template<typename T>
bool Stack<T>::IsEmpty() const {
    return list.GetDataNum() == 0; // データ数が0かどうかを判定
}

template<typename T>
int Stack<T>::GetSize() const {
    return list.GetDataNum(); // データ数を返す
}

// Queue implementation
template<typename T>
Queue<T>::Queue() : list() {} // キューのコンストラクタ

template<typename T>
void Queue<T>::Push(const T& data) {
    list.Insert(nullptr, data); // 末尾にデータを挿入
}

template<typename T>
T Queue<T>::Pop() {
    if (IsEmpty()) {
        throw std::out_of_range("Queue is empty"); // キューが空の場合、例外をスロー
    }
    T data = list.GetBegin()->data; // 先頭のデータを取得
    list.Erase(list.GetBegin()); // 先頭のノードを削除
    return data; // データを返す
}

template<typename T>
bool Queue<T>::IsEmpty() const {
    return list.GetDataNum() == 0; // データ数が0かどうかを判定
}

template<typename T>
int Queue<T>::GetSize() const {
    return list.GetDataNum(); // データ数を返す
}

#endif // SQ_INL
