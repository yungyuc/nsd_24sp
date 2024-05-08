=============================
DE
=============================

Automatic Differential Equation Solver Optimizer
================================================

Basic Information
=================

Github Repository: `DE <https://github.com/Lianghy0326/DE>`_

Design an intelligent C++ solver that automatically selects the optimal 
solving method for differential equation (DE) problems. 
The solver should choose the best integration method and step size based 
on problem characteristics to 
maximize solving speed and accuracy.

Problem to Solve
=================

The goal is to develop an intelligent solver capable of automatically selecting 
the most suitable solving method for DE problems. 
This involves analyzing problem characteristics such as initial conditions, 
boundary conditions, and equation forms 
to determine the appropriate integration method and optimization strategies. 

By doing so, we aim to maximize solving speed and accuracy, addressing the 
challenges of efficiently solving DE problems.
Use ODE to perform some intesting problems,
1. 3 body problem
in some certain cases,
we can perform 3-body problem with the help of ODE.
2. Solar system
RK4 method can be used to solve the solar system problem.


Prospective Users
=================

- Researchers and engineers in fields utilizing DEs for modeling and simulation.
- Academic institutions for teaching and research purposes.


System Architecture
===================

* Solver Module: Contains the core logic for analyzing problem characteristics 
and selecting appropriate solving methods.
* Integration Methods: Implementations of various integration methods such 
as Euler's method, Runge-Kutta methods, etc.
* Step Size Control: Module responsible for implementing adaptive step size 
control algorithms.
* Testing Module: Includes unit tests and performance evaluation tools.

API Description
===============

Engineering Infrastructure
==========================

* ``make``: Used to build the software system.
* ``git``: Used for version control.
* ``gtest``: Used for unit testing.

Schedule
========

* Week 1 (04/08): Research
* Week 2 (04/15): Research
* Week 3 (04/22): Research && Implementation
* Week 4 (04/29): Implementation
* Week 5 (05/06): Implementation && Test and debug
* Week 6 (05/13): Test and debug
* Week 7 (05/20): Test and debug
* Week 8 (05/27): Prepare the presentation.

References
==========
None