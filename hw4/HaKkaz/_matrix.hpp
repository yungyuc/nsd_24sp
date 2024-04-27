# ifndef _MATRIX_HPP
# define _MATRIX_HPP

#include<vector>
#include<stdexcept>
#include<mkl/mkl.h>
using namespace std;

template<typename T> class CustomAllocator
{
private:
  static size_t m_byte;        
  static size_t m_allocated;
  static size_t m_deallocated; 

public:
  using value_type = T;
  CustomAllocator() = default;
  
  T *allocate(size_t n);
  void deallocate(T *ptr, size_t n);
  static size_t bytes();
  static size_t allocated();
  static size_t deallocated();
};
template <class T> std::size_t CustomAllocator<T>::m_byte = 0;
template <class T> std::size_t CustomAllocator<T>::m_allocated = 0;
template <class T> std::size_t CustomAllocator<T>::m_deallocated = 0;

class Matrix {
    public:

        Matrix();
        Matrix(size_t nrow, size_t ncol);
        Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);
        // Matrix & operator=(std::vector<double> const & vec);
        // Matrix(Matrix const & other);
        // Matrix & operator=(Matrix const & other);
        // Matrix(Matrix && other);
        // Matrix & operator=(Matrix && other);

        // ~Matrix();

        double   operator() (size_t row, size_t col) const;
        double & operator() (size_t row, size_t col);

        size_t nrow() const;
        size_t ncol() const;

        bool operator==(Matrix const & other) const;

        // size_t size() const { return m_nrow * m_ncol; }
        double * buffer() const;
        // std::vector<double> buffer_vector() const;

    private:

        size_t index(size_t row, size_t col) const;
        // void reset_buffer(size_t nrow, size_t ncol);

        size_t n_row = 0;
        size_t n_col = 0;
        vector<double, CustomAllocator<double>> buf;
};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

# endif