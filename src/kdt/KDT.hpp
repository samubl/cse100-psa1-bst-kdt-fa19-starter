#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of curDim of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    void build(vector<Point>& points) {
        if (points.size() == 0) {  // we'll have an empty tree
            isize = 0;
            iheight = -1;
            root = nullptr;
            return;
        }

        // establish root point
        sort(points.begin(), points.end(), CompareValueAt(0));
        // get the median to be the root, update size and height
        unsigned int median = floor((0 + points.size()) / 2);
        root = new KDNode(points.at(median));
        isize = 1;
        iheight = 0;
        unsigned int currHeight = iheight;  // pass a height value
        unsigned int currDim = 1;

        if (points.size() != isize) {
            // recurisively build the rest of the tree
            root->left =
                buildSubtree(points, 0, median, currDim, currHeight + 1);
            root->right = buildSubtree(points, median + 1, points.size(),
                                       currDim, currHeight + 1);
        }

        return;
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) {
        if (root == 0)  // empty KDT tree
            return (0);

        // recursively traverse down tree to determine nearest neighbor
        threshold = numeric_limits<double>::max();
        findNNHelper(root, queryPoint, 0);

        // we'll've set the nearest neighbor in findNNHelper
        return &nearestNeighbor;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    unsigned int size() const { return isize; }

    int height() const { return iheight; }

  private:
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        // base case, when there is no more nodes to add
        if (start == end) return 0;

        // sort the subsection of the vector to get median depending on curDim
        sort(points.begin() + start, points.begin() + end,
             CompareValueAt(curDim));

        // get median of subsection to find the new root, increment size
        unsigned int median = floor((start + end) / 2);
        KDNode* subtree_root = new KDNode(points.at(median));

        // inc size, height (maybe), and change curDims
        isize++;
        iheight = (iheight < height) ? height : iheight;
        if (curDim == 0)
            curDim = 1;
        else
            curDim = 0;

        // recursively add the rest of the elements of this subtree
        subtree_root->left =
            buildSubtree(points, start, median, curDim, height + 1);

        subtree_root->right =
            buildSubtree(points, median + 1, end, curDim, height + 1);

        return subtree_root;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        if (node == nullptr) {  // we're at a leaf node
            return;
        }

        // update the threshold, if we can
        (node->point).setDistToQuery(queryPoint);
        if ((node->point).distToQuery < threshold) {
            nearestNeighbor = (node->point);
            threshold = (node->point).distToQuery;
        }

        // get the difference on this dimension
        double thisDimDiff = pow(
            (node->point).valueAt(curDim) - queryPoint.valueAt(curDim), 2.0);

        // set up the next dim
        unsigned int nextDim = (curDim + 1) % 2;

        // check to go left
        if (queryPoint.valueAt(curDim) <= node->point.valueAt(curDim)) {
            findNNHelper(node->left, queryPoint, nextDim);  // search left
            // search right if the difference on this dim isn't that great
            if (thisDimDiff < threshold)
                findNNHelper(node->right, queryPoint, nextDim);
        } else {                                             // go right
            findNNHelper(node->right, queryPoint, nextDim);  // search right
            // search left if the difference on this dim isn't that great
            if (thisDimDiff < threshold)
                findNNHelper(node->left, queryPoint, nextDim);
        }

        return;
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    static void deleteAll(KDNode* n) {
        if (n == nullptr) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete (n);
        return;
    }

    // Add your own helper methods here
};
#endif  // KDT_HPP
