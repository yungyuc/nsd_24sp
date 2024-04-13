=======================
Root Finding Algorithms
=======================

Basic Information
=================

Github Repository: https://github.com/ravencyan/Root-Finding-Algorthms

Problem to Solve & Prospective Users
====================================

When it comes to finding the solution of equations, root finding algorithms are
important for solving them in a numerical way. The prospective users can vary
accross different fields, for example, engineers, physicists, computer scientists,
financial analysts. Among the existing algorithms, the performance in terms of
conversion rate, computational efficiency and robustness need to be compared and
verified. In addition, conditions such as initial guesses, convergence criteria,
and handling special cases need to be taken into consideration.

System Architecture
===================

The program will provide an prompt for the user to input an equation in the format:
:math:`f(x)=0`. The system will then run all implemented algorithms and compare
the performance between them. Finally, the program will show the calculated
root and the comparison table for the user.


API Description
===============

- The algorithms will be developed in ``C++``.
- ``pybind11`` will be used to wrap the API in ``Python``.

Engineering Infrastructure
==========================

- ``CMake`` will be used to build the program.
- ``git`` will be used for version control.
- ``pytest`` will be used for unit tests.
- A ``README.rst`` file will be used for documentation.

Schedule
========

* Week 1 (04/08): Search for the root finding algorithms to be implemented in the program, and get a thorough understanding on them.
* Week 2 (04/15): Implement 2-3 algorithms and perform unit tests to check if they are valid.
* Week 3 (04/22): Add functions in the algorithms to record their performance for comparison.
* Week 4 (04/29): Build the input prompt for users to input equations.
* Week 5 (05/06): Put the algorithms, input prompt, output, and comparison table together into a API.
* Week 6 (05/13): Add 1-2 more algoirthms. Optimize the codes (all).
* Week 7 (05/20): Final check for any potential bugs, update the documentation to the final version.
* Week 8 (05/27): Prepare for the presentation

References
==========
