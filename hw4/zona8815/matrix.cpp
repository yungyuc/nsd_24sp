// matrix.cpp

#include <stdexcept>
#include <cstring>
#include <vector>
#include <limits>
#include <memory>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <mkl.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

// for hw4

template <class T> 
class CustomAllocator {
public:
    using value_type = T;
    CustomAllocator() = default;
    T *allocate(std::size_t n);
    void deallocate(T *ptr, std::size_t n);
    static std::size_t bytes();
    static std::size_t allocated();
    static std::size_t deallocated();

private:
    // used bytes
    static std::size_t byte_;
    // allocated bytes
    static std::size_t allocated_;
    // deallocated bytes
    static std::size_t deallocated_;
};

// initialize the static variables
template <class T> 
std::size_t CustomAllocator<T>::byte_ = 0;
template <class T> 
std::size_t CustomAllocator<T>::allocated_ = 0;
template <class T> 
std::size_t CustomAllocator<T>::deallocated_ = 0;

template <class T> 
T *CustomAllocator<T>::allocate(std::size_t n) {
    // check if the size is reasonable
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
        throw std::bad_alloc();
    }

    // allocate
    const std::size_t bytes = n * sizeof(T);
    T *ptr = (T *)(std::malloc(bytes));

    // check if allocation is successful
    if (ptr == nullptr) {
        throw std::bad_alloc();
    }

    // count bytes
    byte_ += bytes;
    allocated_ += bytes;

    return ptr;
}

template <class T> 
void CustomAllocator<T>::deallocate(T *ptr, std::size_t n) {
    const std::size_t bytes = n * sizeof(T);

    // free the memory
    std::free(ptr);

    // count bytes
    byte_ -= bytes;
    deallocated_ += bytes;
}

// return byte_ (used bytes)
template <class T> 
std::size_t CustomAllocator<T>::bytes() { return byte_; }

// return allocated_ (allocated bytes)
template <class T> 
std::size_t CustomAllocator<T>::allocated() { return allocated_; }

// return deallocated_ (deallocated bytes)
template <class T> 
std::size_t CustomAllocator<T>::deallocated() { return deallocated_; }

// hw3

class Matrix {
public:
    // default constructor
    Matrix();

    // constructor with size
    Matrix(std::size_t row, std::size_t col);
    // constructor with data
    Matrix(std::size_t row, std::size_t col, std::vector<double> const &data);

    // copy constructor
    // Matrix(Matrix const & other);

    // copy assignment (release old buffer and copy new buffer)
    // Matrix & operator=(Matrix const & other);

    // deconstructor
    // ~Matrix();

    // element access
    double   operator() (std::size_t row, std::size_t col) const noexcept;
    double & operator() (std::size_t row, std::size_t col)       noexcept;

    // equality
    bool operator==(Matrix const & other) const;
    // inequality
    bool operator!=(Matrix const & other) const;

    // shape of row
    std::size_t row() const;
    // shape of col
    std::size_t col() const;
    // size
    std::size_t size() const;
    // data
    double * buffer() const;
    
private:
    // shape of row
    std::size_t row_ = 0;
    // shape of col
    std::size_t col_ = 0;
    // data
    std::vector<double, CustomAllocator<double>> buffer_;
};

Matrix::Matrix() : row_(0), col_(0), buffer_({}) {}

Matrix::Matrix(std::size_t row, std::size_t col)
    : row_(row), col_(col), buffer_(std::vector<double, CustomAllocator<double>>(row * col)) {}

Matrix::Matrix(std::size_t row, std::size_t col, std::vector<double> const &data) {
    // copy data
    row_ = row;
    col_ = col;
    buffer_ = std::vector<double, CustomAllocator<double>>(row * col);
    for (std::size_t i = 0; i < data.size(); i++) {
        buffer_[i] = data[i];
    }
}

// Matrix::Matrix(Matrix const & other) { (*this) = other; }

// Matrix & Matrix::operator=(Matrix const & other) {
//     if (this != &other) {
//         if (buffer_) {
//             delete[] buffer_;
//         }
//         row_ = other.row_;
//         col_ = other.col_;
//         if (other.size() > 0) {
//             buffer_ = new double[other.size()];
//             memcpy(buffer_, other.buffer_, other.size() * sizeof(double));
//         }
//         else {
//             buffer_ = nullptr;
//         }
//     }
//     return *this;
// }

// Matrix::~Matrix() {
//     if (buffer_) {
//         delete[] buffer_;
//     }
// }

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

bool Matrix::operator!=(Matrix const & other) const {
    return !((*this) == other);
}

std::size_t Matrix::row() const { return row_; }
std::size_t Matrix::col() const { return col_; }
std::size_t Matrix::size() const { return row_ * col_; }
double * Matrix::buffer() const { return (double *)buffer_.data(); }

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

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        // default constructor
        .def(py::init<>()) 
        // constructor with size
        .def(py::init<std::size_t, std::size_t>())
        // constructor with data
        .def(py::init<std::size_t, std::size_t, std::vector<double>>())

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
        // inequality
        .def("__ne__", &Matrix::operator!=);
        
    // naive matrix matrix multiplication
    m.def("multiply_naive", &multiply_naive, "");
    // tiled matrix matrix multiplication
    m.def("multiply_tile", &multiply_tile, "");
    // MKL DGEMM matrix matrix multiplication
    m.def("multiply_mkl", &multiply_mkl, "");

    m.def("bytes", &CustomAllocator<double>::bytes, "");
    m.def("allocated", &CustomAllocator<double>::allocated, "");
    m.def("deallocated", &CustomAllocator<double>::deallocated, "");
}
