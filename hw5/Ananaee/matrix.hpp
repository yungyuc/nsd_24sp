#pragma once
#include <vector>
#include <iostream>
#include <cstdint>
#include <mkl/mkl.h>

class Matrix {

    public:
        // Matrix();
        Matrix(size_t nrow, size_t ncol);
        Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);


        // TODO: copy and move constructors and assignment operators.
        Matrix(Matrix const & );
        Matrix(Matrix       &&);
        Matrix & operator=(Matrix const & ); // copy assignment operator.
        Matrix & operator=(Matrix       &&);

        ~Matrix();

        double operator() (size_t row, size_t col) const;
        double& operator() (size_t row, size_t col);
        bool operator== (const Matrix& other) const;

        size_t nrow() const;
        size_t ncol() const;


        double* buffer() const;


    private:
        size_t m_nrow = 0;
        size_t m_ncol = 0;
        double * m_buffer = nullptr;

};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);