#include "matrix.hpp"

Matrix Matrix::multiply_naive(const Matrix &mat) const {
  assert(ncol == mat.nrow);
  Matrix ret(nrow, mat.ncol);
  for (size_t i = 0; i < nrow; i++) {
    for (size_t j = 0; j < mat.ncol; j++) {
      double v = 0;
      for (size_t k = 0; k < ncol; k++) v += (*this)(i, k) * mat(k, j);
      ret(i, j) = v;
    }
  }
  return ret;
}

Matrix Matrix::multiply_mkl(const Matrix &mat) const {
  Matrix ret(nrow, mat.ncol);
  cblas_dgemm(  // https://developer.apple.com/documentation/accelerate/1513282-cblas_dgemm
      CblasRowMajor, CblasNoTrans, CblasNoTrans,           // row-major
      nrow, mat.ncol, ncol,                                // m, n, k,
      1.0,                                                 // no scaling
      m_buffer.get(), ncol, mat.m_buffer.get(), mat.ncol,  // operand
      0.0,                          // ignore content in ret
      ret.m_buffer.get(), ret.ncol  // result
  );
  return ret;
}

Matrix Matrix::multiply_tile(const Matrix &mat, const size_t N) const {
  if (N <= 1) return multiply_mkl(mat);
  /* initialize */
  std::vector<std::vector<std::unique_ptr<double[]>>> m_mat1, m_mat2, m_ret;
  for (int i = 0; i * N < nrow; i++) {  // tile this (row-major)
    m_mat1.emplace_back();
    for (int j = 0; j * N < ncol; j++) {
      m_mat1.back().emplace_back(new double[N * N]);
      auto m = m_mat1.back().back().get();
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          m[mi * N + mj] = (r < nrow && c < ncol) ? (*this)(r, c) : 0;
        }
      }
    }
  }
  for (int i = 0; i * N < mat.nrow; i++) {  // tile mat2 (col-major)
    m_mat2.emplace_back();
    for (int j = 0; j * N < mat.ncol; j++) {
      m_mat2.back().emplace_back(new double[N * N]);
      auto m = m_mat2.back().back().get();
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          m[mj * N + mi] = (r < mat.nrow && c < mat.ncol) ? mat(r, c) : 0;
        }
      }
    }
  }
  for (int i = 0; i * N < nrow; i++) {  // tile ret (storing result)
    m_ret.emplace_back();
    for (int j = 0; j * N < mat.ncol; j++) {
      m_ret.back().emplace_back(new double[N * N]);
      auto m = m_ret.back().back().get();
      for (size_t e = 0; e < N * N; e++) m[e] = 0;
    }
  }
  /* multiply */
  for (int i = 0; i * N < nrow; i++) {
    for (int j = 0; j * N < mat.ncol; j++) {
      auto m = m_ret[i][j].get();
      for (int k = 0; k * N < ncol; k++) {
        auto t_mat1 = m_mat1[i][k].get(), t_mat2 = m_mat2[k][j].get();
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
  Matrix ret(nrow, mat.ncol);
  for (int i = 0; i * N < nrow; i++) {
    for (int j = 0; j * N < mat.ncol; j++) {
      auto m = m_ret[i][j].get();
      for (size_t mi = 0; mi < N; mi++) {
        size_t r = (i * N) + mi;
        for (size_t mj = 0; mj < N; mj++) {
          size_t c = (j * N) + mj;
          if (r < ret.nrow && c < ret.ncol) ret(r, c) = m[mi * N + mj];
        }
      }
    }
  }
  return ret;
}

typedef std::pair<int, int> int2;
namespace py = pybind11;
PYBIND11_MODULE(_matrix, m) {
  // https://pybind11.readthedocs.io/en/stable/classes.html
  // https://pybind11.readthedocs.io/en/stable/advanced/classes.html#operator-overloading
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<size_t, size_t>())
      .def_readonly("nrow", &Matrix::nrow)
      .def_readonly("ncol", &Matrix::ncol)
      .def("__getitem__",
           [](Matrix &self, int2 p) { return self(p.first, p.second); })
      .def("__setitem__",
           [](Matrix &self, int2 p, double v) { self(p.first, p.second) = v; })
      .def(py::self == py::self);

  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_mkl", &multiply_mkl);
  m.def("multiply_tile", &multiply_tile);
}
