#include "matrix.hpp"

void populate(Matrix& matrix) {
    for (size_t i = 0; i < matrix.nrow(); ++i) {
        for (size_t j = 0; j < matrix.ncol(); ++j) {
            matrix(i, j) = i * 10 + j;
        }
    }
}

void printMatrix(const Matrix& matrix) {
    for (size_t i = 0; i < matrix.nrow(); ++i) {
        std::cout << std::endl << " ";
        for (size_t j = 0; j < matrix.ncol(); ++j) {
            std::cout << " " << std::setfill('0') << std::setw(2) << matrix(i, j);
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    size_t size = 1000;

    std::cout << "Creating Matrix A...\n";
    Matrix A(size, size);
    populate(A);

    std::cout << "Creating Matrix B...\n";
    Matrix B = A; // This will use the copy constructor

    std::cout << "Performing naive multiplication...\n";
    auto start = std::chrono::high_resolution_clock::now();
    Matrix result1 = multiply_naive(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_naive = end - start;
    std::cout << "Naive multiplication took " << elapsed_naive.count() << " ms.\n";

    std::cout << "Performing tiled multiplication with tile size 16...\n";
    start = std::chrono::high_resolution_clock::now();
    Matrix result2 = multiply_tile(A, B, 16);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_tile16 = end - start;
    std::cout << "Tiled multiplication with tile size 16 took " << elapsed_tile16.count() << " ms.\n";

    std::cout << "Performing MKL multiplication...\n";
    start = std::chrono::high_resolution_clock::now();
    Matrix result3 = multiply_mkl(A, B);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_mkl = end - start;
    std::cout << "MKL multiplication took " << elapsed_mkl.count() << " ms.\n";

    return 0;
}
