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

double* Matrix::data() {
    return buffer_;
}

const double* Matrix::data() const {
    return buffer_;
}

Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    const size_t m = A.rows();
    const size_t n = B.cols();
    const size_t k = A.cols();
    Matrix C(m, n);

    const double alpha = 1.0;
    const double beta = 0.0;
 
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k,
                alpha, A.data(), k,
                B.data(), n,
                beta, C.data(), n);

    return C;
}

Matrix multiply_naive(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    size_t m = A.rows();
    size_t n = A.cols(); 
    size_t p = B.cols();

    Matrix C(m, p);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }

    return C;
}


Matrix multiply_tile(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }
    
    size_t m = A.rows();
    size_t n = A.cols();
    size_t p = B.cols();
    Matrix C(m, p);
    
    
    for (size_t i = 0; i < m; i += TILE_SIZE) {
        for (size_t k = 0; k < n; k += TILE_SIZE) {
            for (size_t j = 0; j < p; j += TILE_SIZE) {
                for (size_t ii = i; ii < std::min(i + TILE_SIZE, m); ++ii) {
                    for (size_t kk = k; kk < std::min(k + TILE_SIZE, n); ++kk) {
                        double r = A(ii, kk);
                        for (size_t jj = j; jj < std::min(j + TILE_SIZE, p); ++jj) {
                            C(ii, jj) += r * B(kk, jj);
                        }
                    }
                }
            }
        }
    }
    
    return C;
}