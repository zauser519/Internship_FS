#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Define node
struct Node {
    int score;
    std::string username;
    Node* prev;
    Node* next;
};

// Double linked list defince
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Add node
    void addNode(int score, const std::string& username) {
        Node* newNode = new Node{ score, username, nullptr, nullptr };
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Show list content
    void displayList() const {
        Node* current = head;
        while (current) {
            std::cout << "Score: " << current->score << ", Username: " << current->username << std::endl;
            current = current->next;
        }
    }

    // Free memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

//Main function
int main() {
    DoublyLinkedList list;
    std::ifstream infile("Scores.txt");

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            int score;
            std::string username;
            if (!(iss >> score >> username)) { break; } // Handling error
            list.addNode(score, username);
        }
        infile.close();
    }
    else {
        std::cerr << "Can't opent the file" << std::endl;
    }

    list.displayList();
    return 0;
}