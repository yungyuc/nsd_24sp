========================
Parallel Vonoroi Diagram
========================

Basic Information
=================

Github Repository:

Vonoroi diagram is a partitioning of a plane into regions based on distance to a specific points,
which is widely used in many fields, such as computer graphics and face recognition.
There are some classic algorithms to generate vonoroi diagram, such as divide and conquer method, fortune's algorithm,
and their time complexity is O(nlogn).
However, with large-scale data, these algorithms will become time-consuming.

Problem to Solve
=================

The primary goal if this project is to implement a thread-level parallel version of 
two-dimensional vonoroi diagram algorithm on shared-memory multi-core machines.

For the parallel version, the following requirements should be satisfied:

1. A high-speed data structure for storing the vonoroi diagram and searching the nearby points.
2. K-d tree for decomposing the points into different blocks.
3. ``Fortune's algorithm`` for generating the vonoroi diagram independently at each thread on the blocks assigned to it.

Prospective Users
=================

The prospective users of this project are researchers and developers
who have requirements for generating vonoroi diagram with large-scale data.

System Architecture
===================

This library will be developed in ``C++`` and be compatible with ``Python``.

* ``C++``: Used to implement the core algorithm and parallelization.
* ``Python``: Used to read the input data and visualize the vonoroi diagram.
* ``Pybind11``: Used to wrap the C++ code and make it compatible with Python.

API Description
===============

The ``C++`` API:

.. code-block:: c++

    // Generate vonoroi diagram
    void generate_vonoroi_diagram(const std::vector<Point>& points, VonoroiDiagram& diagram);

    // Get the neighbors of a specific point
    std::vector<Point> get_neighbors(const Point& point, const VonoroiDiagram& diagram);

The ``Python`` API:

.. code-block:: python

    # Generate vonoroi diagram
    diagram = generate_vonoroi_diagram(points)

    # Get the neighbors of a specific point
    neighbors = get_neighbors(point, diagram)

    # draw the vonoroi diagram
    draw_vonoroi_diagram(diagram)

Engineering Infrastructure
==========================

* ``make``: Used to build the software system.
* ``git``: Used for version control.
* ``perf``: Used for performance analysis.
* ``pytest``: Used for unit testing.

Schedule
========

* Week 1 (04/08): Research on ``fortune's algorithm`` and ``k-d tree``.
* Week 2 (04/15): Implement data structure ``Point`` and design input data for testing.
* Week 3 (04/22): Implement data structure ``VonoroiDiagram``.
* Week 4 (04/29)
    * Implement ``fortune's algorithm``.
    * Implement ``draw_vonoroi_diagram`` function.
* Week 5 (05/06): 
    * Testing and debugging for the serial version.
    * Implement ``get_neighbors`` function.
* Week 6 (05/13): Implement the parallel version.
* Week 7 (05/20):
    * Testing and debugging for the parallel version.
    * Wrap the C++ code with ``Pybind11``.
* Week 8 (05/27):
    * Prepare the presentation.

References
==========

* `ParVoro++: A scalable parallel algorithm for constructing 3D Voronoi tessellations based on kd-tree decomposition <https://www.sciencedirect.com/science/article/pii/S0167819123000017>`__