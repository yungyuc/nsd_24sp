#include "Line.h"

size_t Line::size() const {
    return x_vals.size();
}

const float& Line::x(size_t it) const {
    return x_vals.at(it); 
}

float& Line::x(size_t it) {
    return x_vals.at(it); 
}

const float& Line::y(size_t it) const {
    return y_vals.at(it); 
}

float& Line::y(size_t it) {
    return y_vals.at(it); 
}
