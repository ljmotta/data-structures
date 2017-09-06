/* Copyright [2016] <João Paulo Taylor Ienczak Zanette> */
#include "gtest/gtest.h"
#include "linked_stack.h"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/**
 * Teste unitario para pilha encadeada
 */

class LinkedStackTest: public ::testing::Test {
protected:
    /**
     * Pilha na qual serao efetuadas as operações
     */
    structures::LinkedStack<int> stack{};
};


TEST_F(LinkedStackTest, Push) {
    ASSERT_EQ(0u, stack.size());

    stack.push(0);
    ASSERT_EQ(0, stack.top());
    ASSERT_EQ(1u, stack.size());

    stack.push(2);
    ASSERT_EQ(2, stack.top());
    ASSERT_EQ(2u, stack.size());

    stack.push(-1);
    ASSERT_EQ(-1, stack.top());
    ASSERT_EQ(3u, stack.size());
}

TEST_F(LinkedStackTest, Empty) {
    ASSERT_TRUE(stack.empty());
}

TEST_F(LinkedStackTest, NotEmpty) {
    ASSERT_TRUE(stack.empty());
    stack.push(1);
    ASSERT_FALSE(stack.empty());
}

TEST_F(LinkedStackTest, Clear) {
    for (auto i = 0; i < 10; ++i) {
        stack.push(i);
    }
    stack.clear();
    ASSERT_EQ(0u, stack.size());
    ASSERT_TRUE(stack.empty());
}

TEST_F(LinkedStackTest, Pop) {
    for (auto i = 0; i < 10; ++i) {
        stack.push(i);
        ASSERT_EQ(i, stack.top());
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(9-i, stack.pop());
        ASSERT_EQ(9-i, stack.pop());
    }
    ASSERT_TRUE(stack.empty());
}

TEST_F(LinkedStackTest, TopEmpty) {
    ASSERT_THROW(stack.top(), std::out_of_range);
}

TEST_F(LinkedStackTest, PopEmpty) {
    ASSERT_THROW(stack.pop(), std::out_of_range);
}
