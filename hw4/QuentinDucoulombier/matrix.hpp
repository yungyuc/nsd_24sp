#pragma once
#include <iostream>
#include <cstddef>
#include <vector>
#include <memory> // For std::allocator
#include <algorithm> 
#include <iomanip>
#include <chrono>
#include <mkl/mkl.h>

const size_t TILE_SIZE = 128;

// Custom allocator definition
template<typename T>
class CustomAllocator : public std::allocator<T> {
public:
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using value_type = T;

    static size_t current_allocated;
    static size_t current_deallocated;

    template<typename U>
    struct rebind {
        typedef CustomAllocator<U> other;
    };

    CustomAllocator() = default;

    template<typename U>
    CustomAllocator(const CustomAllocator<U>&) {}

    pointer allocate(size_type n, const void* hint = 0) {
        pointer ptr = std::allocator<T>::allocate(n, hint);
        current_allocated += n * sizeof(T);
        std::cout << "Allocated " << n * sizeof(T) << " bytes\n";
        return ptr;
    }

    void deallocate(pointer p, size_type n) {
        current_deallocated += n * sizeof(T);
        current_allocated -= n * sizeof(T);
        std::cout << "Deallocated " << n * sizeof(T) << " bytes\n";
        std::allocator<T>::deallocate(p, n);
    }
    
};

template<typename T>
size_t CustomAllocator<T>::current_allocated = 0;

template<typename T>
size_t CustomAllocator<T>::current_deallocated = 0;

class Matrix {
public:
    // Constructors
    Matrix(size_t nrow, size_t ncol); // Basic constructor
    Matrix(const Matrix& other); // Copy constructor
    
    // Copy assignment operator
    Matrix& operator=(const Matrix& other);
    
    // Destructor
    ~Matrix() = default; // Default as vector handles its own memory
    
    // Move constructor and assignment operator are implicitly handled by vector
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(Matrix&& other) noexcept = default;

    // Matrix operations
    double operator()(size_t row, size_t col) const;
    double& operator()(size_t row, size_t col);

    bool operator==(const Matrix& other) const;

    // Getters and setters
    size_t nrow() const;
    size_t ncol() const;
    double* data();
    const double* data() const;

private:
    size_t nrow_;
    size_t ncol_;
    std::vector<double, CustomAllocator<double>> buffer_; // Now using std::vector with custom allocator
};

Matrix multiply_naive(const Matrix& A, const Matrix& B);
Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tile_size = TILE_SIZE);
Matrix multiply_mkl(const Matrix& A, const Matrix& B);
