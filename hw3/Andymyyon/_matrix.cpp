#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <math.h>
#include "mkl.h"
#include <chrono>
#include <fstream>


class Matrix {

public:

    Matrix(size_t nrow, size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
    }

    Matrix & operator=(std::vector<double> const & vec)
    {
        if (size() != vec.size())
        {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    Matrix(Matrix const & other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
    }

    Matrix & operator=(Matrix const & other)
    {
        if (this == &other) { return *this; }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
        {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
        return *this;
    }

    Matrix(Matrix && other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    Matrix & operator=(Matrix && other)
    {
        if (this == &other) { return *this; }
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }

    bool operator==(const Matrix& other) const {
        // First, check if the dimensions are the same
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
            return false;
        }

        // Check each element
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                if (std::abs((*this)(i, j) - other(i, j)) > 1e-9) {  // Using a small tolerance for floating point comparison
                    return false;
                }
            }
        }

        return true;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
    }

    double* data() {
        return m_buffer;
    }

    const double* data() const {
        return m_buffer;
    }

private:



    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement) { m_buffer = new double[nelement]; }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;

};

/*
 * Naive matrix matrix multiplication.
 */
Matrix operator*(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); ++i) {
        for (int j = 0; j < mat2.ncol(); ++j) {
            ret(i, j) = 0.0;  // Explicit initialization
    }
}

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

    return ret;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i)
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j)
        {
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
    return mat1 * mat2;
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
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, const int tile_size){
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix res(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); ++i) {
        for (int j = 0; j < mat2.ncol(); ++j) {
            res(i, j) = 0.0;  // Explicit initialization
        }
    }
    // First, we 'create' and iterate over the different tiles
    for(int i_tile = 0; i_tile< mat1.nrow(); i_tile = i_tile + tile_size){
        for(int j_tile = 0; j_tile < mat2.ncol(); j_tile = j_tile + tile_size){
            for(int k_tile = 0; k_tile < mat1.ncol(); k_tile = k_tile + tile_size){
    // And now we iterate inside each tile
                for(int i = i_tile; i < std::min(i_tile + tile_size, int(mat1.nrow())); i++){
                    for(int j = j_tile; j < std::min(j_tile + tile_size, int(mat2.ncol())); j++){
                        double sum = 0;
                        for(int k = k_tile; k < std::min(k_tile + tile_size, int(mat1.ncol())); k++){
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

    for(int i = 0; i < mat1.nrow(); i++){
        for(int j = 0; j < mat1.ncol(); j++){
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


#ifndef SKIP_PYBIND11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

    PYBIND11_MODULE(_matrix, m) {
        py::class_<Matrix>(m, "Matrix")
            .def(py::init<size_t, size_t>())
            .def(py::init<const Matrix &>())
            .def(py::init<size_t, size_t, const std::vector<double>&>())
            .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx){
                return m(idx[0], idx[1]);
            })
            .def("__setitem__", [](Matrix &m, std::vector<std::size_t> idx, double val){
                m(idx[0], idx[1]) = val;
            })
            .def("buffer_vector", &Matrix::buffer_vector, "Returns the internal buffer as a vector")
            .def("__call__", [](Matrix &m, size_t i, size_t j) { return m(i, j); })
            .def("__call__", [](Matrix &m, size_t i, size_t j, double val) { m(i, j) = val; })
            .def_property_readonly("nrow", &Matrix::nrow)
            .def_property_readonly("ncol", &Matrix::ncol)
            .def("__eq__", &Matrix::operator==);

        m.def("multiply_naive", &multiply_naive, "Naive matrix multiplication");
        m.def("multiply_tile", &multiply_tile, "Tiled matrix multiplication");
        m.def("multiply_mkl", &multiply_mkl, "MKL matrix multiplication");
        m.def("check_result", &check_result, "Compares two matrices for equality within a tolerance");
    }

    // PYBIND11_MODULE(_matrix, m) {
    //     py::class_<Matrix>(m, "Matrix")
    //         // .def(py::init<>())
    //         .def(py::init<size_t, size_t>())
    //         // .def(py::init<size_t, size_t, double>())
    //         .def(py::init<const Matrix &>())
    //         .def(py::init<size_t, size_t, const std::vector<double>&>())
    //         .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx){
    //             return m(idx[0],idx[1]);
    //         })
    //         .def("__getitem__", [](Matrix &m, std::vector<std::size_t> idx, int val){
    //             return m(idx[0], idx[1]) = val;
    //         })
    //         .def_property_readonly("nrow", &Matrix::nrow)
    //         .def_property_readonly("ncol", &Matrix::ncol)
    //         .def("__eq__", &Matrix::operator ==);
    //         // .def("buffer_vector", &Matrix::buffer_vector)
    //         // .def("__call__", [](Matrix &m, size_t i, size_t j) { return m(i, j); })
    //         // .def("__call__", [](Matrix &m, size_t i, size_t j, double val) { m(i, j) = val; });

    //     m.def("multiply_naive", &multiply_naive, "Naive matrix multiplication");
    //     m.def("multiply_tile", &multiply_tile, "Tiled matrix multiplication");
    //     m.def("multiply_mkl", &multiply_mkl, "MKL matrix multiplication");
    //     m.def("check_result", &check_result, "Compares two matrices for equality within a tolerance");
    // }
#endif


int main(int argc, char ** argv)
{
    srand(static_cast<unsigned>(time(nullptr)));

    const size_t col1 = 1024;
    const size_t row2 = 1024;
    const size_t row1 = 1024;
    const size_t col2 = 1024;
    std::vector<double> randValues1, randValues2;

    // Generate random values for two matrices
    for (size_t i = 0; i < row1 * col1; ++i) {
        randValues1.push_back(static_cast<double>(rand() % 100 + 1));
    }
    for (size_t i = 0; i < row2 * col2; ++i) {
        randValues2.push_back(static_cast<double>(rand() % 100 + 1));
    }

    Matrix mat1(row1, col1, randValues1);
    Matrix mat2(row2, col2, randValues2);
    
    // Naive multiplication
    auto startNaive = std::chrono::high_resolution_clock::now();
    Matrix naiveMatrix = multiply_naive(mat1,mat2);
    auto stopNaive = std::chrono::high_resolution_clock::now();
    long durationNaive = std::chrono::duration_cast<std::chrono::microseconds>(stopNaive - startNaive).count();
    std::cout << "Naive multiplication execution time: " << durationNaive << " microseconds" << std::endl;
    
    // Tiled multiplication
    auto startTiled = std::chrono::high_resolution_clock::now();
    Matrix tiledMatrix = multiply_tile(mat1,mat2,32);
    auto stopTiled = std::chrono::high_resolution_clock::now();
    long durationTiled = std::chrono::duration_cast<std::chrono::microseconds>(stopTiled - startTiled).count();
    std::cout << "Tiled multiplication execution time: " << durationTiled << " microseconds" << std::endl;

    // MKL multiplication
    auto startMkl = std::chrono::high_resolution_clock::now();
    Matrix mklMatrix = multiply_mkl(mat2,mat1); // Due to how I created my functions, I have to multiply mat2 by mat1 and not mat1 by mat2 here
    auto stopMkl = std::chrono::high_resolution_clock::now();
    long durationMkl = std::chrono::duration_cast<std::chrono::microseconds>(stopMkl - startMkl).count();
    std::cout << "Mkl multiplication execution time: " << durationMkl << " microseconds" << std::endl;

    // Checking if the results are all the same
    if(check_result(naiveMatrix,tiledMatrix) && check_result(naiveMatrix,mklMatrix)){
        std::cout << "The matrices are equal" << std::endl;
    } else {
        std::cout << "The matrices are NOT equal" << std::endl;
    }

    std::ofstream outFile("performance.txt", std::ios::out);
    if (outFile.is_open()){
        // Comparing how fast each multiplication is
        if (durationMkl != 0 && durationNaive != 0 && durationTiled != 0){ // avoid division by 0
            double naiveOverTiled = static_cast<double>(durationNaive) / durationTiled;
            std::cout << "Tiled multiplication is " << (naiveOverTiled - 1) * 100 << "\% faster than the naive implication" << std::endl;
            double tiledOverMkl = static_cast<double>(durationTiled) / durationMkl;
            std::cout << "MKL multiplication is " << (durationMkl - 1) * 100 << "\% faster than the tiled implication" << std::endl;

            outFile << "The performance may differ due to the randomness of the matrix, but it differs lightly (~140\% for the tiled implementation for two 1024*1024 matrix with a tiling size of 32)\n";
            outFile << "Changing the tiling size to 64 doesn't change much\n";
            outFile << "A 100\% faster result means the function is 2 times faster\n";
            outFile << "Tiled multiplication is " << (naiveOverTiled - 1) * 100 << "\% faster than the naive implication\n";
            outFile << "MKL multiplication is " << (durationMkl - 1) * 100 << "\% faster than the tiled implication\n";

        }
    }

    return 0;
}





// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4: