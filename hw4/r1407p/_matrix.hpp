#pragma once

#include <vector>
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

class Matrix{
private:
    size_t m_nrow, m_ncol;
    // double *m_buffer;
    vector<double, CustomAllocator<double>> m_buffer;
public:
    Matrix();
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, double val);
    Matrix(size_t nrow, size_t ncol,const vector<double> &v);
    // Matrix(const Matrix &m);
    // ~Matrix();

    size_t index(size_t i, size_t j) const;
    size_t nrow() const;
    size_t ncol() const;
    double* get_buffer() const;

    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);

    bool operator==(const Matrix &m);  
    bool operator!=(const Matrix &m);

};
