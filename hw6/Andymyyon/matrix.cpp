#include "matrix.hpp"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <algorithm>
#include <cstring>
#include <mkl.h>

namespace py = pybind11;

Matrix::Matrix() : m_nrow(0), m_ncol(0), m_buffer(nullptr) {}

Matrix::Matrix(const Matrix& other) : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(new double[other.m_nrow * other.m_ncol]()) {
    std::memcpy(m_buffer, other.m_buffer, m_nrow * m_ncol * sizeof(double));
}

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[m_nrow * m_ncol]()) {}

bool Matrix::operator==(const Matrix& other) const {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) return false;
    return std::memcmp(m_buffer, other.m_buffer, m_nrow * m_ncol * sizeof(double)) == 0;
}

pybind11::array_t<double> Matrix::to_numpy() const {
    return pybind11::array_t<double>(
        { m_nrow, m_ncol }, // shape
        { m_ncol * sizeof(double), sizeof(double) }, // strides
        m_buffer, // the data pointer
        pybind11::cast(this) // the parent to ensure shared ownership
    );
}

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("The number of columns in the first matrix must match the number of rows in the second matrix.");
    }

    size_t nrow = mat1.nrow(), ncol = mat2.ncol(), ncommon = mat1.ncol();
    Matrix result(nrow, ncol);

    for (size_t i = 0; i < nrow; ++i) {
        for (size_t j = 0; j < ncol; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < ncommon; ++k) {
                sum += mat1(i, k) * mat2(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, const size_t tile_size) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("The number of first matrix column differs from that of second matrix row");
    }

    Matrix res(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); ++i) {
        for (size_t j = 0; j < mat2.ncol(); ++j) {
            res(i, j) = 0.0;
        }
    }

    for (size_t i_tile = 0; i_tile < mat1.nrow(); i_tile = i_tile + tile_size) {
        for (size_t j_tile = 0; j_tile < mat2.ncol(); j_tile = j_tile + tile_size) {
            for (size_t k_tile = 0; k_tile < mat1.ncol(); k_tile = k_tile + tile_size) {
                for (int i = i_tile; i < std::min(int(i_tile + tile_size), int(mat1.nrow())); i++) {
                    for (int j = j_tile; j < std::min(int(j_tile + tile_size), int(mat2.ncol())); j++) {
                        double sum = 0;
                        for (int k = k_tile; k < std::min(int(k_tile + tile_size), int(mat1.ncol())); k++) {
                            sum = sum + mat1(i, k) * mat2(k, j);
                        }
                        res(i, j) = res(i, j) + sum;
                    }
                }
            }
        }
    }

    return res;
}

Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2) {
    size_t m = mat1.nrow();
    size_t p = mat1.ncol();
    size_t n = mat2.ncol();

    if (p != mat2.nrow()) {
        throw std::invalid_argument("Second dimension of mat1 must be equal to the first dimension of mat2");
    }

    Matrix result(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1.0, mat1.get_buffer(), p, mat2.get_buffer(), n, 0.0, result.get_buffer(), result.ncol());
    return result;
}

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<std::size_t, std::size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("get_buffer", &Matrix::get_buffer)
        .def("to_numpy", &Matrix::to_numpy)
        .def_property_readonly("array", &Matrix::to_numpy)
        .def("__getitem__", [](const Matrix& mat, std::pair<std::size_t, std::size_t> idx) {
            return mat(idx.first, idx.second);
        })
        .def("__setitem__", [](Matrix& mat, std::pair<std::size_t, std::size_t> idx, double value) {
            mat(idx.first, idx.second) = value;
        })
        .def(py::self == py::self);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}
