# ifndef _MATRIX_HPP
# define _MATRIX_HPP

#include<iostream>
#include<vector>
#include<stdexcept>
#include<mkl/mkl.h>
#include<atomic>
#include<cstddef>
#include<limits>
#include<new>
#include<cstdlib>

class ByteCounterImpl{
public:
    size_t allocated = 0;
    size_t deallocated = 0;
    size_t refcount = 0;
};

class ByteCounter{
public:
    ByteCounter()
        : m_impl(new ByteCounterImpl){
        incref();
    }
    ByteCounter(ByteCounter const & other)
        : m_impl(other.m_impl){
        incref();
    }
    ByteCounter & operator=(ByteCounter const & other){
        if (&other != this){
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }
    ByteCounter(ByteCounter && other)
        : m_impl(other.m_impl){
        incref();
    }
    ByteCounter & operator=(ByteCounter && other){
        if (&other != this){
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }
    ~ByteCounter(){
        decref();
    }
    void increase(std::size_t amount){
        m_impl->allocated += amount;
    }
    void decrease(std::size_t amount){
        m_impl->deallocated += amount;
    }
    std::size_t bytes() const{
        return m_impl->allocated - m_impl->deallocated;
    }
    std::size_t get_allocated() const{
        return m_impl->allocated;
    }
    std::size_t get_deallocated() const{
        return m_impl->deallocated;
    }
    std::size_t refcount() const{
        return m_impl->refcount;
    }

private:
    void incref(){
        ++m_impl->refcount;
    }
    void decref(){
        if (nullptr == m_impl) {}
        else if (1 == m_impl->refcount)
        {
            delete m_impl;
            m_impl = nullptr;
        }
        else
        {
            --m_impl->refcount;
        }
    }
    ByteCounterImpl * m_impl;
};

ByteCounter counter;

template <class T>
struct myAllocator
{
    using value_type = T;
    myAllocator() = default;
    T * allocate(std::size_t n){
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)){
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T * p = static_cast<T *>(std::malloc(bytes));
        if (p){
            counter.increase(bytes);
            return p;
        }
        else{
            throw std::bad_alloc();
        }
    }
    void deallocate(T * p, std::size_t n) noexcept{
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }
};

size_t bytes() { return counter.bytes(); }
size_t allocated() { return counter.get_allocated(); }
size_t deallocated() { return counter.get_deallocated(); }

class Matrix {
    public:

        using m_buffer_type = std::vector<double, myAllocator<double>>;

        Matrix(size_t nrow, size_t ncol);

        double   operator() (size_t row, size_t col) const;
        double & operator() (size_t row, size_t col);

        size_t nrow() const;
        size_t ncol() const;

        bool operator==(Matrix const & other) const;

        m_buffer_type buffer() const;
        double * data();
        const double * data() const; 

    private:

        size_t index(size_t row, size_t col) const;

        size_t m_nrow = 0;
        size_t m_ncol = 0;
        
        m_buffer_type m_buffer;
};

Matrix multiply_naive(const Matrix &m1, const Matrix &m2);
Matrix multiply_tile(const Matrix &m1, const Matrix &m2, size_t tile_size);
Matrix multiply_mkl(const Matrix &m1, const Matrix &m2);

# endif