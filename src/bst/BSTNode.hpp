#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>
class BSTNode {
  public:
    /** Constructor.  Initialize a BSTNode with the given Data item,
     *  no parent, and no children.
     */
    BSTNode(const Data& d) : data(d) { left = right = parent = 0; }

    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** Return the successor of this BSTNode in a BST, or 0 if none.
     ** PRECONDITION: this BSTNode is a node in a BST.
     ** POSTCONDITION:  the BST is unchanged.
     ** RETURNS: the BSTNode that is the successor of this BSTNode,
     ** or 0 if there is none.
     */
    BSTNode<Data>* successor() {
        BSTNode<Data>* currNode = 0;

        // if node has a right child, the successor must be smallest node to the
        // right
        if (right != 0) {
            currNode = right;
            // traverse to right child, and then as far left as possible
            while (currNode->left != 0) currNode = currNode->left;
            // we have the leftmost node that is to the right of the original
            // node
            return currNode;
        }

        // check parent nodes if there is no right children
        if (parent != 0) {
            // check if we're already the left child
            if (parent->left == this) return parent;
            // traverse up the tree to find a left child of its parent
            currNode = parent;
            while (currNode->parent != 0) {
                // we hope find a node that is the left child of its parent
                if (currNode->parent->left == currNode) return currNode->parent;
                currNode = currNode->parent;
            }
        }

        // there is no successor, this is the maximum element in the tree
        return 0;
    }
};

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
