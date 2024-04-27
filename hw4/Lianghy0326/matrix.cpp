#include "matrix.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// CustomAllocator
template <typename Type> 
Type *CustomAllocator<Type>::allocate(size_t n){
    // allocate the memory
    Type *p = (Type *)std::malloc(n*sizeof(Type));
    // if the memory is not allocated, throw an exception
    if (!p){
        throw std::bad_alloc();
    }
    // calculate the bytes of allocated memory
    const size_t bytes = n*sizeof(Type);
    byte_num += bytes; // increase the allocated memory
    allocated_num += bytes; // increase the allocated memory

    return p; // return the pointer of allocated memory
}
// deallocate function
template <typename Type>
void CustomAllocator<Type>::deallocate(Type *p, size_t n){
    // calculate the bytes of deallocated memory
    const size_t bytes = n*sizeof(Type);
    byte_num -= bytes; // decrease the allocated memory
    de_allocated_num += bytes; // increase the deallocated memory
    // free the memory
    std::free(p);
}
// bytes function
template <typename Type>
size_t CustomAllocator<Type>::bytes(){
    return byte_num;
}
// allocated function
template <typename Type>
size_t CustomAllocator<Type>::allocated(){
    return allocated_num;
}
// deallocated function
template <typename Type>
size_t CustomAllocator<Type>::deallocated(){
    return de_allocated_num;
}

//========Matrix==============
// constructor
Matrix::Matrix(size_t row, size_t col){
    this->row = row;
    this->col = col;
    // buffer the data
    buffer =  buffer_type(row*col);
}
// operator() : get the value of matrix at row, col
double Matrix::operator()(size_t row,size_t col) const{
    return buffer[row*this->col+col];
}
// operator() : get the value of matrix at row, col
double & Matrix::operator()(size_t row, size_t col){
    return buffer[row*this->col+col];
}
// get row
size_t Matrix::get_row() const{
    return row;
}
// get col
size_t Matrix::get_col() const{
    return col;
}
// operator == : compare two matrix
bool Matrix::operator==(const Matrix &rhs) const{
    // if row and col are not equal, return false
    if (row != rhs.row || col != rhs.col){
        return false;
    }
    // compare the buffer data
    for (size_t i=0; i<row*col; i++){
        if (buffer[i] != rhs.buffer[i]){
            return false;
        }
    }
    return true;
}
// get buffer
Matrix::buffer_type Matrix::get_buffer() const{
    return buffer;
}


// multiply naive
Matrix multiply_naive(const Matrix &m1,const Matrix &m2){
    if (m1.get_col() != m2.get_row()){
        throw std::invalid_argument("Matrix size mismatch");
    }
    // create a new matrix
    Matrix result(m1.get_row(),m2.get_col());
    // multiply the matrix
    for (size_t i=0; i<m1.get_row(); i++){
        for (size_t j=0; j<m2.get_col(); j++){
            for (size_t k=0; k<m1.get_col(); k++){
                result(i,j) += m1(i,k)*m2(k,j);
            }
        }
    }
    return result;
}
// multiply tile
Matrix multiply_tile(const Matrix &m1,const Matrix &m2,size_t tile_size){
    if (m1.get_col() != m2.get_row()){
        throw std::invalid_argument("Matrix size mismatch");
    }
    // create a new matrix
    Matrix result(m1.get_row(),m2.get_col());
    // multiply the matrix
    for (size_t i=0; i<m1.get_row(); i+=tile_size){
        for (size_t j=0; j<m2.get_col(); j+=tile_size){
            for (size_t k=0; k<m1.get_col(); k+=tile_size){
                size_t limit = std::min(m1.get_row(),i+tile_size);
                for (size_t ii=i; ii<limit; ii++){
                    size_t limit2 = std::min(m2.get_col(),j+tile_size);
                    for (size_t jj=j; jj<limit2; jj++){
                        size_t limit3 = std::min(m1.get_col(),k+tile_size);
                        double sum = 0;
                        for (size_t kk=k; kk<limit3; kk++){
                            sum += m1(ii,kk)*m2(kk,jj);
                        }
                        result(ii,jj) += sum;
                    }
                }
            }
        }
    }
    return result;
}
// muliply mkl
Matrix multiply_mkl(const Matrix &m1,const Matrix &m2){
    if (m1.get_col() != m2.get_row()){
            throw std::invalid_argument("Matrix size mismatch");
        }
    // create a new matrix
    Matrix result(m1.get_row(),m2.get_col());
    // CBLAS
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1.get_row(), m2.get_col(), m1.get_col(), 1.0, m1.get_buffer().data(), m1.get_col(), m2.get_buffer().data(), m2.get_col(), 0.0, result.get_buffer().data(), result.get_col());
    return result;
}
// pybind module
PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "Matrix mutiplication module";
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())

        .def("__setitem__", [](Matrix &m, std::pair<size_t, size_t> const & p, double val){
            m(p.first, p.second) = val;
        })
        .def("__getitem__", [](Matrix &m, std::pair<size_t, size_t> const & p){
            return m(p.first, p.second);
        })
        .def_property_readonly("row", &Matrix::get_row)
        .def_property_readonly("col", &Matrix::get_col)
        .def("__eq__", &Matrix::operator==);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);

    m.def("allocate", &CustomAllocator<double>::allocated, "Allocate memory");
    m.def("deallocate", &CustomAllocator<double>::deallocated, "Deallocate memory");
    m.def("bytes", &CustomAllocator<double>::bytes, "Get bytes");

}
