#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

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
    DoublyLinkedList() noexcept : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() noexcept {
        clear();
    }

    bool addNode(int score, const std::string& username) noexcept {
        try {
            Node* newNode = new Node{ {score, username}, nullptr, nullptr };
            if (!head) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            return true;
        }
        catch (std::bad_alloc&) {
            return false; // Simulate insertion failure on memory allocation error
        }
    }

    void displayList() const noexcept {
        Node* current = head;
        while (current) {
            std::cout << "Score: " << current->data.score << ", Username: " << current->data.username << std::endl;
            current = current->next;
        }
    }

    size_t getSize() const noexcept {
        size_t size = 0;
        Node* current = head;
        while (current) {
            ++size;
            current = current->next;
        }
        return size;
    }

    bool deleteNode(const std::string& username) noexcept {
        Node* current = head;
        while (current) {
            if (current->data.username == username) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                if (current == head) {
                    head = current->next;
                }
                if (current == tail) {
                    tail = current->prev;
                }
                delete current;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() noexcept {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }

    class Iterator {
    private:
        Node* current;
    public:
        explicit Iterator(Node* node = nullptr) : current(node) {}

        PerformanceData& operator*() {
            return current->data;
        }

        PerformanceData* operator->() {
            return &(current->data);
        }

        Iterator& operator++() { // Pre-increment
            if (current) current = current->next;
            return *this;
        }

        Iterator operator++(int) { // Post-increment
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() { // Pre-decrement
            if (current) current = current->prev;
            return *this;
        }

        Iterator operator--(int) { // Post-decrement
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Node* getCurrent() const {
            return current;
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
        explicit ConstIterator(const Node* node = nullptr) : current(node) {}

        const PerformanceData& operator*() const {
            return current->data;
        }

        const PerformanceData* operator->() const {
            return &(current->data);
        }

        ConstIterator& operator++() { // Pre-increment
            if (current) current = current->next;
            return *this;
        }

        ConstIterator operator++(int) { // Post-increment
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator& operator--() { // Pre-decrement
            if (current) current = current->prev;
            return *this;
        }

        ConstIterator operator--(int) { // Post-decrement
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        const Node* getCurrent() const {
            return current;
        }
    };

    ConstIterator begin() const {
        return ConstIterator(head);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    bool insert(Iterator pos, int score, const std::string& username) {
        if (pos == end()) {
            return addNode(score, username);
        }

        Node* newNode = new Node{ {score, username}, nullptr, nullptr };
        Node* current = pos.getCurrent();
        Node* prevNode = current->prev;

        newNode->next = current;
        newNode->prev = prevNode;
        current->prev = newNode;

        if (prevNode) {
            prevNode->next = newNode;
        }
        else {
            head = newNode;
        }

        return true;
    }
};

#endif // DOUBLYLINKEDLIST_H
