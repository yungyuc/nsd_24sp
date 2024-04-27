#ifndef  MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>


using namespace std;
// using buffer = std::vector<double,CustomAllocator<double>>;

// 1. Count the byte of the allocated memory
template <class Type>
class CountByte{
    public:
        // increase function - increase allocated
        static void increase(size_t inc){
            allocated += inc;
        };
        // decrease function - increase for de_allocated
        static void decrease(size_t dec){
            de_allocated += dec;
        };
        // 3 functions
        static size_t allocated(){
            return allocated;
        }
        static size_t deallocated(){
            return de_allocated;
        }
        static size_t bytes(){
            return allocated-deallocated;
        }

    // private member 
    private:
        // allocated part
        static size_t allocated;
        static size_t de_allocated;
};
// initialize the static member
template <class Type>
size_t CountByte<Type>::allocated = 0;
template <class Type>
size_t CountByte<Type>::de_allocated = 0;


// 2. CustomAllocator
template <class Type>
class CustomAllocator{
    public:
        using value_type = T;
        CustomAllocator() noexcept = default;
        
        // Allocate function
        Type * allocate(size_t n)
        { 
            // n : 分配的數量
            // check if n is bigger than limit
            if (n>std::numeric_limits<size_t>::max()/sizeof(Type)){
                throw std::bad_alloc(); // momory allocation failed
            }
            // calculate the bytes of allocated memory
            const auto bytes = n*sizeof(Type);
            // allocate memory dynamically and point to T
            // malloc return (void *) pointer,透過cast to (T *) pointer.
            // use this memory area to stores T type object. 
            // " T *p means p is a pointer to T type object."
            T *p = static_cast<Type*>(std::malloc(bytes)); // malloc bytes and return the pointer, cast to Type.
            // if p is nullptr, means memory allocation failed
            if (!p){
                throw std::bad_alloc();
            }
            // if p is not nullptr, increase the allocated memory
            CountByte<Type>::increase(bytes);

            //CountByte<Type>::increase(n*sizeof(Type));
            //return static_cast<Type*>(::operator new(n*sizeof(Type)));

            return p; // return the pointer of allocated memory
        }
        // deallocate function
        void deallocate(Type *p, size_t n) noexcept
        {
            // if p is nullptr, return
            if (!p){
                return;
            }
            // calculate the bytes of deallocated memory
            const auto bytes = n*sizeof(Type);
            // deallocate memory
            std::free(p);
            // decrease the deallocated memory
            CountByte<Type>::decrease(bytes);
        }
};

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