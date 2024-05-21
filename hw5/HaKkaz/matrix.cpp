#include "matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

template<typename T> T *CustomAllocator<T>::allocate(size_t n){
    const size_t bytes = n * sizeof(T);
    T *ptr = (T *)(malloc(bytes));

    if (ptr == nullptr){
        throw std::bad_alloc();
    }

    m_byte += bytes;
    m_allocated += bytes;

    return ptr; 
}

template<typename T> void CustomAllocator<T>::deallocate(T *ptr, size_t n){
    const size_t bytes = n * sizeof(T);
    m_deallocated += bytes;
    m_byte -= bytes; 
    free(ptr);
}

template<typename T> size_t CustomAllocator<T>::bytes(){
    return m_byte;
}

template<typename T> size_t CustomAllocator<T>::allocated(){
    return m_allocated;
}

template<typename T> size_t CustomAllocator<T>::deallocated(){
    return m_deallocated;
}



Matrix::Matrix(){
    this->n_row = 0;
    this->n_col = 0;
    this->buf = vector<double, CustomAllocator<double>>();
}


Matrix::Matrix(size_t nrow, size_t ncol){
    n_row = nrow;
    n_col = ncol;
    buf = vector<double, CustomAllocator<double>>(nrow * ncol);
    for(size_t i = 0; i < nrow * ncol; i++){
        buf[i] = 0;
    }
}


Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & numbers){
    n_row = nrow;
    n_col = ncol;
    buf = vector<double, CustomAllocator<double>>(nrow * ncol);
    if(numbers.size() != n_row * n_col){
        throw std::invalid_argument("size of vector does not match matrix size");
    }
    for (size_t i = 0; i < nrow * ncol; i++){
        buf[i] = numbers[i];
    }
}

// Matrix::Matrix(Matrix const & other){
//     n_row = other.n_row;
//     n_col = other.n_col;
//     buf = vector<double, CustomAllocator<double>>(n_row * n_col);
//     for (size_t i = 0; i < n_row * n_col; i++){
//         buf[i] = other.buf[i];
//     }
// }

double Matrix::operator() (size_t row, size_t col) const{
    return buf[index(row, col)];
}

double & Matrix::operator() (size_t row, size_t col){
    return buf[index(row, col)];
}

size_t Matrix::nrow() const{
    return n_row;
}

size_t Matrix::ncol() const{
    return n_col;
}

bool Matrix::operator==(Matrix const & other) const{
    if (n_row != other.n_row || n_col != other.n_col){
        return false;
    }
    for (size_t i = 0; i < n_row * n_col; i++){
        if (buf[i] != other.buf[i]){
            return false;
        }
    }
    return true;
}

// Matrix::~Matrix() {
//     // Add any cleanup code here if necessary
// }

double * Matrix::buffer() const{
    return (double *)buf.data();
}

size_t Matrix::index(size_t row, size_t col) const{
    return row * n_col + col;
}

Matrix multiply_naive(const Matrix &m1, const Matrix &m2){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for (size_t i = 0; i < m1.nrow(); i++){
        for (size_t j = 0; j < m2.ncol(); j++){
            for (size_t k = 0; k < m1.ncol(); k++){
                result(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for (size_t i = 0; i < m1.nrow(); i += tile_size){
        for (size_t j = 0; j < m2.ncol(); j += tile_size){
            for (size_t k = 0; k < m1.ncol(); k += tile_size){
                size_t ii_limit = std::min(i + tile_size, m1.nrow());
                for (size_t ii = i; ii < ii_limit; ii++){
                    size_t jj_limit = std::min(j + tile_size, m2.ncol());
                    for (size_t jj = j; jj < jj_limit; jj++){
                        size_t kk_limit = std::min(k + tile_size, m1.ncol());
                        double tmp = 0;
                        for (size_t kk = k; kk < kk_limit; kk++){
                            tmp += m1(ii, kk) * m2(kk, jj);
                        }
                        result(ii, jj) += tmp;
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiply_mkl(const Matrix &m1, const Matrix &m2){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    Matrix result(m1.nrow(), m2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m1.nrow(), 
                m2.ncol(), 
                m1.ncol(), 
                1.0, 
                m1.buffer(), 
                m1.ncol(), 
                m2.buffer(), 
                m2.ncol(), 
                0.0, 
                result.buffer(), 
                result.ncol());

    return result;
}

// PYBIND11_MODULE(_matrix, m){
//     m.doc() = "Matrix multiplication module";
//     pybind11::class_<Matrix>(m, "Matrix")
//         .def(pybind11::init<>())
//         .def(pybind11::init<size_t, size_t>())
//         .def(pybind11::init<size_t, size_t, std::vector<double> const &>())
//         // .def(pybind11::init<Matrix const &>())
//         .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> const & p, double val){
//             m(p.first, p.second) = val;
//         })
//         .def("__getitem__", [](Matrix &m, std::pair<size_t, size_t> const & p){
//             return m(p.first, p.second);
//         })
//         .def_property_readonly("nrow", &Matrix::nrow)
//         .def_property_readonly("ncol", &Matrix::ncol)
//         .def("__eq__", &Matrix::operator==);
//     m.def("multiply_naive", &multiply_naive);
//     m.def("multiply_tile", &multiply_tile);
//     m.def("multiply_mkl", &multiply_mkl);

//     m.def("bytes", &CustomAllocator<double>::bytes);
// 	m.def("allocated", &CustomAllocator<double>::allocated);
// 	m.def("deallocated", &CustomAllocator<double>::deallocated);
// }