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



// /**
//  * @author FURGER Achille (furgerachi@cy-tech.fr)
//  * @version 0.1
//  * @date 05-04-2024
//  * 
//  * @brief Implementation of the naive matrix-matrix multiplication (you said we could use the code in the course note)
//  * 
//  * @param mat1 
//  * @param mat2 
//  * @return Matrix 
//  */
Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2) {
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
            result(i, j) = sum;  // Directly setting the value in the result matrix.
        }
    }

    return result;
}

/**
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 05-04-2024
 * 
 * @brief Implementation of the tiled matrix-matrix multiplication for perfomance optimization
 * 
 * @param mat1 
 * @param mat2 
 * @return Matrix 
 */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, const size_t tile_size){
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix res(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); ++i) {
        for (size_t j = 0; j < mat2.ncol(); ++j) {
            res(i, j) = 0.0;  // Explicit initialization
        }
    }
    // First, we 'create' and iterate over the different tiles
    for(size_t i_tile = 0; i_tile< mat1.nrow(); i_tile = i_tile + tile_size){
        for(size_t j_tile = 0; j_tile < mat2.ncol(); j_tile = j_tile + tile_size){
            for(size_t k_tile = 0; k_tile < mat1.ncol(); k_tile = k_tile + tile_size){
    // And now we iterate inside each tile
                for(int i = i_tile; i < std::min(int(i_tile + tile_size), int(mat1.nrow())); i++){
                    for(int j = j_tile; j < std::min(int(j_tile + tile_size), int(mat2.ncol())); j++){
                        double sum = 0;
                        for(int k = k_tile; k < std::min(int(k_tile + tile_size), int(mat1.ncol())); k++){
                            sum = sum + mat1(i,k)*mat2(k,j);
                        }
                        res(i,j) = res(i,j) + sum;
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
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m,
                n, p, 1.0, mat1.get_buffer(), p,
                mat2.get_buffer(), n, 0.0, result.get_buffer(), result.ncol());
    return result;
}