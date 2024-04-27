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
template <class Type>
class CustomAllocator{
    private:
        static size_t byte_num;
        static size_t allocated_num;
        static size_t de_allocated_num;
    public:
        using value_type = Type;
        CustomAllocator() noexcept = default;

        // Allocate function
        Type * allocate(size_t n)
        { 
            // n : 分配的數量
            // check if n is bigger than limit
            if (n > std::numeric_limits<std::size_t>::max()/sizeof(Type)){
                throw std::bad_alloc(); // momory allocation failed
            }
            // calculate the bytes of allocated memory
            const size_t bytes = n*sizeof(Type);
            // allocate memory dynamically and point to T
            // malloc return (void *) pointer,透過cast to (T *) pointer.
            // use this memory area to stores T type object. 
            // " T *p means p is a pointer to T type object."
            Type *p = static_cast<Type*>(std::malloc(bytes)); // malloc bytes and return the pointer, cast to Type.
            // if p is nullptr, means memory allocation failed
            if (!p){
                throw std::bad_alloc();
            }
            byte_num += bytes; // increase the allocated memory
            allocated_num += bytes; // increase the allocated memory

            return p; // return the pointer of allocated memory
        }
        // deallocate function
        void deallocate(Type *p, size_t n) noexcept
        {
            // calculate the bytes of deallocated memory
            const size_t bytes = n*sizeof(Type);
            byte_num -= bytes; // decrease the allocated memory
            de_allocated_num += bytes; // increase the deallocated memory
            // free the memory
            std::free(p);
        }
        // 

        // bytes function
        static size_t bytes()
        {
            return byte_num;
        }
        static size_t allocated(){
            return allocated_num;
        };
        static size_t deallocated()
        {
            return de_allocated_num;
        };
        
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
        Matrix(size_t row, size_t col); //constructor
        double operator()(size_t row, size_t col) const; // operator() : get the value of matrix at row, col
        double & operator()(size_t row, size_t col); // operator() : get the value of matrix at row, col
        size_t get_row() const; // get row
        size_t get_col() const; // get col
        bool operator==(const Matrix &rhs) const; // operator == : compare two matrix
        buffer_type get_buffer() const; // get buffer
        

    private:
        // row and column
        size_t row=0;
        size_t col=0;
        // buffer data;
        buffer_type buffer;

};
Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

#endif