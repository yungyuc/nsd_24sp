#include "matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

Matrix::Matrix(size_t nrow, size_t ncol){
    n_row = nrow;
    n_col = ncol;
    buf = (double *) calloc(nrow * ncol, sizeof(double));
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & numbers){
    n_row = nrow;
    n_col = ncol;
    buf = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++){
        buf[i] = numbers[i];
    }
}

Matrix::Matrix(Matrix const &other){
    n_row = other.n_row;
    n_col = other.n_col;
    buf = new double[n_row * n_col];
    for (size_t i = 0; i < n_row * n_col; i++){
        buf[i] = other.buf[i];
    }
}

Matrix::~Matrix(){
    delete[] buf;
}

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

bool Matrix::operator==(Matrix const & other) const {
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

double* Matrix::buffer() const {
    return buf;
}

size_t Matrix::index(size_t row, size_t col) const {
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
                size_t mn_i = std::min(i + tile_size, m1.nrow());
                size_t mn_j = std::min(j + tile_size, m2.ncol());
                size_t mn_k = std::min(k + tile_size, m1.ncol());
                for (size_t ii = i; ii < mn_i; ii++){
                    for (size_t jj = j; jj < mn_j; jj++){
                        double tmp = 0;
                        for (size_t kk = k; kk < mn_k; kk++){
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