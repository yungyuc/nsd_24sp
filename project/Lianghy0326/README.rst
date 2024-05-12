=============================
DE-Project
=============================

C++ Differential Evolution
==========================

Basic Information 
=================

| Github Repository: `DE <https://github.com/Lianghy0326/DE>`_


| Introduction:
| 1. Differential Evolution (DE) is a population based stochastic function 
| optimizer algorithm developed by Kenneth Price and Rainer Storn in the 1990s.

| 2. In computer science, differential evolution (DE) is a method that optimizes a 
| problem by iteratively trying to improve a candidate solution with regard to 
| a given measure of quality.

| Implementation:
| 1. The DE algorithm is implemented in C++.
| 2. The 1st goal of this project is to implement the DE algorithm in C++.

Terminology
===========

Objective Function: 
    The function to be optimized.
Population: 
    a collection of individuals.the population changes according 
    to mutation algorithms to attempt to generate the optimium individual.
Mutation: 
    perturbing the current population
Selection:
    the process of selecting the individuals for the next generation, 
    of the best individual for the current generation, 
    and of the best individual for the entire process.
Generation:
    a single iteration of the algorithm, which transforms one population 
    in a new one, by mutating some of its individuals.



DE Algorithm
============

1. Initialization:
    Create an initial population with random variable values within defined 
    constraints. Evaluate the objective function for each individual.
2. Mutation and Evaluation:
    Iterate through the population and apply mutation according to the policy.
    Enqueue mutated individuals for objective function evaluation.
    Parallel processors evaluate the objective function for enqueued individuals.
3. Selection:
    Choose individuals for the next generation based on a selection policy.
    Maintain the best individual of the current iteration and overall optimization.
4. Generation Update:
    Form the next generation using selected individuals.
5. Termination:
    Repeat steps 2-4 until a termination criterion is met.


Problem to Solve
=================

1. Algorithm Implementation:
    Implement the DE algorithm in C++.
2. Performance Evaluation:
    Evaluate the performance of the implemented DE algorithm.
3. Testing:
    Develop unit tests to validate the correctness of the implementation.
4. Other real use cases(if i have enough time):
    - trading system optimization
    - enhancing algorithmic trading systems by efficiently tuning parameters to 
    - adapt to market conditions, using differential evolution (DE) to reduce the 
    - exploration of vast variable spaces and converge quickly towards optimal solutions.


Prospective Users
=================

- Target Audience
- DE can be useful to many involved in scientific or engineering areas such as: 
    - chemistry, electronics, physics, agriculture, telecommunications, software engineering etc.



System Architecture
===================

Objective Function: 
    Defines the function to be optimized (e.g., "sphere function"). 
    It inherits from the objective_function class and implements 
    the operator() method to calculate the function value.

Processors: 
    Utilizes multiple parallel processors to evaluate function values, 
    speeding up the optimization process. Managed using the processors
    < objective_function_ptr > class.

DE module: 
    Implements the differential evolution algorithm to manage the 
    optimization process.
    
Testing Module: 
    Includes unit tests and performance evaluation tools.

API Description
===============

- objective_function: 
    - The objective_function class defines the interface for an objective function.
    - It includes the operator() method to calculate the function value.
- DE library: 
    - The DE library provides the implementation of the differential evolution algorithm.
    - It includes the DE class to manage the optimization process.

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
