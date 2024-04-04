#include "line.hpp"

Line::Line() = default;

Line::Line(size_t size) : m_x_coords(size), m_y_coords(size) {}

// For the following functions, we use the default implementation because the vector class already handles the copy/move constructors and assignment operators.
// We also use the default implementation for the destructor because the vector class will automatically clean up its resources when it goes out of scope
// https://cplusplus.com/reference/vector/vector/
Line::Line(const Line& other) = default;
Line::Line(Line&& other) noexcept = default;
Line& Line::operator=(const Line& other) = default;
Line& Line::operator=(Line&& other) noexcept = default;

Line::~Line() = default;

size_t Line::size() const { return m_x_coords.size(); }

// Getters and setters for x and y coordinatess
const float& Line::x(size_t it) const { return m_x_coords[it]; }
float& Line::x(size_t it) { return m_x_coords[it]; }

const float& Line::y(size_t it) const { return m_y_coords[it]; }
float& Line::y(size_t it) { return m_y_coords[it]; }
