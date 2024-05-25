#include "matrix.hpp"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>



Matrix::Matrix(){
    this->rows = 0;
    this->cols = 0;
    this->m_buffer = nullptr;
}

Matrix::Matrix(size_t nrow, size_t ncol){
    this->rows = nrow;
    this->cols = ncol;
    this->m_buffer = new double[nrow * ncol];
    for(size_t i = 0; i < nrow * ncol; i++){
        this->m_buffer[i] = 0;
    }
}

Matrix::Matrix(size_t row, size_t col, double val){
    this->rows = row;
    this->cols = col;
    this->m_buffer = new double[row * col];
    for(size_t i = 0; i < row * col; i++){
        this->m_buffer[i] = val;
    }
}

Matrix::Matrix(size_t row, size_t col,const std::vector<double> &v){
    this->rows = row;
    this->cols = col;
    this->m_buffer = new double[row * col];
    if(v.size() != row * col){
        throw std::invalid_argument("size of vector does not match matrix size");
    }
    for(size_t i = 0; i < row * col; i++){
        this->m_buffer[i] = v[i];
    }
}
Matrix::Matrix(const Matrix &m){
    this->rows = m.rows;
    this->cols = m.cols;
    this->m_buffer = new double[m.rows * m.cols];
    for(size_t i = 0; i < m.rows * m.cols; i++){
        this->m_buffer[i] = m.m_buffer[i];
    }
} 

size_t Matrix::index(size_t i, size_t j) const{
    return i * cols + j;
}
size_t Matrix::nrow() const{
    return rows;
}
size_t Matrix::ncol() const{
    return cols;
}

double* Matrix::get_buffer() const{
    return m_buffer;
}
    
Matrix::~Matrix() {
    delete[] m_buffer;
}

double Matrix::operator() (size_t row, size_t col) const{
    if (row < 0 || row >= rows || col < 0 || col > cols){
        throw std::out_of_range("index out of range");
    }
    return m_buffer[index(row, col)];
}
double &Matrix::operator() (size_t row, size_t col){
    if (row < 0 || row >= rows || col < 0 || col > cols){
        throw std::out_of_range("index out of range");
    }
    return m_buffer[index(row, col)];
}

bool Matrix::operator==(const Matrix &m) const{
    if(this->rows != m.rows || this->cols != m.cols){
        return false;
    }
    for(size_t i = 0; i < this->rows * this->cols; i++){
        if(this->m_buffer[i] != m.m_buffer[i]){
            return false;
        }
    }
    return true;
}

Matrix &Matrix::operator=(const Matrix &m){
    if(this == &m){
        return *this;
    }
    if(this->m_buffer != nullptr){
        delete[] this->m_buffer;
    }
    this->rows = m.nrow();
    this->cols = m.ncol();
    this->m_buffer = new double[m.nrow() * m.ncol()];
    std::memcpy(this->m_buffer, m.get_buffer(), m.nrow() * m.ncol() * sizeof(double));
    return *this;
}

// Add pybind11 array
pybind11::array_t<double> Matrix::array() const {

    // use c_style and forecast to create numpy array
    return pybind11::array_t<double>(
        // shape
        {rows, cols},
        // stride of the array
        {cols*sizeof(double), sizeof(double)},
        // pointer to the m_buffer
        m_buffer,
        // cast to python object
        pybind11::cast(this)); // To make sure that the lifetime of the array is bound to the matrix object
        // flags
        // pybind11::array::c_style | pybind11::array::forcecast // c_style is the default, forcecast is needed to cast the pointer to the object
}// 接著要將 Matrix 類綁定到 Python Module 的代碼



Matrix multiply_naive(Matrix const &m1, Matrix const &m2){
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

// add pybind11 module
PYBIND11_MODULE(_matrix, m) {
    m.doc() = "Matrix multiplication module";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<>())  // Default constructor
        .def(pybind11::init<size_t, size_t>())  // Constructor with rows and cols
        .def(pybind11::init<size_t, size_t, double>())  // Constructor with rows, cols, and initial value
        .def(pybind11::init<size_t, size_t, const std::vector<double>&>())  // Constructor with rows, cols, and vector
        .def(pybind11::init<const Matrix&>())  // Copy constructor

        .def("nrow", &Matrix::nrow)  // Number of rows
        .def("ncol", &Matrix::ncol)  // Number of cols
        .def("get_buffer", &Matrix::get_buffer)  // Get the buffer

        .def("array", &Matrix::array)  // Convert to numpy array

        .def("__call__", (double (Matrix::*)(size_t, size_t) const) &Matrix::operator())  // Call operator for const objects
        .def("__call__", (double& (Matrix::*)(size_t, size_t)) &Matrix::operator())  // Call operator for non-const objects

        .def("__eq__", &Matrix::operator==)  // Equality operator
        .def("__assign__", &Matrix::operator=)  // Assignment operator
        .def("__repr__",
             [](const Matrix &m) {
                 return "<Matrix with " + std::to_string(m.nrow()) + " rows and " + std::to_string(m.ncol()) + " cols>";
             });

    m.def("multiply_naive", &multiply_naive, "Naive matrix multiplication");
    m.def("multiply_tile", &multiply_tile, "Tiled matrix multiplication");
    m.def("multiply_mkl", &multiply_mkl, "Matrix multiplication using MKL");
}