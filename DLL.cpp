#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// ノード構造体の定義
struct Node {
    int score;
    std::string username;
    Node* prev;
    Node* next;
};

// 双方向リストクラスの定義
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ノードの追加
    void addNode(int score, const std::string& username) {
        Node* newNode = new Node{score, username, nullptr, nullptr};
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // リストの内容を表示
    void displayList() const {
        Node* current = head;
        while (current) {
            std::cout << "Score: " << current->score << ", Username: " << current->username << std::endl;
            current = current->next;
        }
    }

    // デストラクタでメモリ解放
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// メイン関数
int main() {
    DoublyLinkedList list;
    std::ifstream infile("Scores.txt");

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            int score;
            std::string username;
            if (!(iss >> score >> username)) { break; } // エラーハンドリング
            list.addNode(score, username);
        }
        infile.close();
    } else {
        std::cerr << "Can't opent the file" << std::endl;
    }

    list.displayList();
    return 0;
}
