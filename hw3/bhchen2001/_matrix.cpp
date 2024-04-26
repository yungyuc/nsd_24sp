#include "_matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

Matrix::Matrix(size_t nrow, size_t ncol){
    this->m_nrow = nrow;
    this->m_ncol = ncol;
    m_buffer = (double *) calloc(nrow * ncol, sizeof(double));
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec){
    this->m_nrow = nrow;
    this->m_ncol = ncol;
    m_buffer = new double[nrow * ncol];
    for (size_t i = 0; i < nrow * ncol; i++){
        m_buffer[i] = vec[i];
    }
}

Matrix::Matrix(Matrix const & other){
    this->m_nrow = other.m_nrow;
    this->m_ncol = other.m_ncol;
    m_buffer = new double[this->m_nrow * this->m_ncol];
    for (size_t i = 0; i < this->m_nrow * this->m_ncol; i++){
        m_buffer[i] = other.m_buffer[i];
    }
}

Matrix::~Matrix(){
    delete[] m_buffer;
}

double Matrix::operator() (size_t row, size_t col) const{
    return m_buffer[index(row, col)];
}

double & Matrix::operator() (size_t row, size_t col){
    return m_buffer[index(row, col)];
}

size_t Matrix::nrow() const{
    return m_nrow;
}

size_t Matrix::ncol() const{
    return m_ncol;
}

bool Matrix::operator==(Matrix const & other) const{
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

double * Matrix::buffer() const{
    return m_buffer;
}

size_t Matrix::index(size_t row, size_t col) const{
    return row * m_ncol + col;
}

Matrix multiply_naive(const Matrix &m1, const Matrix &m2){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for (size_t i = 0; i < m1.nrow(); i++){
        for (size_t j = 0; j < m2.ncol(); j++){
            for (size_t k = 0; k < m1.ncol(); k++){
                result(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    for (size_t i = 0; i < m1.nrow(); i += tile_size){
        for (size_t j = 0; j < m2.ncol(); j += tile_size){
            for (size_t k = 0; k < m1.ncol(); k += tile_size){
                size_t ii_limit = std::min(i + tile_size, m1.nrow());
                for (size_t ii = i; ii < ii_limit; ii++){
                    size_t jj_limit = std::min(j + tile_size, m2.ncol());
                    for (size_t jj = j; jj < jj_limit; jj++){
                        size_t kk_limit = std::min(k + tile_size, m1.ncol());
                        double tmp = 0;
                        for (size_t kk = k; kk < kk_limit; kk++){
                            tmp += m1(ii, kk) * m2(kk, jj);
                        }
                        result(ii, jj) += tmp;
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiply_mkl(const Matrix &m1, const Matrix &m2){
    if (m1.ncol() != m2.nrow()){
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(m1.nrow(), m2.ncol());
    cblas_dgemm(CblasRowMajor, 
                CblasNoTrans, 
                CblasNoTrans, 
                m1.nrow(), 
                m2.ncol(), 
                m1.ncol(), 
                1.0, 
                m1.buffer(), 
                m1.ncol(), 
                m2.buffer(), 
                m2.ncol(), 
                0.0, 
                result.buffer(), 
                result.ncol());
    return result;
}

PYBIND11_MODULE(_matrix, m){
    m.doc() = "Matrix multiplication module";
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<size_t, size_t, std::vector<double> const &>())
        .def(pybind11::init<Matrix const &>())
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> const & p, double val){
            m(p.first, p.second) = val;
        })
        .def("__getitem__", [](Matrix &m, std::pair<size_t, size_t> const & p){
            return m(p.first, p.second);
        })
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__eq__", &Matrix::operator==);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}