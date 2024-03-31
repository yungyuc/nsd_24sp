#include "line.hpp"
using namespace std;

Line::Line() {}

Line::Line(Line const &line2) : vx(line2.vx), vy(line2.vy) {}

Line::Line(Line &&line2) : vx(std::move(line2.vx)), vy(std::move(line2.vy)) {}

Line &Line::operator=(Line const &line2) {
    if (this != &line2) {
        vx = line2.vx;
        vy = line2.vy;
    }
    return *this;
}

Line &Line::operator=(Line &&line2) {
    if (this != &line2) {
        vx = std::move(line2.vx);
        vy = std::move(line2.vy);
    }
    return *this;
}

Line::Line(size_t size) : vx(size), vy(size) {}

Line::~Line() {}

size_t Line::size() const {
    return vx.size();
}

float const &Line::x(size_t it) const {
    return vx[it];
}

float &Line::x(size_t it) {
    return vx[it];
}

float const &Line::y(size_t it) const {
    return vy[it];
}

float &Line::y(size_t it) {
    return vy[it];
}