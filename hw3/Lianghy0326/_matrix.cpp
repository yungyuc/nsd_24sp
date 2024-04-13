#include "_matrix.hpp"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

namespace py=pybind11;

Matrix::Matrix(){
    // Default constructor
    this->crow = 0;
    this->ccol = 0;
    this->data = nullptr;
}

Matrix::Matrix(size_t nrow, size_t ncol){
    // Constructor with specified number of rows and columns
    this->crow = nrow;
    this->ccol = ncol;
    this->data = new double[nrow * ncol];
    for(size_t i = 0; i < nrow * ncol; i++){
        this->data[i] = 0;
    }
}

Matrix::Matrix(size_t row, size_t col, double val){
    // Constructor with specified number of rows, columns, and initialization value
    this->crow = row;
    this->ccol = col;
    this->data = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->data[i] = val;
    }
}

Matrix::Matrix(size_t row, size_t col,const std::vector<double> &v){
    // Constructor with specified number of rows, columns, and initialization vector
    this->crow = row;
    this->ccol = col;
    this->data = new double[row * col];
    if(v.size() != row * col){
        throw std::invalid_argument("size of vector does not match matrix size");
    }
    for(size_t i = 0; i < row * col; i++){
        this->data[i] = v[i];
    }
}

Matrix::Matrix(const Matrix &m){
    // Copy constructor
    this->crow = m.crow;
    this->ccol = m.ccol;
    this->data = new double[m.crow * m.ccol];
    for(size_t i = 0; i < m.crow * m.ccol; i++){
        this->data[i] = m.data[i];
    }
} 

size_t Matrix::index(size_t i, size_t j) const{
    // Get the linear index of the element at position (i, j)
    return i * ccol + j;
}

size_t Matrix::nrow() const{
    // Get the number of rows
    return crow;
}

size_t Matrix::ncol() const{
    // Get the number of columns
    return ccol;
}

double* Matrix::get_buffer() const{
    // Get a pointer to the buffer containing the matrix data
    return data;
}
    
Matrix::~Matrix() {
    // Destructor
    delete[] data;
}

double Matrix::operator() (size_t row, size_t col) const{
    // Accessor for reading matrix elements
    if (row < 0 || row >= crow || col < 0 || col > ccol){
        throw std::out_of_range("index out of range");
    }
    return data[index(row, col)];
}

double &Matrix::operator() (size_t row, size_t col){
    // Accessor for modifying matrix elements
    if (row < 0 || row >= crow || col < 0 || col > ccol){
        throw std::out_of_range("index out of range");
    }
    return data[index(row, col)];
}

bool Matrix::operator==(const Matrix &m){
    // Comparison operator for checking equality of matrices
    if(this->crow != m.crow || this->ccol != m.ccol){
        return false;
    }
    for(size_t i = 0; i < this->crow * this->ccol; i++){
        if(this->data[i] != m.data[i]){
            return false;
        }
    }
    return true;
}

Matrix multiply_naive(Matrix const &m1, Matrix const &m2){
    // Naive matrix multiplication
    if(m1.ncol() != m2.nrow()){
        throw std::invalid_argument("matrix size does not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i++){
        for(size_t j = 0; j < m2.ncol(); j++){
            for(size_t k = 0; k < m1.ncol(); k++){
                result(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return result;
}

Matrix multiply_tile(Matrix const &m1, Matrix const &m2, std::size_t size){
    // Tiled matrix multiplication
    if(m1.ncol() != m2.nrow()){
        throw std::invalid_argument("matrix size does not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for(size_t i = 0; i < m1.nrow(); i += size){
        for(size_t j = 0; j < m2.ncol(); j += size){
            for(size_t k = 0; k < m1.ncol(); k += size){
                for(size_t ii = i; ii < std::min(i + size, m1.nrow()); ii++){
                    for(size_t jj = j; jj < std::min(j + size, m2.ncol()); jj++){
                        for(size_t kk = k; kk < std::min(k + size, m1.ncol()); kk++){
                            result(ii, jj) += m1(ii, kk) * m2(kk, jj);
                        }
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiply_mkl(Matrix const &m1, Matrix const &m2){
    // MKL matrix multiplication
    if(m1.ncol() != m2.nrow()){
        throw std::invalid_argument("matrix size does not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m1.nrow(), m2.ncol(), m1.ncol(),
                1.0, m1.get_buffer(), m1.ncol(),
                m2.get_buffer(), m2.ncol(),
                0.0, result.get_buffer(), result.ncol());

    return result;
}

PYBIND11_MODULE(_matrix, m) {
    // Python bindings using pybind11
    py::class_<Matrix>(m, "Matrix")
    .def(py::init<>())
    .def(py::init<size_t, size_t>())
    .def(py::init<size_t, size_t, double>())
    .def(py::init<size_t, size_t, const std::vector<double> &>())
    .def(py::init<const Matrix &>())
    .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx){ 	 
        return m(idx[0],idx[1]);       
    })
    .def("__setitem__",[](Matrix &m, std::vector<std::size_t> idx, int val){
        m(idx[0],idx[1]) = val;
    })
    .def_property_readonly("nrow", &Matrix::nrow)
    .def_property_readonly("ncol", &Matrix::ncol)
    .def("__eq__", &Matrix::operator ==);

    m.def("multiply_naive", &multiply_naive, "");
    m.def("multiply_tile", &multiply_tile, "");
    m.def("multiply_mkl", &multiply_mkl, "");
}
