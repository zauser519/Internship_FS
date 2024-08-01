#include <gtest/gtest.h>
#include "DoublyLinkedList.h"

// Test case to check if the list is empty
TEST(DoublyLinkedListTest, IsEmptyInitially) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getSize(), 0);
}

// Test case to check insertion at the end of the list
TEST(DoublyLinkedListTest, InsertAtEnd) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    EXPECT_EQ(list.getSize(), 1);
}

// Test case to check iterator functionality
TEST(DoublyLinkedListTest, IteratorFunctionality) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");

    auto it = list.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

// Test case to check const iterator functionality
TEST(DoublyLinkedListTest, ConstIteratorFunctionality) {
    DoublyLinkedList list;
    list.addNode(10, "user1");
    list.addNode(20, "user2");

    const DoublyLinkedList& constList = list;
    auto it = constList.begin();
    EXPECT_EQ(it->score, 10);
    EXPECT_EQ(it->username, "user1");
    ++it;
    EXPECT_EQ(it->score, 20);
    EXPECT_EQ(it->username, "user2");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
