#include <fstream>
#include <sstream>
#include <iostream>

// コンストラクタ
inline DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr) {}

// デストラクタ
inline DoubleLinkedList::~DoubleLinkedList() {
    clear();
}

// リストをクリアする関数
inline void DoubleLinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = tail = nullptr;
}

// スコアを追加する関数
inline void DoubleLinkedList::addScore(int score, const std::string& username) {
    Node* newNode = new Node(Score(score, username));
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// スコアを出力する関数
inline void DoubleLinkedList::printScores() const {
    Node* current = head;
    while (current) {
        std::cout << current->data.score << "\t" << current->data.username << std::endl;
        current = current->next;
    }
}

// ベクターからリストを構築する関数
inline void DoubleLinkedList::fromVector(const std::vector<Score>& scores) {
    clear();
    for (const auto& score : scores) {
        addScore(score.score, score.username);
    }
}

// リストからベクターを生成する関数
inline std::vector<Score> DoubleLinkedList::toVector() const {
    std::vector<Score> scores;
    Node* current = head;
    while (current) {
        scores.push_back(current->data);
        current = current->next;
    }
    return scores;
}

inline Node* DoubleLinkedList::getHead() const {
    return head;
}

inline Node* DoubleLinkedList::getTail() const {
    return tail;
}

// 2つのScoreオブジェクトを交換する関数
inline void swap(Score& a, Score& b) noexcept {
    Score temp = a;
    a = b;
    b = temp;
}

// 双方向リストのパーティション関数
inline Node* DoubleLinkedList::partition(Node* low, Node* high, bool byScore, bool ascending) {
    Score pivot = high->data;
    Node* i = low->prev;

    for (Node* j = low; j != high; j = j->next) {
        bool condition = byScore ? (j->data.score < pivot.score) : (j->data.username < pivot.username);
        if (!ascending) condition = !condition;

        if (condition) {
            i = (i == nullptr) ? low : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

// 双方向リストのクイックソート関数
inline void DoubleLinkedList::quicksort(Node* low, Node* high, bool byScore, bool ascending) {
    if (high != nullptr && low != high && low != high->next) {
        Node* pi = partition(low, high, byScore, ascending);
        quicksort(low, pi->prev, byScore, ascending);
        quicksort(pi->next, high, byScore, ascending);
    }
}

// ファイルからスコアを読み込む関数
inline std::vector<Score> loadScores(const std::string& filename) {
    std::vector<Score> scores;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            int score;
            std::string username;
            ss >> score >> username;
            scores.emplace_back(score, username);
        }
        file.close();
    }
    return scores;
}

// スコアを出力する関数
inline void printScores(const std::vector<Score>& scores) {
    for (const auto& score : scores) {
        std::cout << score.score << "\t" << score.username << std::endl;
    }
}

// リストにデータを追加するヘルパー関数
inline void addScore(std::vector<Score>& scores, int score, const std::string& username) {
    scores.push_back({ score, username });
}
