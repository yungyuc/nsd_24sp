#include "line.hpp"

Line::Line() {}
Line::Line(size_t _sz) {
    px.resize(_sz);
    py.resize(_sz);
}

Line::Line(const Line& other) {
    px = other.px;
    py = other.py;
}

Line::Line(Line&& other) {
    px = std::move(other.px);
    py = std::move(other.py);
}

Line::~Line() {px.clear(); py.clear();}

Line& Line::operator=(Line const & other){
    px = other.px;
    py = other.py;
    return *this;
}

Line& Line::operator=(Line && other){
    px = std::move(other.px);
    py = std::move(other.py);
    return *this;
}

float const & Line::x(size_t it) const {
    return px[it];
}

float & Line::x(size_t it) {
    return px[it];
}

float const & Line::y(size_t it) const {
    return py[it];
}

float & Line::y(size_t it) {
    return py[it];
}

size_t Line::size() const {
    return px.size();

}