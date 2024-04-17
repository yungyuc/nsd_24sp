#pragma once
#include <vector>
#include <iostream>

class Matrix {

public:
    Matrix();
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);
    

    // TODO: copy and move constructors and assignment operators.
    Matrix(Matrix const & );
    Matrix(Matrix       &&);
    Matrix & operator=(Matrix const & ); // copy assignment operator.
    Matrix & operator=(Matrix       &&);

    ~Matrix();

    double operator() (size_t row, size_t col) const;
    double& operator() (size_t row, size_t col);
    bool operator== (const Matrix& other) const;

    size_t nrow() const;
    size_t ncol() const;

    
    double* buffer() const;


private:
    size_t m_nrow;
    size_t m_ncol;
    double * m_buffer;

};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

// There are totally 5 points in this homework assignment.

// 1. Develop a two-dimensional Matrix class (you may reuse the code in the course
//    note) in C++.  (2 points)

//    1. Implement a free function performing naive Matrix-Matrix multiplication.
//       Name it ``multiply_naive()``.
//    2. Implement a free function performing Matrix-Matrix multiplication with
//       tiling.  Name it ``multiple_tile()``.
//    3. Implement a free frunction that uses ``DGEMM`` for the multiplication.
//       Name it ``multiply_mkl()``.
// 2. Make Python unit tests for the C++ Matrix class and multiplication
//    functions.  (1 point)

//    1. Use the same names in Python.
//    2. The unit tests should support py.test.
//    3. ``make test`` should run the same unit tests.
// 3. Make sure the answers from the two multiplication functions match.  (1
//    point)
// 4. Time the two multiplication functions and compare the performance. Then output
//    ``performance.txt``. The format of ``performance.txt`` can be any. Just make
//    it reasonable.  (1 point)