#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <math.h>
#include <mkl/mkl.h>
#include <chrono>
#include <fstream>
#include <memory>
#include <algorithm>

#include "matrix.hpp"
#include <cmath>

// Constructor definitions
Matrix::Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol), m_buffer(nrow * ncol) {
}

Matrix::Matrix(size_t nrow, size_t ncol, const std::vector<double>& vec)
    : m_nrow(nrow), m_ncol(ncol), m_buffer(vec.begin(), vec.end()) {
}

Matrix::Matrix(const Matrix& other)
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(other.m_buffer) {
}

Matrix::Matrix(Matrix&& other) noexcept
    : m_nrow(other.m_nrow), m_ncol(other.m_ncol), m_buffer(std::move(other.m_buffer)) {
    other.m_nrow = 0;
    other.m_ncol = 0;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = other.m_buffer;
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = std::move(other.m_buffer);
        other.m_nrow = 0;
        other.m_ncol = 0;
    }
    return *this;
}

Matrix::~Matrix() {
    // Destructor does not need to manually deallocate memory since we are using CustomVector
}

bool Matrix::operator==(const Matrix& other) const {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) return false;
    return std::equal(m_buffer.begin(), m_buffer.end(), other.m_buffer.begin());
}

double Matrix::operator()(size_t row, size_t col) const {
    return m_buffer[index(row, col)];
}

double& Matrix::operator()(size_t row, size_t col) {
    return m_buffer[index(row, col)];
}

size_t Matrix::index(size_t row, size_t col) const {
    return row * m_ncol + col;  // Or however you calculate the index based on your row/column major order.
}

size_t Matrix::nrow() const {
    return m_nrow;
}

size_t Matrix::ncol() const {
    return m_ncol;
}

size_t Matrix::size() const {
    return m_nrow * m_ncol;
}

double Matrix::buffer(size_t i) const {
    return m_buffer[i];
}

std::vector<double> Matrix::buffer_vector() const {
    return std::vector<double>(m_buffer.begin(), m_buffer.end());
}

double* Matrix::data() {
    return m_buffer.data();
}

const double* Matrix::data() const {
    return m_buffer.data();
}

// Free functions related to Matrix operations
std::ostream& operator<<(std::ostream& ostr, const Matrix& mat) {
    for (size_t i = 0; i < mat.nrow(); ++i) {
        ostr << "\n ";
        for (size_t j = 0; j < mat.ncol(); ++j) {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }
    return ostr;
}

/**
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 05-04-2024
 * 
 * @brief Implementation of the naive matrix-matrix multiplication (you said we could use the code in the course note)
 * 
 * @param mat1 
 * @param mat2 
 * @return Matrix 
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2){
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    // for (size_t i = 0; i < mat1.nrow(); ++i) {
    //     for (size_t j = 0; j < mat2.ncol(); ++j) {
    //         ret(i, j) = 0.0;  // Explicit initialization
    //     }
    // }

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;}

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
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, const int tile_size){
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





/**
 * @author FURGER Achille (furgerachi@cy-tech.fr)
 * @version 0.1
 * @date 05-04-2024
 * 
 * @brief Compares two matrices to see if they are exactly the same. We could apply the tiled logic here but comparison isn't performance-consuming enough for it to be needed.
 * 
 * @param mat1 
 * @param mat2 
 * @return true 
 * @return false 
 */
bool check_result(Matrix const & mat1, Matrix const & mat2){
    // First, we check if the matrices are of the same size
    if(mat1.nrow() != mat2.nrow() || mat1.ncol() != mat2.ncol()){
        return false;
    }

    double tolerance = 1e-9;

    for(size_t i = 0; i < mat1.nrow(); i++){
        for(size_t j = 0; j < mat1.ncol(); j++){
            if(std::abs(mat1(i,j) - mat2(i,j)) > tolerance){
                return false;
            }
        }
    }

    return true;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("the number of first matrix column "
                                "differs from that of second matrix row");
    }

    // Allocate the result matrix with appropriate dimensions
    Matrix res(mat1.nrow(), mat2.ncol());

    // Define alpha and beta for the operation C = alpha * A * B + beta * C
    double alpha = 1.0;
    double beta = 0.0;

    // Perform the multiplication using cblas_dgemm
    // Note: MKL uses column-major order storage, but the Matrix class uses row-major.
    // Parameters are adjusted accordingly to account for the difference in storage order.
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(),
                alpha, mat1.data(), mat1.ncol(),
                mat2.data(), mat2.ncol(), beta,
                res.data(), res.ncol());

    return res;
}
