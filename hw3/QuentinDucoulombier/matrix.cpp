#include "matrix.hpp"

Matrix::Matrix(size_t rows, size_t cols) 
    : rows_(rows), cols_(cols), buffer_(new double[rows * cols]) {}

// Copy constructor
Matrix::Matrix(const Matrix& other) 
    : rows_(other.rows_), cols_(other.cols_), buffer_(new double[other.rows_ * other.cols_]) {
    for (size_t i = 0; i < rows_ * cols_; ++i) {
        buffer_[i] = other.buffer_[i];
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) { 
        delete[] buffer_;

        rows_ = other.rows_;
        cols_ = other.cols_;
        buffer_ = new double[rows_ * cols_];
        for (size_t i = 0; i < rows_ * cols_; ++i) {
            buffer_[i] = other.buffer_[i];
        }
    }
    return *this;
}

// Move constructor
Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), buffer_(other.buffer_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.buffer_ = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) { 
        delete[] buffer_; 

        rows_ = other.rows_;
        cols_ = other.cols_;
        buffer_ = other.buffer_;

        other.rows_ = 0;
        other.cols_ = 0;
        other.buffer_ = nullptr;  }
    return *this;
}

Matrix::~Matrix() {
    delete[] buffer_;
}

double Matrix::operator()(size_t row, size_t col) const {
    return buffer_[row * cols_ + col];
}

double& Matrix::operator()(size_t row, size_t col) {
    return buffer_[row * cols_ + col];
}

size_t Matrix::rows() const {
    return rows_;
}

size_t Matrix::cols() const {
    return cols_;
}
