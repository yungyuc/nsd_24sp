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
    Matrix(size_t nrow, size_t ncol); // Basic constructor
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

    
    bool operator==(const Matrix& other) const;

    // Getters and setters
    size_t nrow() const;
    size_t ncol() const;
    double* data();
    const double* data() const;

private:
    size_t nrow_;
    size_t ncol_;
    double* buffer_;
};

Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size = TILE_SIZE);
Matrix multiply_mkl(const Matrix& A, const Matrix& B);