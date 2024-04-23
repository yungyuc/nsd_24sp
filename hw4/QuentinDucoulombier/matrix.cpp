#include "matrix.hpp"

// Basic constructor
Matrix::Matrix(size_t nrow, size_t ncol) 
    : nrow_(nrow), ncol_(ncol), buffer_(nrow * ncol, 0.0) {
    // All initialization is handled by vector's constructor
}

// Copy constructor - Let vector handle the copy
Matrix::Matrix(const Matrix& other)
    : nrow_(other.nrow_), ncol_(other.ncol_), buffer_(other.buffer_) {}

// Copy assignment operator - Let vector handle the copy assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        nrow_ = other.nrow_;
        ncol_ = other.ncol_;
        buffer_ = other.buffer_;
    }
    return *this;
}

// Element access (const and non-const versions)
double Matrix::operator()(size_t row, size_t col) const {
    return buffer_[row * ncol_ + col];
}

double& Matrix::operator()(size_t row, size_t col) {
    return buffer_[row * ncol_ + col];
}

// Comparison operator
bool Matrix::operator==(const Matrix& other) const {
    return nrow_ == other.nrow_ && ncol_ == other.ncol_ && buffer_ == other.buffer_;
}

// Getters
size_t Matrix::nrow() const {
    return nrow_;
} 

size_t Matrix::ncol() const {
    return ncol_;
}

double* Matrix::data() {
    return buffer_.data();
}

const double* Matrix::data() const {
    return buffer_.data();
}

Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
    if (A.ncol() != B.nrow()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    const size_t m = A.nrow();
    const size_t n = B.ncol();
    const size_t k = A.ncol();
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
    if (A.ncol() != B.nrow()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    size_t m = A.nrow();
    size_t n = A.ncol(); 
    size_t p = B.ncol();

    Matrix C(m, p);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            for (size_t k = 0; k < n; ++k) {
                C(i, j)  += A(i, k) * B(k, j);
            }
        }
    }

    return C;
}


Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size) {
    if (A.ncol() != B.nrow()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    size_t m = A.nrow();
    size_t n = A.ncol();
    size_t p = B.ncol();
    Matrix C(m, p);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            C(i, j) = 0;
        }
    }

    // Iterate over tiles
    for (size_t i_tile = 0; i_tile < m; i_tile += tile_size) {
        for (size_t j_tile = 0; j_tile < p; j_tile += tile_size) {
            for (size_t k_tile = 0; k_tile < n; k_tile += tile_size) {
                // Iterate within a tile
                for (size_t i = i_tile; i < std::min(i_tile + tile_size, m); ++i) {
                    for (size_t j = j_tile; j < std::min(j_tile + tile_size, p); ++j) {
                        double sum = 0;
                        for (size_t k = k_tile; k < std::min(k_tile + tile_size, n); ++k) {
                            sum += A(i, k) * B(k, j);
                        }
                        C(i, j) += sum;
                    }
                }
            }
        }
    }

    return C;
}