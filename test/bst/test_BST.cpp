#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

TEST(BSTTests, EMPTY_TREE_SIZE_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
}

TEST(BSTTests, EMPTY_TREE_TEST) {
    BST<int> bst;
    ASSERT_TRUE(bst.empty());
}

TEST(BSTTests, EMPTY_TREE_NO_ELEMENTS) {
    BST<int> bst;
    ASSERT_EQ(bst.begin(), bst.end());
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    // assert that the small BST has the correct height
    ASSERT_EQ(bst.height(), 2);
}

TEST_F(SmallBSTFixture, SMALL_EMPTY_TEST) {
    // assert that the small BST is not empty
    ASSERT_FALSE(bst.empty());
}

TEST_F(SmallBSTFixture, SMALL_BEGIN_TEST) {
    // assert that the small bst has correct beginning
    ASSERT_NE(bst.begin(), bst.end());
    ASSERT_EQ(*(bst.begin()), -33);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_TEST) {
    // assert insertion
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 6);
    ASSERT_EQ(bst.height(), 3);
}

TEST_F(SmallBSTFixture, SMALL_FIRST_TEST) {
    // assert failed duplicate insertion
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 6);
    ASSERT_EQ(bst.height(), 3);
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST) {
    // assert find
    ASSERT_EQ(bst.find(5), bst.end());
    ASSERT_EQ(*(bst.find(3)), 3);
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INORDER_TEST) {
    // assert inorder
    vector<int> elements = bst.inorder();
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(elements[0], -33);
    ASSERT_EQ(elements[1], 1);
    ASSERT_EQ(elements[2], 3);
    ASSERT_EQ(elements[3], 4);
    ASSERT_EQ(elements[4], 100);
}
