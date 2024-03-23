#include "line.hpp"

void Line::checkIdx(size_t i) const {
    if (i >= n) {
        throw std::out_of_range("Index out of range");
    }
}

// copy assignment operator
Line & Line::operator=(const Line& line) {
    if (this == &line) return *this;
    n = line.n;
    cord = line.cord;
    return *this;
}