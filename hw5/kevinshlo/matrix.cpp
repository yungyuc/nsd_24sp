#include "matrix.hpp"

#include <cassert>

Matrix Matrix::multiply_naive(const Matrix &mat) const {
  assert(m_ncol == mat.m_nrow);
  Matrix ret(m_nrow, mat.m_ncol);
  for (size_t i = 0; i < m_nrow; i++) {
    for (size_t j = 0; j < mat.m_ncol; j++) {
      double v = 0;
      for (size_t k = 0; k < m_ncol; k++) v += (*this)(i, k) * mat(k, j);
      ret(i, j) = v;
    }
  }
  return ret;
}

Matrix Matrix::multiply_mkl(const Matrix &mat) const {
  Matrix ret(m_nrow, mat.m_ncol);
  cblas_dgemm(  // https://developer.apple.com/documentation/accelerate/1513282-cblas_dgemm
      CblasRowMajor, CblasNoTrans, CblasNoTrans,                 // row-major
      m_nrow, mat.m_ncol, m_ncol,                                // m, n, k,
      1.0,                                                       // no scaling
      m_buffer.data(), m_ncol, mat.m_buffer.data(), mat.m_ncol,  // operand
      0.0,                             // ignore content in ret
      ret.m_buffer.data(), ret.m_ncol  // result
  );
  return ret;
}

Matrix Matrix::multiply_tile(const Matrix &mat, const size_t N) const {
  if (N <= 1) return multiply_mkl(mat);
  /* initialize */
  std::vector<std::vector<std::vector<double>>> m_mat1, m_mat2, m_ret;
  for (int i = 0; i * N < m_nrow; i++) {  // tile this (row-major)
    m_mat1.emplace_back();
    for (int j = 0; j * N < m_ncol; j++) {
      m_mat1.back().emplace_back(N * N);
      auto &m = m_mat1.back().back();
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          m[mi * N + mj] = (r < m_nrow && c < m_ncol) ? (*this)(r, c) : 0;
        }
      }
    }
  }
  for (int i = 0; i * N < mat.m_nrow; i++) {  // tile mat2 (col-major)
    m_mat2.emplace_back();
    for (int j = 0; j * N < mat.m_ncol; j++) {
      m_mat2.back().emplace_back(N * N);
      auto &m = m_mat2.back().back();
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          m[mj * N + mi] = (r < mat.m_nrow && c < mat.m_ncol) ? mat(r, c) : 0;
        }
      }
    }
  }
  for (int i = 0; i * N < m_nrow; i++) {  // tile ret (storing result)
    m_ret.emplace_back();
    for (int j = 0; j * N < mat.m_ncol; j++) {
      m_ret.back().emplace_back(N * N);
      auto &m = m_ret.back().back();
      for (size_t e = 0; e < N * N; e++) m[e] = 0;
    }
  }
  /* multiply */
  for (int i = 0; i * N < m_nrow; i++) {
    for (int j = 0; j * N < mat.m_ncol; j++) {
      auto &m = m_ret[i][j];
      for (int k = 0; k * N < m_ncol; k++) {
        auto &t_mat1 = m_mat1[i][k], &t_mat2 = m_mat2[k][j];
        for (size_t mi = 0; mi < N; mi++) {
          for (size_t mj = 0; mj < N; mj++) {
            double v = 0;
            for (size_t mk = 0; mk < N; mk++)
              v += t_mat1[mi * N + mk] * t_mat2[mj * N + mk];
            m[mi * N + mj] += v;
          }
        }
      }
    }
  }
  /* copy to Matrix */
  Matrix ret(m_nrow, mat.m_ncol);
  for (int i = 0; i * N < m_nrow; i++) {
    for (int j = 0; j * N < mat.m_ncol; j++) {
      auto &m = m_ret[i][j];
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          if (r < ret.m_nrow && c < ret.m_ncol) ret(r, c) = m[mi * N + mj];
        }
      }
    }
  }
  return ret;
}

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_naive(mat2);
}

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_mkl(mat2);
}

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tsize) {
  return mat1.multiply_tile(mat2, tsize);
}
