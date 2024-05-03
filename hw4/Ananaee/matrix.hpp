#pragma once
#include <vector>
#include <iostream>
#include <cstdint>
#include <mkl/mkl.h>


template<typename T>
class CustomAllocator : public std::allocator<T> {
    public:
        // Type definitions required by the allocator
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = size_t;
        
        // Rebind allocator to type U
        template<typename U>
        struct rebind {
            typedef CustomAllocator<U> other;
        };

        // Default constructor
        CustomAllocator() = default;

        // Copy constructor
        template<typename U>
        CustomAllocator(const CustomAllocator<U>&) {}

        // Destructor
        ~CustomAllocator() = default;

        // Allocate memory for 'n' objects of type T
        pointer allocate(size_type n, const void* hint = 0) {
            // std::cout << "\n\nallocate function called. We currently have:\nAllocatedBytes = " << allocated_bytes << "\nDeallocatedBytes = " << deallocated_bytes << "\nCurrentlyUsedBytes = " << current_allocated;
            // Track allocated bytes
            current_allocated += n * sizeof(T);
            allocated_bytes += n * sizeof(T);
            // std::cout << "\nAllocated " << n * sizeof(T) << " bytes\n";
            // std::cout << "We now have:\nAllocatedBytes = " << allocated_bytes << "\nDeallocatedBytes = " << deallocated_bytes << "\nCurrentlyUsedBytes = " << current_allocated;
            return std::allocator<T>::allocate(n, hint);

        }

        // Deallocate memory for 'n' objects of type T starting at 'p'
        void deallocate(pointer p, size_type n) noexcept {
            // std::cout << "\n\ndeallocate function called. We currently have:\nAllocatedBytes = " << allocated_bytes << "\nDeallocatedBytes = " << deallocated_bytes << "\nCurrentlyUsedBytes = " << current_allocated;

            // Track deallocated bytes
            current_allocated -= n * sizeof(T);
            deallocated_bytes += n * sizeof(T);
            // std::cout << "\ndeAllocated " << n * sizeof(T) << " bytes\n";
            // std::cout << "We now have:\nAllocatedBytes = " << allocated_bytes << "\nDeallocatedBytes = " << deallocated_bytes << "\nCurrentlyUsedBytes = " << current_allocated;
            std::allocator<T>::deallocate(p, n);
        }

        // Public access functions for member variables
        static size_t get_current_allocated() {
            return current_allocated;
        }

        static size_t get_allocated_bytes() {
            return allocated_bytes;
        }

        static size_t get_deallocated_bytes() {
            return deallocated_bytes;
        }
       

    private:
        static size_t allocated_bytes; // Track allocated bytes
        static size_t deallocated_bytes; // Track deallocated bytes
        static size_t current_allocated; // Track current allocated bytes
};

template<typename T>
size_t CustomAllocator<T>::current_allocated = 0;

template<typename T>
size_t CustomAllocator<T>::allocated_bytes = 0;

template<typename T>
size_t CustomAllocator<T>::deallocated_bytes = 0;



class Matrix {

    public:
        // Matrix();
        Matrix(size_t nrow, size_t ncol);
        Matrix(size_t nrow, size_t ncol, std::vector<double, CustomAllocator<double>> const & vec);


        // TODO: copy and move constructors and assignment operators.
        Matrix(Matrix const & );
        Matrix(Matrix       &&);
        Matrix & operator=(Matrix const & ); // copy assignment operator.
        Matrix & operator=(Matrix       &&);

        ~Matrix();

        double operator() (size_t row, size_t col) const;
        double& operator() (size_t row, size_t col);
        bool operator== (const Matrix& other) const;

        size_t nrow() const;
        size_t ncol() const;

        double* buffer() ;
        const double* buffer() const;


    private:
        size_t m_nrow = 0;
        size_t m_ncol = 0;
        // double * m_buffer = nullptr;
        std::vector<double, CustomAllocator<double>> m_buffer;

};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);



