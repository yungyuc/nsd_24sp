#pragma once
#include <iostream>
#include <cstddef>
#include <algorithm> 
#include <iomanip>
#include <chrono>
#include "mkl.h"

const size_t TILE_SIZE = 128;

class Matrix {
public:
    // Constructors
    Matrix(size_t rows, size_t cols); // Basic constructor
    Matrix(const Matrix& other); // Copy constructor
    
    // Copy assignment operator
    Matrix& operator=(const Matrix& other);
    
    // Destructor
    ~Matrix();
    
    // Move constructor
    Matrix(Matrix&& other) noexcept;
    
    // Move assignment operator
    Matrix& operator=(Matrix&& other) noexcept;

    // Matrix operations
    double operator()(size_t row, size_t col) const;
    double& operator()(size_t row, size_t col);

    // Getters and setters
    size_t rows() const;
    size_t cols() const;
    double* data();
    const double* data() const;

private:
    size_t rows_;
    size_t cols_;
    double* buffer_;
};

Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B);
Matrix multiply_mkl(const Matrix& A, const Matrix& B);