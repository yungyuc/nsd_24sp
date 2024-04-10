#pragma once
#include <iostream>
#include <cstddef>
#include <algorithm> 

const size_t TILE_SIZE = 16;

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

    // Getters
    size_t rows() const;
    size_t cols() const;

private:
    size_t rows_;
    size_t cols_;
    double* buffer_;
};
