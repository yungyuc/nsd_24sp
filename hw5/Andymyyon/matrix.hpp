#pragma once

#include <vector>
#include <iostream>
#include <memory>

// Custom Allocator for handling memory allocations in Matrix
template <typename T>
class MyAlloc : public std::allocator<T> {
public:
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using value_type = T;

    static inline size_t allocatedBytes = 0;
    static inline size_t deallocatedBytes = 0;
    static inline size_t currentlyUsedBytes = 0;

    template<typename U>
    struct rebind { using other = MyAlloc<U>; };

    MyAlloc() = default;
    template<typename U>
    MyAlloc(const MyAlloc<U>&) {}

    ~MyAlloc() = default;

    T* allocate(size_t num, const void* hint = 0) {
        size_t bytes = num * sizeof(T);
        allocatedBytes += bytes;
        currentlyUsedBytes += bytes;
        return std::allocator<T>::allocate(num, hint);
    }

    void deallocate(T* p, size_t num) {
        size_t bytes = num * sizeof(T);
        deallocatedBytes += bytes;
        currentlyUsedBytes -= bytes;
        std::allocator<T>::deallocate(p, num);
    }
};

template <typename T>
using CustomVector = std::vector<T, MyAlloc<T>>;

// Matrix class definition using CustomVector
class Matrix {
public:
    Matrix(size_t nrow, size_t ncol);
    Matrix(size_t nrow, size_t ncol, const std::vector<double>& vec);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    ~Matrix();

    bool operator==(const Matrix& other) const;

    double operator()(size_t row, size_t col) const;
    double& operator()(size_t row, size_t col);

    size_t nrow() const;
    size_t ncol() const;
    size_t size() const;
    double buffer(size_t i) const;
    std::vector<double> buffer_vector() const;
    double* data();
    const double* data() const;

private:
    size_t m_nrow;
    size_t m_ncol;
    CustomVector<double> m_buffer;

    size_t index(size_t row, size_t col) const;
};

Matrix operator*(const Matrix& mat1, const Matrix& mat2);
std::ostream& operator<<(std::ostream& ostr, const Matrix& mat);

Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2);
Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, int tile_size);
Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2);

bool check_result(const Matrix& mat1, const Matrix& mat2);
