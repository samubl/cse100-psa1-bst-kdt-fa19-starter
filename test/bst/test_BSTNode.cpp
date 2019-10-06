#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_RIGHT) {
    BSTNode<int> node(3);
    BSTNode<int> right(5);
    BSTNode<int> right_left(4);
    ASSERT_EQ(node.successor(), nullptr);
    node.right = &right;
    right.parent = &node;
    ASSERT_EQ(node.successor(), &right);
    right.left = &right_left;
    right_left.parent = &right;
    ASSERT_EQ(node.successor(), &right_left);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_PARENT) {
    BSTNode<int> node(3);
    BSTNode<int> parent_immediate(5);
    BSTNode<int> parent_not_immediate(2);
    ASSERT_EQ(node.successor(), nullptr);
    parent_immediate.left = &node;
    node.parent = &parent_immediate;
    ASSERT_EQ(node.successor(), &parent_immediate);
    parent_immediate.left = &parent_not_immediate;
    parent_not_immediate.parent = &parent_immediate;
    parent_not_immediate.right = &node;
    node.parent = &parent_not_immediate;
    ASSERT_EQ(node.successor(), &parent_immediate);
}