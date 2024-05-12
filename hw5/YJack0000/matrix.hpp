#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <mkl.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdexcept>
#include <utility>
#include <vector>

class Matrix {

public:
  Matrix(size_t nrow, size_t ncol);
  Matrix(const Matrix &mat);
  Matrix(size_t nrow, size_t ncol, std::vector<double> const &vec);
  ~Matrix();
  double operator()(size_t row, size_t col) const;
  double &operator()(size_t row, size_t col);
  bool operator==(Matrix const &other) const;

  size_t nrow() const { return m_nrow; }
  size_t ncol() const { return m_ncol; }
  double *data() const { return m_buffer; }

private:
  size_t index(size_t row, size_t col) const { return m_ncol * row + col; }
  size_t m_nrow = 0;
  size_t m_ncol = 0;
  double *m_buffer = nullptr;
};

Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t tsize);
Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2);
Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2);

#endif