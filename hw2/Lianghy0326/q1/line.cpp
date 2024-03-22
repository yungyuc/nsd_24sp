// line.cpp
#include "line.hpp"

Line::Line() = default;

Line::Line(size_t size) : x_coords(size), y_coords(size) {}

Line::Line(const Line &line) = default;
Line::Line(Line &&line) noexcept = default;
Line& Line::operator=(const Line &line) = default;
Line& Line::operator=(Line &&line) noexcept = default;

Line::~Line() = default;

size_t Line::size() const {
    return x_coords.size();
}

float const& Line::x(size_t it) const {
    return x_coords.at(it);
}

float& Line::x(size_t it) {
    return x_coords.at(it);
}

float const& Line::y(size_t it) const {
    return y_coords.at(it);
}

float& Line::y(size_t it) {
    return y_coords.at(it);
}
