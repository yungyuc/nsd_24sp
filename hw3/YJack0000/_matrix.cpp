#include "_matrix.hpp"
#include <cstring>

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) {
  size_t nelements = nrow * ncol;
  m_buffer = new double[nelements];
  memset(m_buffer, nelements, sizeof(double));
}

Matrix::Matrix(const Matrix &mat) : m_nrow(mat.m_nrow), m_ncol(mat.m_ncol) {
  size_t nelements = m_nrow * m_ncol;
  m_buffer = new double[nelements];
  memcpy(m_buffer, mat.m_buffer, nelements * sizeof(double));
}

Matrix::~Matrix() { delete[] m_buffer; }

double Matrix::operator()(size_t row, size_t col) const {
  return m_buffer[index(row, col)];
}

double &Matrix::operator()(size_t row, size_t col) {
  return m_buffer[index(row, col)];
}

bool Matrix::operator==(const Matrix &other) const {
  if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    return false;
  for (size_t i = 0; i < m_nrow; i++)
    for (size_t j = 0; j < m_ncol; j++)
      if ((*this)(i, j) != other(i, j))
        return false;
  return true;
}

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
  if (mat1.ncol() != mat2.nrow()) {
    throw std::out_of_range("the number of first matrix column "
                            "differs from that of second matrix row");
  }

  Matrix result(mat1.nrow(), mat2.ncol());
  for (size_t i = 0; i < mat1.nrow(); i++) {
    for (size_t j = 0; j < mat2.ncol(); j++) {
      for (size_t k = 0; k < mat1.ncol(); k++) {
        result(i, j) += mat1(i, k) * mat2(k, j);
      }
    }
  }

  return result;
}

Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t tsize) {

  if (mat1.ncol() != mat2.nrow()) {
    throw std::out_of_range("the number of first matrix column "
                            "differs from that of second matrix row");
  }

  Matrix result(mat1.nrow(), mat2.ncol());
  size_t max_i = mat1.nrow();
  size_t max_j = mat2.ncol();
  size_t max_k = mat1.ncol();

  for (size_t i = 0; i < max_i; i += tsize) {
    for (size_t j = 0; j < max_j; j += tsize) {
      for (size_t k = 0; k < max_k; k += tsize) {
        size_t upper_i = std::min(i + tsize, max_i);
        size_t upper_j = std::min(j + tsize, max_j);
        size_t upper_k = std::min(k + tsize, max_k);
        for (size_t t_i = i; t_i < upper_i; ++t_i) {
          for (size_t t_j = j; t_j < upper_j; ++t_j) {
            double sum = .0;
            for (size_t t_k = k; t_k < upper_k; ++t_k) {
              sum += mat1(t_i, t_k) * mat2(t_k, t_j);
            }
            result(t_i, t_j) += sum;
          }
        }
      }
    }
  }

  return result;
}

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
  if (mat1.ncol() != mat2.nrow()) {
    throw std::out_of_range("the number of first matrix column "
                            "differs from that of second matrix row");
  }
  Matrix result(mat1.nrow(), mat2.ncol());
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.nrow(),
              mat2.ncol(), mat1.ncol(), 1.0, mat1.data(), mat1.ncol(),
              mat2.data(), mat2.ncol(), 0.0, result.data(), result.ncol());
  return result;
}

namespace py = pybind11;
PYBIND11_MODULE(_matrix, m) {
  m.doc() = "matrix-matrix multiplication";

  m.def("multiply_naive", &multiply_naive, "multiply_naive");
  m.def("multiply_tile", &multiply_tile, "multiply_tile");
  m.def("multiply_mkl", &multiply_mkl, "multiply_mkl");
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<size_t, size_t>())
      .def_property_readonly("nrow", &Matrix::nrow)
      .def_property_readonly("ncol", &Matrix::ncol)
      .def("__eq__", [](const Matrix &a, const Matrix &b) { return a == b; })
      .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> idx,
                             double val) { self(idx.first, idx.second) = val; })
      .def("__getitem__",
           [](const Matrix &self, std::pair<size_t, size_t> idx) {
             return self(idx.first, idx.second);
           });
}
