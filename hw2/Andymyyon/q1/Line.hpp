#pragma once

#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
};

class Line {
private:
    std::vector<Point> data;

public:
    Line();
    Line(size_t n);
    size_t size() const;
    float& x(size_t i);
    float& y(size_t i);
    const float& x(size_t i) const;
    const float& y(size_t i) const;
};