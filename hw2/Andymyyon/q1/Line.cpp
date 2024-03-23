#include "Line.hpp"

Line::Line() {}
Line::Line(size_t n) : data(n) {}

// No need to implement the copy, move and assignment operators functions as they are default-handled with TSL vector containers

size_t Line::size() const {
    return data.size();
}

float & Line::x(size_t i) {
    if(i >= 0 && i < size()) {
        return data[i].x;
    }
    throw std::out_of_range("Index out of range");
}

float & Line::y(size_t i) {
    if(i >= 0 && i < size()) {
        return data[i].y;
    }
    throw std::out_of_range("Index out of range");
}

const float & Line::x(size_t i) const {
    if(i >= 0 && i < size()) {
        return data[i].x;
    }
    throw std::out_of_range("Index out of range");
}

const float & Line::y(size_t i) const {
    if(i >= 0 && i < size()) {
        return data[i].y;
    }
    throw std::out_of_range("Index out of range");
}