#include <iostream>
#include <cstdint>
#include "line.hpp"


Line::Line(size_t size) : vec(size) {

}
size_t Line::size() const {
    return vec.size(); 
}

float const & Line::x(size_t it) const {
    if (it >= size()) 
    { 
        throw std::out_of_range("Line index out of range"); 
    } 
    return vec[it].first;
}

float & Line::x(size_t it) {
    if (it >= size()) 
    { 
        throw std::out_of_range("Line index out of range"); 
    } 
    return vec[it].first;
}

float const & Line::y(size_t it) const {
    if (it >= size()) 
    { 
        throw std::out_of_range("Line index out of range"); 
    } 
    return vec[it].second;
}

float & Line::y(size_t it) {
    if (it >= size()) 
    { 
        throw std::out_of_range("Line index out of range"); 
    } 
    return vec[it].second;
}



