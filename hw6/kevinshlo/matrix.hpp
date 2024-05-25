#pragma once

#ifdef MKL
#include <mkl/mkl.h>
#else
#include <cblas.h>
#endif

#include <vector>

class Matrix {
 public:
  const size_t m_nrow;
  const size_t m_ncol;
  std::vector<double> m_buffer;

 public:
  size_t nrow() const { return m_nrow; }
  size_t ncol() const { return m_ncol; }
  size_t size() const { return m_nrow * m_ncol; }
  double buffer(size_t i) const { return m_buffer[i]; }
  size_t index(size_t row, size_t col) const { return row * m_ncol + col; }
  double operator[](size_t idx) const { return m_buffer[idx]; }
  double &operator[](size_t idx) { return m_buffer[idx]; }
  double operator()(size_t row, size_t col) const {
    return m_buffer[index(row, col)];
  }
  double &operator()(size_t row, size_t col) {
    return m_buffer[index(row, col)];
  }
  bool operator==(const Matrix &mat) const {
    return (m_nrow == mat.m_nrow) && (m_ncol == mat.m_ncol) &&
           (m_buffer == mat.m_buffer);
  }

 public:
  Matrix(size_t n_row, size_t n_col)
      : m_nrow(n_row), m_ncol(n_col), m_buffer(n_row * n_col) {}

  /* naive matrix multiplication */
  Matrix multiply_naive(const Matrix &mat) const;
  /* matrix multiplication using BLAS DGEMM */
  Matrix multiply_mkl(const Matrix &mat) const;
  /* tiling matrix multiplication */
  Matrix multiply_tile(const Matrix &mat, const size_t N) const;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2);

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize);