#include "matrix.hpp"





int main(int, char **)
{


    // Create two matrices
    std::vector<double> elmement{1,2,3,4,5,6};
    Matrix m1(2, 3, elmement);
    Matrix m2(3, 2, elmement);



    // Perform matrix multiplication
    Matrix result1 = multiply_naive(m1, m2);
    // Matrix result2 = multiply_mkl(m1, m2);
    Matrix result2 = multiply_tile(m1, m2, 128);

    // Display the result
    int verif = 0;
    std::cout << "Result of matrix multiplication:" << std::endl;
    for (size_t i = 0; i < result1.nrow(); ++i) {
        for (size_t j = 0; j < result1.ncol(); ++j) {
            if (result1(i,j) != result2(i,j)){
                std::cout << "Eroor pas les memes" << std::endl;
                verif=1;
            }
        }

    }
    if (verif == 0){
        std::cout << "Good job  :  " << result1.buffer()<< std::endl;
    }

    return 0;
}