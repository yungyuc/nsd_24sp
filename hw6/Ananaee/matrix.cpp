#include "matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// #include <pybind11/pybind11.h>
#include <pybind11/numpy.h>




// const size_t tile_size = 128;
// Matrix::Matrix() : m_nrow(0), m_ncol(0), m_buffer(nullptr) {}

Matrix::Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol)
{
    size_t nelement = nrow * ncol;
    m_buffer = new double[nelement];
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec)
    : m_nrow(nrow), m_ncol(ncol)
{
    size_t nelement = nrow * ncol;
    m_buffer = new double[nelement];
    for (size_t i = 0; i < nelement; i++) {
        m_buffer[i] = vec[i];
    }
}


// Copy constructor
Matrix::Matrix(Matrix const & other)
{
    if (other.m_buffer)
    {
        if (m_buffer) { delete[] m_buffer; } // free unused buffer.
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer = new double[m_nrow * m_ncol];
        std::copy(other.m_buffer, other.m_buffer + m_nrow * m_ncol, m_buffer);
    }

}

// Move constructor
Matrix::Matrix(Matrix && other)
{
    std::swap(other.m_ncol, m_ncol);
    std::swap(other.m_nrow, m_nrow);
    std::swap(other.m_buffer, m_buffer);
}

// Copy assignment operator
Matrix& Matrix::operator=(const Matrix& other) {

    if (this == &other) { return *this; }

    delete[] m_buffer;
    m_nrow = other.m_nrow;
    m_ncol = other.m_ncol;
    m_buffer = new double[m_nrow * m_ncol];
    std::copy(other.m_buffer, other.m_buffer + m_nrow * m_ncol, m_buffer);

    return *this;
}

// Move assignment operator 
Matrix & Matrix::operator=(Matrix && other)
{
    if (this == &other) { return *this; } // don't move to self.
    std::swap(other.m_ncol, m_ncol);
    std::swap(other.m_nrow, m_nrow);
    std::swap(other.m_buffer, m_buffer);
    return *this;
}


Matrix::~Matrix()
{
    delete[] m_buffer;
}

double Matrix::operator() (size_t row, size_t col) const
{
    return m_buffer[row * m_ncol + col];
}

double& Matrix::operator() (size_t row, size_t col)
{
    return m_buffer[row * m_ncol + col];
}

bool Matrix::operator==(const Matrix& other) const {
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
        return false;
    }
    for (size_t i = 0; i < m_nrow; i++) {
        for (size_t j = 0; j < m_ncol; j++) {
            if (m_buffer[i*m_ncol+j] != other.m_buffer[i*m_ncol+j]){
                return false;
            }
        }
    }
    return true;
}


size_t Matrix::nrow() const
{
    return m_nrow;
}

size_t Matrix::ncol() const
{
    return m_ncol;
}



double* Matrix::buffer() const
{ 
    return m_buffer;
}


pybind11::array_t<double> Matrix::to_numpy() const {
    // Create a numpy array that doesn't own the data, but rather points to the internal buffer
    return pybind11::array_t<double>(
        {m_nrow, m_ncol},            // shape
        {m_ncol * sizeof(double),    // stride in bytes for each row
         sizeof(double)},            // stride in bytes for each column
        m_buffer,                    // the actual buffer
        pybind11::capsule(m_buffer, [](void *f) { /* custom deleter if necessary */ })
    );
}

// Function to perform naive matrix-matrix multiplication
Matrix multiply_naive(const Matrix& m1, const Matrix& m2) {
    size_t nrow_m1 = m1.nrow();
    size_t ncol_m1 = m1.ncol();
    size_t ncol_m2 = m2.ncol();
    size_t nrow_m2 = m2.nrow();

    if (ncol_m1 != nrow_m2){
        throw std::invalid_argument(
            "Number of columns in the first matrix must be equal"
            " to the number of rows in the second"
            "matrix for matrix multiplication.");
    }
    Matrix result(nrow_m1, ncol_m2);

    for (size_t i = 0; i < nrow_m1; i++) {
        for (size_t j = 0; j < ncol_m2; j++) {
            result(i, j) = 0.0;
            for (size_t k = 0; k < ncol_m1; k++) {
                result(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }

    return result;
}



// Function to perform matrix-matrix multiplication with tiling
Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, size_t tile_size) {
    size_t nrow1 = mat1.nrow();
    size_t ncol1 = mat1.ncol();
    size_t ncol2 = mat2.ncol();

    if (ncol1 != mat2.nrow()) {
        throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for matrix multiplication.");
    }

    // Create a result matrix
    Matrix result(nrow1, ncol2);

    for (size_t i = 0; i < mat1.nrow(); ++i) {
        for (size_t j = 0; j < mat2.ncol(); ++j) {
            result(i, j) = 0;
        }
    }
    // Perform tiling multiplication
    for (size_t i = 0; i < nrow1; i += tile_size) {
        for (size_t j = 0; j < ncol2; j += tile_size) {
            for (size_t k = 0; k < ncol1; k += tile_size) {
                // Compute the indices for the current tile
                size_t i_end = std::min(i + tile_size, nrow1);
                size_t j_end = std::min(j + tile_size, ncol2);
                size_t k_end = std::min(k + tile_size, ncol1);

                // Multiply the current tile
                for (size_t ii = i; ii < i_end; ii++) {
                    for (size_t jj = j; jj < j_end; jj++) {
                        double sum = 0.0;
                        for (size_t kk = k; kk < k_end; ++kk) {
                            sum += mat1(ii, kk) * mat2(kk, jj);
                        }
                        result(ii, jj) += sum;
                    }
                }
            }
        }
    }

    return result;
}



Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2) {
    // Check if the matrices have compatible dimensions
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for matrix multiplication.");
    }

    // Allocate memory for the result matrix
    Matrix result(mat1.nrow(), mat2.ncol());

    // Call MKL's DGEMM routine for matrix multiplication
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                mat1.nrow(), 
                mat2.ncol(), 
                mat1.ncol(), 
                1.0, 
                mat1.buffer(), 
                mat1.ncol(), 
                mat2.buffer(), 
                mat2.ncol(), 
                0.0, 
                result.buffer(), 
                result.ncol());

    return result;
}


namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, std::vector<double> const &>())
        .def("__getitem__", [](const Matrix &m, std::pair<size_t, size_t> idx) {
            return m(idx.first, idx.second);
        })
        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> idx, double val) {
            m(idx.first, idx.second) = val;
        })
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("buffer", &Matrix::buffer)
        .def("to_numpy", &Matrix::to_numpy)
        .def_property_readonly("array", &Matrix::to_numpy);  // Exposing array attribute

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}