#include <mkl/mkl.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <cassert>
#include <utility>

class Matrix {
 public:
  const size_t nrow = 0;
  const size_t ncol = 0;
  std::unique_ptr<double[]> m_buffer;

 public:
  size_t size() const { return nrow * ncol; }
  double buffer(size_t i) const { return m_buffer[i]; }
  size_t index(size_t row, size_t col) const { return row * ncol + col; }
  double operator[](size_t idx) const { return m_buffer[idx]; }
  double &operator[](size_t idx) { return m_buffer[idx]; }
  double operator()(size_t row, size_t col) const {
    return m_buffer[index(row, col)];
  }
  double &operator()(size_t row, size_t col) {
    return m_buffer[index(row, col)];
  }
  bool operator==(const Matrix &mat) const {
    return (nrow == mat.nrow) && (ncol == mat.ncol) &&
           (memcmp(m_buffer.get(), mat.m_buffer.get(),
                   size() * sizeof(double)) == 0);
  }

 public:
  Matrix(size_t n_row, size_t n_col)
      : nrow(n_row), ncol(n_col), m_buffer(new double[n_row * n_col]) {}
  Matrix(const Matrix &m)
      : nrow(m.nrow), ncol(m.ncol), m_buffer(new double[m.nrow * m.ncol]) {
    memcpy(m_buffer.get(), m.m_buffer.get(), sizeof(double) * nrow * ncol);
  }

  /* naive matrix multiplication */
  Matrix multiply_naive(const Matrix &mat) const;
  /* matrix multiplication using BLAS DGEMM */
  Matrix multiply_mkl(const Matrix &mat) const;
  /* tiling matrix multiplication */
  Matrix multiply_tile(const Matrix &mat, const size_t N) const;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_naive(mat2);
}

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_mkl(mat2);
}

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize) {
  return mat1.multiply_tile(mat2, tsize);
}
