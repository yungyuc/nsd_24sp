// matrix.hpp

#pragma once

#include <vector>
#include <stdexcept>

class Matrix {
public:
    // default constructor
    Matrix();

    // constructor with size
    Matrix(std::size_t row, std::size_t col);

    // copy constructor
    Matrix(Matrix const & other);

    // copy assignment (release old buffer and copy new buffer)
    Matrix & operator=(Matrix const & other);

    // deconstructor
    ~Matrix();

    // element access
    double   operator() (std::size_t row, std::size_t col) const noexcept;
    double & operator() (std::size_t row, std::size_t col)       noexcept;

    // equality
    bool operator==(Matrix const & other) const;

    // shape of row
    std::size_t row() const;
    // shape of col
    std::size_t col() const;
    // size
    std::size_t size() const;
    // data
    double * buffer() const;
    
private:
    // shape of row
    std::size_t row_ = 0;
    // shape of col
    std::size_t col_ = 0;
    // data
    double * buffer_ = nullptr;
};

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2);
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, std::size_t tsize);
Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2);

