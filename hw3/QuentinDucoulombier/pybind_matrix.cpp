#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "matrix.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("__getitem__", [](const Matrix &m, std::pair<size_t, size_t> idx) {
            if (idx.first >= m.nrow() || idx.second >= m.ncol()) {
                throw std::out_of_range("Matrix index out of range");
            }
            return m(idx.first, idx.second);
        })
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> idx, double val) {
            if (idx.first >= m.nrow() || idx.second >= m.ncol()) {
                throw std::out_of_range("Matrix index out of range");
            }
            m(idx.first, idx.second) = val;
        })
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__eq__", &Matrix::operator==, py::is_operator())
    ;

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile, 
          py::arg("A"), py::arg("B"), py::arg("tile_size") = TILE_SIZE,  // Providing default value
          "Multiply two matrices using tiling with an optional tile size.");
    m.def("multiply_mkl", &multiply_mkl); 
}
