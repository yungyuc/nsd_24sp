#include "matrix.hpp"
#include <iomanip>

Matrix multiply_naive(const Matrix& A, const Matrix& B);

void populate(Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = i * 10 + j;
        }
    }
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
    size_t n = A.cols(); // or B.rows();
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
    size_t n = A.cols(); // ou B.rows();
    size_t p = B.cols();
    Matrix C(m, p);
    
    
    for (size_t i = 0; i < m; i += TILE_SIZE) {
        for (size_t j = 0; j < p; j += TILE_SIZE) {
            for (size_t k = 0; k < n; k += TILE_SIZE) {
                // Pour chaque tuile, effectuer la multiplication de matrices sur les éléments de la tuile
                for (size_t ii = i; ii < std::min(i + TILE_SIZE, m); ++ii) {
                    for (size_t jj = j; jj < std::min(j + TILE_SIZE, p); ++jj) {
                        for (size_t kk = k; kk < std::min(k + TILE_SIZE, n); ++kk) {
                            C(ii, jj) += A(ii, kk) * B(kk, jj);
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
    size_t size = 1000;

    Matrix A(size, size);
    
    populate(A);

    Matrix B = A;


    std::cout << "Matrix A:" << std::endl;
    printMatrix(A);

    std::cout << std::endl << "Matrix B:" << std::endl;
    printMatrix(B);

    Matrix result = multiply_naive(A, B);

    std::cout << std::endl << "Result of A * B:" << std::endl;
    printMatrix(result);

    return 0;
}