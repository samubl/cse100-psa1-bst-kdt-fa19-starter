#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data>* root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

  public:
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    virtual ~BST() { deleteAll(root); }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual bool insert(const Data& item) {
        if (empty()) {  // update the root for when we're just starting
            BSTNode<Data>* newNode =
                new BSTNode<Data>(item);  // create the new root
            root = newNode;
            isize++;
            iheight++;
            return true;
        } else {
            BSTNode<Data>* currNode =
                root;                    // starting point for our loop pointer
            bool added = false;          // will be used to manage loop
            unsigned int currDepth = 0;  // will be used to calculate height

            while (!added) {
                currDepth++;  // increase depth everytime we go through loop
                if (item < currNode->data) {  // newNode should go left
                    if (currNode->left ==
                        nullptr) {  // we found where our node should go
                        BSTNode<Data>* newNode = new BSTNode<Data>(item);
                        currNode->left = newNode;  // update left pointer
                        newNode->parent =
                            currNode;  // update newNode's parent pointer
                        isize++;
                        if (iheight <
                            currDepth)  // see if we've increased height of tree
                            iheight = currDepth;
                        added = true;
                    }
                    currNode = currNode->left;
                } else if (currNode->data < item) {  // newNode should go right
                    if (currNode->right ==
                        nullptr) {  // we found where our node should go
                        // create newNode on the heap
                        BSTNode<Data>* newNode = new BSTNode<Data>(item);
                        currNode->right = newNode;  // update right pointer
                        newNode->parent =
                            currNode;  // update newNode's parent pointer
                        isize++;
                        if (iheight <
                            currDepth)  // see if we've increased heigh of tree
                            iheight = currDepth;
                        added = true;
                    }
                    currNode = currNode->right;
                } else {  // newNode is a duplicate since it is equal to another
                          // node
                    return added;  // return false since we tried to insert a
                                   // duplicate
                }
            }

            // once we're out of the while loop, we know we've added the node
            return added;
        }
    }

    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual iterator find(const Data& item) const {
        BSTNode<Data>* currNode =
            root;            // we'll start our searching from the root
        bool found = false;  // we'll use this to loop through our tree

        while (!found) {
            if (currNode == nullptr)  // this will happen if node is not in tree
                break;                // leave the loop, return null
            if (item < currNode->data) {  // search left
                currNode = currNode->left;
            } else if (currNode->data < item) {  // search right
                currNode = currNode->right;
            } else {  // we found it, return the node with the correct data
                found = true;
            }
        }

        // once we're out of the while loop, currNode will be null or correct
        // node
        return typename BST<Data>::iterator(currNode);
    }

    /** Return the number of items currently in the BST.
     */
    unsigned int size() const { return isize; }

    /** Return the height of the BST.
     */
    unsigned int height() const { return iheight; }

    /** Return true if the BST is empty, else false.
     */
    bool empty() const {
        if (root == 0)  // root will point to null if BST is empty
            return true;
        return false;
    }

    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    iterator begin() const {
        // return typename BST<Data>::iterator(somethinghere);
        // return leftmost element
        return typename BST<Data>::iterator(first(root));
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    vector<Data> inorder() const {
        vector<Data> values;
        inorder(root, values);
        return values;
    }

  private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    void inorder(BSTNode<Data>* n, vector<Data>& values) const {
        /* Pseudo Code:
          if current node is null: return;
          recursively traverse left sub-tree
          print current node data
          recursively traverse right sub-tree
        */
        if (n == nullptr) return;
        inorder(n->left, values);
        values.push_back(n->data);
        inorder(n->right, values);
        return;
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data>* first(BSTNode<Data>* curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudo Code:
          if current node is null: return;
          recursively delete left sub-tree
          recursively delete right sub-tree
          delete current node
        */
        if (n == nullptr) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete (n);
        return;
    }
};

#endif  // BST_HPP
