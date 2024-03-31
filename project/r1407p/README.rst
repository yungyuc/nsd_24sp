PyMatrixOpt
=========================

Basic Information
-----------------
Project name: `PyMatrixOpt <https://github.com/r1407p/PyMatrixOpt>`_
PyMatrixOpt is a Python matrix library with optimizations for 
improved performance. 
It provides various matrix operations and optimizations to 
enhance computational efficiency.

Problem to Solve
----------------
Matrix operations and linear algebra computations are fundamental
in various scientific and mathematical fields, 
particularly in domains like deep learning. 
However, a critical challenge lies in optimizing computation speed 
to handle large datasets efficiently. 

1. Parallel Optimization: 
    Developing parallel computing techniques to leverage multi-core processors 
    or distributed computing environments, 
    thereby enhancing computation speed for matrix operations.
2. SIMD Optimization: 
    Implementing Single Instruction, 
    Multiple Data (SIMD) optimizations to accelerate matrix operations by 
    processing multiple data elements simultaneously.
3. Cache Optimization: 
    Utilizing cache optimization techniques to minimize cache misses and 
    improve memory access patterns, 
    thereby enhancing computational efficiency.
4. Algorithmic Optimization: 
    Implementing optimized algorithms for matrix operations, 
    such as matrix multiplication, matrix addition, and matrix inversion, 
    to reduce computational complexity and improve performance.

Prospective Users
------------------
- Software Developers: 
    Software developers building applications requiring intensive mathematical computations, 
    such as optimization algorithms, signal processing, and computer graphics, 
    can integrate the DataFrame library to improve performance and efficiency. 
- Machine Learning Engineers: 
    Machine learning engineers developing and deploying machine learning models 
    will find the optimized DataFrame library valuable for 
    performing data preprocessing, 
    feature engineering, and model training. 
    The efficient linear algebra computations 
    can accelerate model training and inference tasks, 
    leading to improved performance and scalability.
- Data Scientists and Analysts: 
    Data scientists and analysts working with large datasets in fields such as 
    machine learning, data mining, and statistical analysis will 
    benefit from the optimized DataFrame library. 
    They can leverage the efficient matrix operations and linear algebra 
    computations for faster data processing and analysis.

System Architecture
---------------------
- Using ``C++`` to implement the algorithm.
- Using ``pybind11`` to make API in python.

API Description
----------------
The provided C++ API allows users to perform various matrix operations efficiently 
using the Matrix class. 
Below is an overview of the functionalities and how to use them:
and we will use pybind11 to make the API in python.

.. code-block:: cpp

    #include <Matrix.h>

    Matrix matrix1 = Matrix::load_data(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}});
    vector<vector<int>> data = matrix1.get_data();

    auto multiply = matrix1.multiply(matrix2);
    auto add = matrix1.add(matrix2);
    auto subtract = matrix1.subtract(matrix2);

    auto determinant = matrix1.determinant();
    auto inverse = matrix1.inverse();
    auto transpose = matrix1.transpose();
    auto rank = matrix1.rank();
    auto row_echelon = matrix1.row_echelon();
    auto diagonal = matrix1.diagonal();
    auto power = matrix1.power(2);
    auto LU_decomposition = matrix1.LU();

Engineering Infrastructure
---------------------------
- Use ``CMake`` to build the binaries.
- Use ``git`` for version control.
- Use ``pytest`` for testing the performance and correctness.

Schedule
---------
- Week 1 (4/8): Research the matrix optimization algorithm and implement the 
C++ version of the algorithm.
- Week 2 (4/15): Write unit test.
- Week 3 (4/22): Implement the method in C++ class and write the function.
- Week 4 (4/29): Finish the basic API function.
- Week 5 (5/6): Add parallel computing to the algorithm.
- Week 6 (5/13): Performance test and bug fix.
- Week 7 (5/20): Optimize the algorithm.
- Week 8 (5/27): Document the code and prepare for presentation

Reference
----------
- https://aprilyang.home.blog/2021/12/24/matrix-multiplication-in-c/
- https://juejin.cn/s/c%2B%2B%20matrix%20multiplication%20simd
- https://blog.csdn.net/weixin_55035144/article/details/131844687
- https://zh.wikipedia.org/zh-tw/%E6%96%BD%E7%89%B9%E6%8B%89%E6%A3%AE%E6%BC%94%E7%AE%97%E6%B3%95
