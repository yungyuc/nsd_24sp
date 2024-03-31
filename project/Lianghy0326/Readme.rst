=============================
Path Finding Using Algorithms
=============================

Basic Information
=================

Github Repository: https://github.com/Lianghy0326/Path-finding-visualization

Pathfinding is a fundamental problem in computer science and has numerous applications in various domains, including robotics, video games, and network routing. 
The objective of pathfinding algorithms is to find the optimal path between two points in a given environment while considering obstacles, costs, and other constraints.
In this project, we aim to explore and implement different pathfinding algorithms, such as A* (A-star), Depth-First Search (DFS), and possibly others, to address the diverse needs of users in path planning scenarios. Through this endeavor, we seek to provide researchers and developers with a versatile toolkit for efficiently navigating complex environments and finding optimal paths. Additionally, we will develop visualization tools to aid in understanding the behavior and performance of these algorithms.

Problem to Solve
=================

The primary goal of this project is to implement various pathfinding algorithms, including A*, DFS, etc., and visualize the paths they generate.

Prospective Users
=================

The prospective users of this project are researchers and developers who have requirements for pathfinding in large-scale environments.

System Architecture
===================

This library will be developed in ``C++`` .
``Python`` library will be used if nessesary.
* ``C++``: Used to implement the algorithm .


API Description
===============

The ``C++`` API::

    // Find a path using A* algorithm
    Path find_path_a_star(const Grid& grid, const Point& start, const Point& goal);

    // Find a path using Depth-First Search algorithm
    Path find_path_dfs(const Grid& grid, const Point& start, const Point& goal);


The ``Python`` API::

    # Find a path using A* algorithm
    path_a_star = find_path_a_star(grid, start, goal)

    # Find a path using Depth-First Search algorithm
    path_dfs = find_path_dfs(grid, start, goal)


Engineering Infrastructure
==========================

* ``make``: Used to build the software system.
* ``git``: Used for version control.
* ``pytest``: Used for unit testing.

Schedule
========

* Week 1 (04/08): Research on A* algorithm and DFS.
* Week 2 (04/15): Implement basic data structures and design input data for testing.
* Week 3 (04/22): Implement A* algorithm.
* Week 4 (04/29): Implement DFS algorithm.
* Week 5 (05/06): Visualizing and debugging for both algorithms.
* Week 6 (05/13): Implement additional pathfinding algorithms.
* Week 7 (05/20): Testing and debugging for all implemented algorithms.
* Week 8 (05/27): Prepare the presentation.

References
==========
