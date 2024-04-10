#include "matrix.hpp"
#include "mkl.h"

Matrix multiply_naive(const Matrix& A, const Matrix& B);

void populate(Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = i * 10 + j;
        }
    }
}

void multiply_mkl(const Matrix& A, const Matrix& B, Matrix& C) {
    if (A.cols() != B.rows() || A.rows() != C.rows() || B.cols() != C.cols()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    const double alpha = 1.0;
    const double beta = 0.0;
    const MKL_INT m = A.rows();
    const MKL_INT n = B.cols();
    const MKL_INT k = A.cols();

    // DGEMM performs C = alpha*A*B + beta*C
    // Note: MKL uses column-major storage, ensure your Matrix class is compatible or adjust accordingly
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A.data(), k, B.data(), n, beta, C.data(), n);
}

void printMatrix(const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        std::cout << std::endl << " ";
        for (size_t j = 0; j < matrix.cols(); ++j) {
            std::cout << " " << std::setfill('0') << std::setw(2) << matrix(i, j);      
        }
        std::cout << std::endl;
    }
}

Matrix multiply_naive(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    size_t m = A.rows();
    size_t n = A.cols(); 
    size_t p = B.cols();

    Matrix C(m, p);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k) {
                sum += A(i, k) * B(k, j);
            }
            C(i, j) = sum;
        }
    }

    return C;
}


Matrix multiply_tile(const Matrix& A, const Matrix& B) {
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }
    
    size_t m = A.rows();
    size_t n = A.cols();
    size_t p = B.cols();
    Matrix C(m, p);
    
    
    for (size_t i = 0; i < m; i += TILE_SIZE) {
        for (size_t k = 0; k < n; k += TILE_SIZE) {
            for (size_t j = 0; j < p; j += TILE_SIZE) {
                for (size_t ii = i; ii < std::min(i + TILE_SIZE, m); ++ii) {
                    for (size_t kk = k; kk < std::min(k + TILE_SIZE, n); ++kk) {
                        double r = A(ii, kk);
                        for (size_t jj = j; jj < std::min(j + TILE_SIZE, p); ++jj) {
                            C(ii, jj) += r * B(kk, jj);
                        }
                    }
                }
            }
        }
    }
    
    return C;
}

int main(int argc, char const *argv[])
{
    size_t size = 10000;

    Matrix A(size, size);
    
    populate(A);

    Matrix B = A;

    auto start = std::chrono::high_resolution_clock::now();
    Matrix result1 = multiply_naive(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_naive = end - start;
    std::cout << "Naive multiplication took " << elapsed_naive.count() << " ms.\n";

    start = std::chrono::high_resolution_clock::now();
    Matrix result2 = multiply_tile(A, B);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_tile = end - start;
    std::cout << "Tiled multiplication took " << elapsed_tile.count() << " ms.\n";

    Matrix result3(size, size);
    start = std::chrono::high_resolution_clock::now();
    multiply_mkl(A, B, result3);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_mkl = end - start;
    std::cout << "MKL multiplication took " << elapsed_mkl.count() << " ms.\n";

    double percent_reduction_tile_from_naive = (1 - elapsed_tile.count() / elapsed_naive.count()) * 100;
    double percent_reduction_mkl_from_naive = (1 - elapsed_mkl.count() / elapsed_naive.count()) * 100;
    double percent_reduction_mkl_from_tile = (1 - elapsed_mkl.count() / elapsed_tile.count()) * 100;

    std::cout << "\nPercentage speed increase of Tiling over Naive: " << percent_reduction_tile_from_naive << "%\n";
    std::cout << "Percentage speed increase of MKL over Naive: " << percent_reduction_mkl_from_naive << "%\n";
    std::cout << "Percentage speed increase of MKL over Tiling: " << percent_reduction_mkl_from_tile << "%\n";

    return 0;
}