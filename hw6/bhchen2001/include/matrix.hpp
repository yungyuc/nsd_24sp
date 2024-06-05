# ifndef _MATRIX_HPP
# define _MATRIX_HPP

#include<iostream>
#include<vector>
#include<stdexcept>
#include<mkl/mkl.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

class Matrix {
    public:

        Matrix(size_t nrow, size_t ncol){
            this->m_nrow = nrow;
            this->m_ncol = ncol;
            m_buffer = (double *) calloc(nrow * ncol, sizeof(double));
        }

        pybind11::array_t<double> to_numpy(){
            std::vector<size_t> shape = {nrow(), ncol()};
            std::vector<size_t> strides = {ncol() * sizeof(double), sizeof(double)};
            return pybind11::array_t<double>(
                shape,
                strides,
                m_buffer,
                pybind11::cast(m_buffer)
            );
        }

        double operator() (size_t row, size_t col) const{
            return m_buffer[index(row, col)];
        }
        double & operator() (size_t row, size_t col){
            return m_buffer[index(row, col)];
        }

        size_t nrow() const{
            return m_nrow;
        }
        size_t ncol() const{
            return m_ncol;
        }

        bool operator==(Matrix const & other) const{
            if (m_nrow != other.m_nrow || m_ncol != other.m_ncol){
                return false;
            }
            for (size_t i = 0; i < m_nrow * m_ncol; i++){
                if (m_buffer[i] != other.m_buffer[i]){
                    return false;
                }
            }
            return true;
        }

        double * buffer(){
            return m_buffer;
        }

        const double * buffer() const{
            return m_buffer;
        }

    private:

        size_t index(size_t row, size_t col) const{
            return row * m_ncol + col;
        }

        size_t m_nrow = 0;
        size_t m_ncol = 0;
        double * m_buffer = nullptr;
};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

# endif