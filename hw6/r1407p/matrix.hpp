#pragma once

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
namespace py=pybind11;

using namespace std;

class Matrix{
private:
    size_t m_nrow, m_ncol;
    double *m_buffer;
public:
    Matrix();
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, double val);
    Matrix(size_t nrow, size_t ncol,const vector<double> &v);
    Matrix(const Matrix &m);
    Matrix & operator=(const Matrix &m);
    ~Matrix();

    size_t index(size_t i, size_t j) const;
    size_t nrow() const;
    size_t ncol() const;
    double* get_buffer() const;

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    bool operator==(const Matrix &m) const;  
    bool operator!=(const Matrix &m) const;

    py::array_t<double> array() const;
};
Matrix multiply_naive(Matrix const &m1, Matrix const &m2);
Matrix multiply_tile(Matrix const &m1, Matrix const &m2, std::size_t size);
Matrix multiply_mkl(Matrix const &m1, Matrix const &m2);