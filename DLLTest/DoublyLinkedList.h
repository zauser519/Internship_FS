// DoublyLinkedList.h

#include <iostream>
#include <string>

struct PerformanceData {
    int score;
    std::string username;
};

struct Node {
    PerformanceData data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void addNode(int score, const std::string& username) {
        Node* newNode = new Node{ {score, username}, nullptr, nullptr };
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void displayList() const {
        Node* current = head;
        while (current) {
            std::cout << "Score: " << current->data.score << ", Username: " << current->data.username << std::endl;
            current = current->next;
        }
    }

    size_t getSize() const {
        size_t size = 0;
        Node* current = head;
        while (current) {
            ++size;
            current = current->next;
        }
        return size;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        PerformanceData& operator*() {
            return current->data;
        }

        PerformanceData* operator->() {
            return &(current->data);
        }

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    class ConstIterator {
    private:
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}

        const PerformanceData& operator*() const {
            return current->data;
        }

        const PerformanceData* operator->() const {
            return &(current->data);
        }

        ConstIterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
    };

    ConstIterator begin() const {
        return ConstIterator(head);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }
};
