#ifndef SORT_H
#define SORT_H

#include <vector>
#include <string>
#include <iostream>

// スコアデータを保持する構造体
struct Score {
    int score;
    std::string username;
    Score(int s = 0, std::string u = "") : score(s), username(u) {} // メンバーを初期化
};

// ノードの構造体
struct Node {
    Score data;
    Node* prev;
    Node* next;
    Node(Score s) : data(s), prev(nullptr), next(nullptr) {}
};

// 双方向リストのクラス
class DoubleLinkedList {
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void addScore(int score, const std::string& username);
    void printScores() const;
    void clear();
    void fromVector(const std::vector<Score>& scores);
    std::vector<Score> toVector() const;
    Node* partition(Node* low, Node* high, bool byScore, bool ascending);
    void quicksort(Node* low, Node* high, bool byScore, bool ascending);

    Node* getHead() const;
    Node* getTail() const;

private:
    Node* head;
    Node* tail;
};

#include "Sort.inl"

#endif // SORT_H
