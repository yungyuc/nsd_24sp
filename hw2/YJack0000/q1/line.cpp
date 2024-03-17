#include "line.hpp"
#include <cstddef>
#include <sys/wait.h>

Line::Line() {}

Line::Line(size_t size) : _x(size), _y(size) {}

Line::Line(Line const &other) : _x(other._x), _y(other._y) {}

Line::Line(Line &&other) : _x(std::move(other._x)), _y(std::move(other._y)) {}

Line &Line::operator=(Line const &other) {
  _x = other._x;
  _y = other._y;
  return *this;
}

Line &Line::operator=(Line &&other) {
  _x = std::move(other._x);
  _y = std::move(other._y);
  return *this;
}

Line::~Line() {}

size_t Line::size() const { return _x.size(); }

float const &Line::x(size_t it) const { return _x[it]; }

float &Line::x(size_t it) { return _x[it]; }

float const &Line::y(size_t it) const { return _y[it]; }

float &Line::y(size_t it) { return _y[it]; }
