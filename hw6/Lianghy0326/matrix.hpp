#include <vector>
#include<iostream>
#include<mkl/mkl.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

using namespace std;

class Matrix{
private:
    size_t rows, cols;
    double *m_buffer;

public:
    // Default constructor
    Matrix(size_t nrow, size_t ncol);
    // Constructor with specified number of rows and columns
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);

    // Constructor with specified number of rows and columns, and initialization vector
    Matrix(size_t nrow, size_t ncol, const vector<double> &v);
    // Copy constructor
    Matrix(const Matrix &m);
    // Destructor
    ~Matrix();

    // Get the linear index of the element at position (i, j)
    size_t index(size_t i, size_t j) const;
    // Get the number of rows
    size_t nrow() const;
    // Get the number of columns
    size_t ncol() const;
    // Get a pointer to the buffer containing the matrix data
    double* get_buffer() const;

    // Accessor for reading matrix elements
    double operator() (size_t row, size_t col) const;
    // Accessor for modifying matrix elements
    double & operator() (size_t row, size_t col);

    // Comparison operator for checking equality of matrices
    bool operator==(const Matrix &m) const;

    Matrix & operator=(const Matrix &m);

    // new
    pybind11::array_t<double> array() const;

};

Matrix multiply_naive(Matrix const &m1, Matrix const &m2);
Matrix multiply_tile(Matrix const &m1, Matrix const &m2, std::size_t size);
Matrix multiply_mkl(Matrix const &m1, Matrix const &m2);