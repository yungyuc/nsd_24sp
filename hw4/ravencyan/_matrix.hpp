#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
#include <vector>
using namespace std;

template<typename T> class CustomAllocator {
public:
    using value_type = T;
    CustomAllocator() = default;
    T *allocate(size_t n);
    void deallocate(T *ptr, size_t n);
    static size_t bytes();
    static size_t allocated();
    static size_t deallocated();
private:
    static size_t m_byte;
    static size_t m_allocated;
    static size_t m_deallocated;
};
template <class T> std::size_t CustomAllocator<T>::m_byte = 0;
template <class T> std::size_t CustomAllocator<T>::m_allocated = 0;
template <class T> std::size_t CustomAllocator<T>::m_deallocated = 0;


class Matrix {
public:
    Matrix();
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, const vector<double> &v);
    //Matrix(const Matrix& other);
    //~Matrix() { delete [] m_buffer; };

    double operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool operator==(const Matrix& other) const;
    size_t nrow() const { return m_nrow; };
    size_t ncol() const { return m_ncol; };
    double* get_buffer() const;

private:
    size_t m_nrow;
    size_t m_ncol;
    //double * m_buffer;
    vector<double, CustomAllocator<double>> m_buffer;
};

#endif