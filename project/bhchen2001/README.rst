===========================
 Searching based on KD-Tree
===========================

Basic Information
=================

Github Repository: https://github.com/bhchen2001/Searching-based-on-KD-Tree.git

KD-Tree is a data structure that is used to organize multiple dimensions
of data, and is used to perform searches on data. It is a binary tree that
is used to partition the data based on different dimensions.


Problem to Solve
================

The primary goal of this project is to implement a KD-Tree structure
and use it to perform K-Nearest Neighbor search and Range search on
a dataset.

K-Nearest Neighbor search with KD-Tree (pseudo code)::

    L: list of k-nearest neighbors
    1. Traverse the KD-Tree (subtree).
    2. When reaching a leaf node and if it's not visited:
      a. add the point if L is not full
      b. if L is full, replace the farthest point in L with the current point
    3. If current node is root node, return L. Otherwise, go to step 4.
    4. Traverse the parent node and if it's not visited:
      a. add the point if L is not full
      b. if L is full, replace the farthest point in L with the current point
    5. Compare the distance between current point and the hyperplane of the current node and the farthest point in L
      a. If the distance is less than the farthest point in L or L is not full, traverse the other sub-tree (step 1).
      b. If the distance is greater than the farthest point in L, go to step 3.

Range search with KD-Tree (pseudo code)::

    Q: query range, L: list of points within the query range
    1. Traverse the KD-Tree (subtree)
    2. If current node is leaf node, check if the point is within the query range
      a. If the point is within the query range, add it to L.
      b. If the point is not within the query range, do nothing and return
    3. If the current node is not leaf node, check if the region of the current node intersects with the query range
      a. If the region does not overlap Q, return
      b. Else add the point to L if it's within the query range and traverse the left and right sub-trees (step 1).

Prospective Users
=================

The prospective users of this project are researchers and developers
who are interested in multi-dimensional data searching and range queries.

System Architecture
===================

This library will be developed in ``C++`` and be compatible with
``Python``.

* ``C++``: Used to implement the KD-Tree structure and perform the KNN and Range search.
* ``Python``: Used to read the input data.
* ``Pybind11``: Used to wrap the C++ code and make it compatible with Python.

API Description
===============

The ``C++`` API::

    // class to represent a point in multi-dimensional space
    class Point{
        public:
            std::vector<double> coordinates;
    };

    // class to represent a rectangle
    class Rect{
        public:
            Point lower;
            Point upper;
    };

    // class to represent a node in the KD-Tree
    class KDNode {
        public:
            Point point;
            KDNode* left;
            KDNode* right;
            // region that the node belongs to depending on split dimension
            Rect region;
    };

    // class to represent the KD-Tree
    class KDTree {
        public:
            KDTree(std::vector<Point> points);
            void Insert(Point point);
            void Delete(Point point);
            std::vector<Point> KNN(Point point, int k);
            std::vector<Point> RangeSearch(Rect query_range);

        private:
            KDNode* root;
            KDNode* buildKDTree(std::vector<Point> points, int depth);
    };

The ``Python`` API::

    # Generate KD-tree
    my_kd_tree = KDTree(points)
    
    # Insert a point
    my_kd_tree.Insert(point)

    # Delete a point
    my_kd_tree.Delete(point)

    # Perform KNN search
    k_nearest_points = my_kd_tree.KNN(point, k)

    # Perform Range search
    points_in_range = my_kd_tree.RangeSearch(range)

Engineering Infrastructure
==========================

* ``make``: Used to build the software system.
* ``git``: Used for version control.
* ``pytest``: Used for unit testing.

Schedule
========

* Week 1 (04/08): Research on ``KD-Tree``
* Week 2 (04/15): 
  * Implement data structure ``Point``, ``KDNode``
  * Research on ``KNN`` and ``RangeSearch`` based on ``KD-Tree``
  * Design input data for ``Insert`` and ``Delete`` functions
* Week 3 (04/22):
  * Implement ``Insert`` and ``Delete`` functions
  * Design input data for ``KNN`` and ``RangeSearch`` functions
* Week 4 (04/29)
  * Testing and refactoring for ``Insert`` and ``Delete`` functions
  * Implement ``KNN`` searching function
* Week 5 (05/06): 
  * Testing and refactoring for ``KNN`` function
  * Implement ``RangeSearch`` searching function
* Week 6 (05/13): 
  * Testing and refactoring for ``RangeSearch`` function
* Week 7 (05/20):
  * Final testing and refactoring
  * Wrap the C++ code with ``Pybind11``
* Week 8 (05/27):
  * Prepare the presentation