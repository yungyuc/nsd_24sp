#pragma once
#include <vector>
#include <iostream>

class Line
{
public:
    Line() = default;
    Line(Line const & )= default;
    Line(Line       &&)= default;
    Line & operator=(Line const & )= default;
    Line & operator=(Line       &&)= default;
    Line(size_t size);
    ~Line()= default;
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);

   
private:
    // Member data.
    std::vector<std::pair<float, float>> vec;
}; /* end class Line */

