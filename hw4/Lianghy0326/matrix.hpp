#ifndef  MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <limits>
#include<stdexcept>
#include<mkl/mkl.h>
#include<atomic>
#include<cstddef>
#include<new>
#include<cstdlib>


using namespace std;
// using buffer = std::vector<double,CustomAllocator<double>>;

// 2. CustomAllocator
template <typename Type>
class CustomAllocator{
    private:
        static size_t byte_num;
        static size_t allocated_num;
        static size_t de_allocated_num;
    public:
        using value_type = Type;
        CustomAllocator() noexcept = default;

        Type *allocate(size_t n);
        void deallocate(Type *p, size_t n);
        static size_t bytes();
        static size_t allocated();
        static size_t deallocated();
        
};
// initialize the static member
template <class Type>
size_t CustomAllocator<Type>::byte_num = 0;
template <class Type>
size_t CustomAllocator<Type>::allocated_num = 0;
template <class Type>
size_t CustomAllocator<Type>::de_allocated_num = 0;


// 3. Matrix
class Matrix{
    public:
        // buffer type 
        using buffer_type = std::vector<double,CustomAllocator<double>>;
        Matrix(size_t nrow, size_t ncol); //constructor
        double operator()(size_t nrow, size_t ncol) const; // operator() : get the value of matrix at row, col
        double & operator()(size_t nrow, size_t ncol); // operator() : get the value of matrix at row, col
        size_t nrow() const; // get row
        size_t ncol() const; // get col
        bool operator==(const Matrix &rhs) const; // operator == : compare two matrix
        buffer_type get_buffer() const; // get buffer
        

    private:
        // row and column
        size_t nrow=0;
        size_t ncol=0;
        // buffer data;
        buffer_type buffer;

};
Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

#endif