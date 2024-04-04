#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>
#include <iostream>
#include <exception>

typedef double ff;
typedef std::vector<ff> vf;

inline ff norm(const vf &a)
{
    return sqrt(a[0] * a[0] + a[1] * a[1]);
}

inline ff dot(const vf &a, const vf &b)
{
    return a[0] * b[0] + a[1] * b[1];
}

ff angle(vf a, const vf &b)
{
    if (a.size() != 2 || b.size() != 2)
        throw std::range_error("vector size not equals to 2");
    return acos(dot(a, b) / (norm(a) * norm(b)));
}

// ref: https://bayareanotes.com/pybind-tutorial/
PYBIND11_MODULE(_vector, m)
{
    m.def("angle", &angle, "A function that calculates the angle (in radians) between two vectors in the 2-dimensional Cartesian coordinate system");
}
