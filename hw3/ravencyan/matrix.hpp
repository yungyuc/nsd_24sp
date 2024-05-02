#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
#include <vector>

class Matrix {
public:
    Matrix();
    Matrix(std::size_t nrow, std::size_t ncol);
    Matrix(const Matrix& other);
    ~Matrix() { delete [] m_buffer; };

    double operator() (std::size_t row, std::size_t col) const { return m_buffer[row*m_ncol + col]; };
    double & operator() (std::size_t row, std::size_t col) { return m_buffer[row*m_ncol + col]; };
    bool operator==(const Matrix& other) const;
    std::size_t nrow() const { return m_nrow; };
    std::size_t ncol() const { return m_ncol; };
    double* get_buffer() const { return m_buffer; };

private:
    std::size_t m_nrow;
    std::size_t m_ncol;
    double * m_buffer;
};

#endif