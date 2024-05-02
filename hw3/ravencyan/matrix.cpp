#include "matrix.hpp"

#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <algorithm>
#include <cstring>
#include <mkl.h>

Matrix::Matrix() : m_nrow(0), m_ncol(0), m_buffer(nullptr) {}

Matrix::Matrix(const Matrix& other) :  m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(new double[other.m_nrow * other.m_ncol]()) {
    m_nrow = other.m_nrow;
    m_ncol = other.m_ncol;
    m_buffer = new double[m_nrow * m_ncol];
    for (size_t i = 0; i < m_nrow * m_ncol; i++)
        m_buffer[i] = other.m_buffer[i];
}

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[m_nrow * m_ncol]()) {} //Initialize buffer to zeros

bool Matrix::operator==(const Matrix& other) const {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) return false;
    for (size_t i = 0; i < m_nrow; i++)
        for (size_t j = 0; j < m_ncol; j++)
            if (m_buffer[i*m_ncol+j] != other.m_buffer[i*m_ncol+j])
                return false;
    return true;
}

Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2) {
    size_t m = mat1.nrow();
    size_t p = mat1.ncol();
    size_t n = mat2.ncol();

    if (p != mat2.nrow()) {
        throw std::invalid_argument("Second dimension of mat1 must be equal to the first dimension of mat2");
    }

    Matrix result(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < p; k++) {
                result(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }

    return result;
}

Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, size_t tileSize) {
    size_t m = mat1.nrow();
    size_t p = mat1.ncol();
    size_t n = mat2.ncol();

    if (p != mat2.nrow()) {
        throw std::invalid_argument("Second dimension of mat1 must be equal to the first dimension of mat2");
    }

    Matrix result(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < m; i += tileSize) {
        for (size_t j = 0; j < n; j += tileSize) {
            for (size_t k = 0; k < p; k += tileSize) {
                for (size_t ii = i; ii < std::min(i + tileSize, m); ii++) {
                    for (size_t jj = j; jj < std::min(j + tileSize, n); jj++) {
                        for (size_t kk = k; kk < std::min(k + tileSize, p); kk++) {
                            result(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return result;
}

Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2) {
    size_t m = mat1.nrow();
    size_t p = mat1.ncol();
    size_t n = mat2.ncol();

    if (p != mat2.nrow()) {
        throw std::invalid_argument("Second dimension of mat1 must be equal to the first dimension of mat2");
    }

    Matrix result(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m,
                n, p, 1.0, mat1.get_buffer(), p,
                mat2.get_buffer(), n, 0.0, result.get_buffer(), result.ncol());
    return result;
}

namespace py = pybind11;
PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", [](Matrix &self, std::pair<int, int> idx) { return self(idx.first, idx.second); })
        .def("__setitem__", [](Matrix &self, std::pair<int, int> idx, double val) { self(idx.first, idx.second) = val; })
        .def("__eq__", [](const Matrix &mat1, const Matrix &mat2) { return mat1 == mat2; });
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}