// matrix.cpp

#include <stdexcept>
#include <cstring>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// #include <cblas.h>
// #ifdef HASMKL
#include <mkl.h>
// #include <mkl/mkl_lapack.h>
// #include <mkl/mkl_lapacke.h>
// #endif // HASMKL

#include "matrix.hpp"

Matrix::Matrix() : row_(0), col_(0), buffer_(nullptr) {}

Matrix::Matrix(std::size_t row, std::size_t col)
    : row_(row), col_(col), buffer_(new double[row_ * col_]()) {}

Matrix::Matrix(Matrix const & other) { (*this) = other; }

Matrix & Matrix::operator=(Matrix const & other) {
    if (this != &other) {
        if (buffer_) {
            delete[] buffer_;
        }
        row_ = other.row_;
        col_ = other.col_;
        if (other.size() > 0) {
            buffer_ = new double[other.size()];
            memcpy(buffer_, other.buffer_, other.size() * sizeof(double));
        }
        else {
            buffer_ = nullptr;
        }
    }
    return *this;
}

Matrix::~Matrix() {
    if (buffer_) {
        delete[] buffer_;
    }
}

double   Matrix::operator() (std::size_t row, std::size_t col) const noexcept {
    return buffer_[row * col_ + col];
}

double & Matrix::operator() (std::size_t row, std::size_t col)       noexcept {
    return buffer_[row * col_ + col];
}

bool Matrix::operator==(Matrix const & other) const {
    for (std::size_t i = 0; i < size(); ++i) {
        if (buffer_[i] != other.buffer_[i]) {
            return false;
        }
    }
    return true;
}

std::size_t Matrix::row() const { return row_; }
std::size_t Matrix::col() const { return col_; }
std::size_t Matrix::size() const { return row_ * col_; }
double * Matrix::buffer() const { return buffer_; }

// naive matrix matrix multiplication
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.col() != mat2.row()) {
        throw std::invalid_argument(
            "can't do matrix multiplication due to incompatible shapes");
    }

    Matrix res(mat1.row(), mat2.col());
    for (std::size_t i = 0; i < res.row(); ++i) {
        for (std::size_t j = 0; j < res.col(); ++j) {
            for (std::size_t k = 0; k < mat1.col(); ++k) {
                res(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }
    return res;
}

// tiled matrix matrix multiplication
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, std::size_t tsize) {
    if (mat1.col() != mat2.row()) {
        throw std::invalid_argument(
            "can't do matrix multiplication due to incompatible shapes");
    }

    Matrix res(mat1.row(), mat2.col());
    for (std::size_t i = 0; i < mat1.row(); i += tsize) {
        for (std::size_t j = 0; j < mat2.col(); j += tsize) {
            for (std::size_t k = 0; k < mat1.col(); k += tsize) {
                std::size_t const ii_range = std::min(i + tsize, mat1.row());
                for (std::size_t ii = i; ii < ii_range; ++ii) {
                    std::size_t const jj_range = std::min(j + tsize, mat2.col());
                    for (std::size_t jj = j; jj < jj_range; ++jj) {
                        std::size_t const kk_range = std::min(k + tsize, mat1.col());
                        double temp_sum = 0.0;
                        for (std::size_t kk = k; kk < kk_range; ++kk) {
                            temp_sum += mat1(ii, kk) * mat2(kk, jj);
                            // res(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                        res(ii, jj) += temp_sum;
                    }
                }
            }
        }
    }
    return res;
}

// MKL DGEMM matrix matrix multiplication
// DGEMM (double-precision general matrix multiply)
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.col() != mat2.row()) {
        throw std::invalid_argument(
            "can't do matrix multiplication due to incompatible shapes");
    }
    
    double alpha = 1.0, beta = 0.0;
    Matrix res(mat1.row(), mat2.col());

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
        mat1.row(), mat2.col(), mat1.col(), 
        alpha, 
        mat1.buffer(), mat1.col(), 
        mat2.buffer(), mat2.col(), 
        beta, 
        res.buffer(), res.col()
    );
    return res;
}

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        // default constructor
        .def(py::init<>()) 
        // constructor with size
        .def(py::init<std::size_t, std::size_t>())
        // copy constructor
        .def(py::init<const Matrix &>())

        // get size
        .def_property_readonly("nrow", &Matrix::row)
        .def_property_readonly("ncol", &Matrix::col)

        // element access
        .def("__setitem__", [](Matrix &m, std::vector<std::size_t> idx, double val) { 
            m(idx[0], idx[1]) = val; 
        })
        .def("__getitem__", [](Matrix const &m, std::vector<std::size_t> idx) { 
            return m(idx[0], idx[1]); 
        })

        // equality
        .def("__eq__", &Matrix::operator==);
        
    // naive matrix matrix multiplication
    m.def("multiply_naive", &multiply_naive, "");
    // tiled matrix matrix multiplication
    m.def("multiply_tile", &multiply_tile, "");
    // MKL DGEMM matrix matrix multiplication
    m.def("multiply_mkl", &multiply_mkl, "");
}
