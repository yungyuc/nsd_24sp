#include "matrix.hpp"

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

int main(int argc, char const *argv[])
{
    size_t size = 1024;

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
    result3 = multiply_mkl(A, B);
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