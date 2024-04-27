#include <mkl/mkl.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <atomic>
#include <cassert>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

/* static class to store counters of allocated/deallocated bytes for type T */
template <class T>
class Counter {
 private:
  static std::atomic_size_t m_allocated;
  static std::atomic_size_t m_deallocated;

 public:
  static void increase(size_t n) { m_allocated += n; }
  static void decrease(size_t n) { m_deallocated += n; }
  static size_t allocated() { return m_allocated; }
  static size_t deallocated() { return m_deallocated; }
  static size_t bytes() { return m_allocated - m_deallocated; }
};
template <class T>
std::atomic_size_t Counter<T>::m_allocated{0};
template <class T>
std::atomic_size_t Counter<T>::m_deallocated{0};

/** Custom allocator tracking allocated & deallocated bytes for all Matrix
 * Need no member variables since Counter is used for global counts
 */
template <class T>
struct CustomAllocator {
  using value_type = T;
  CustomAllocator() noexcept = default;
  template <class U>
  CustomAllocator(const CustomAllocator<U> &) noexcept {};
  T *allocate(std::size_t n) {
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
      throw std::bad_alloc();
    const std::size_t bytes = n * sizeof(T);
    T *p = static_cast<T *>(std::malloc(bytes));
    if (p == nullptr) throw std::bad_alloc();
    Counter<T>::increase(bytes);
    return p;
  }
  void deallocate(T *p, std::size_t n) noexcept {
    std::free(p);
    Counter<T>::decrease(n * sizeof(T));
  }
};

/* helpers to determine template classes are equal */
template <typename T, typename U>
struct is_same : std::false_type {};
template <typename T>
struct is_same<T, T> : std::true_type {};
template <typename T, typename U>
constexpr bool eqTypes() {
  return is_same<T, U>::value;
}

/* traits for CustomAllocator */
template <class T, class U>
constexpr bool operator==(const CustomAllocator<T> &,
                          const CustomAllocator<U> &) noexcept {
  return eqTypes<T, U>();
}

template <class T, class U>
constexpr bool operator!=(const CustomAllocator<T> &,
                          const CustomAllocator<U> &) noexcept {
  return !eqTypes<T, U>();
}

class Matrix {
 public:
  const size_t nrow = 0;
  const size_t ncol = 0;
  std::vector<double, CustomAllocator<double>> m_buffer;

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
           (m_buffer == mat.m_buffer);
  }

 public:
  Matrix(size_t n_row, size_t n_col)
      : nrow(n_row), ncol(n_col), m_buffer(n_row * n_col) {}

  /**
   * naive matrix multiplication
   */
  Matrix multiply_naive(const Matrix &mat) const {
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

  /**
   * matrix multiplication using BLAS DGEMM
   */
  Matrix multiply_mkl(const Matrix &mat) const {
    Matrix ret(nrow, mat.ncol);
    cblas_dgemm(  // https://developer.apple.com/documentation/accelerate/1513282-cblas_dgemm
        CblasRowMajor, CblasNoTrans, CblasNoTrans,             // row-major
        nrow, mat.ncol, ncol,                                  // m, n, k,
        1.0,                                                   // no scaling
        m_buffer.data(), ncol, mat.m_buffer.data(), mat.ncol,  // operand
        0.0,                           // ignore content in ret
        ret.m_buffer.data(), ret.ncol  // result
    );
    return ret;
  }
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_naive(mat2);
}

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
  return mat1.multiply_mkl(mat2);
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

  m.def("allocated", &Counter<double>::allocated);
  m.def("deallocated", &Counter<double>::deallocated);
  m.def("bytes", &Counter<double>::bytes);
}
