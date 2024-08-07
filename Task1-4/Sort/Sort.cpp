#include "Sort.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv) {
    std::string filename = "Scores.txt";
    std::vector<Score> scores = loadScores(filename);

    DoubleLinkedList scoreList;
    scoreList.fromVector(scores);

    std::cout << "Original scores:" << std::endl;
    scoreList.printScores();

    // スコアを昇順にソート
    scoreList.quicksort(scoreList.getHead(), scoreList.getTail(), true, true);
    std::cout << "\nScores sorted in ascending order:" << std::endl;
    scoreList.printScores();

    // スコアを降順にソート
    scoreList.quicksort(scoreList.getHead(), scoreList.getTail(), true, false);
    std::cout << "\nScores sorted in descending order:" << std::endl;
    scoreList.printScores();

    // ユーザー名を昇順にソート
    scoreList.quicksort(scoreList.getHead(), scoreList.getTail(), false, true);
    std::cout << "\nUser names sorted in ascending order:" << std::endl;
    scoreList.printScores();

    // ユーザー名を降順にソート
    scoreList.quicksort(scoreList.getHead(), scoreList.getTail(), false, false);
    std::cout << "\nUser names sorted in descending order:" << std::endl;
    scoreList.printScores();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
