#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>

double get_length(std::pair<double, double> v) {
    return std::sqrt(v.first * v.first + v.second * v.second);
}


double get_angle(std::pair<double, double> v1, std::pair<double, double> v2) {
    double v1_len = get_length(v1);
    double v2_len = get_length(v2);

    double dot_product = v1.first * v2.first + v1.second * v2.second;

    double angle = acos(dot_product / (v1_len * v2_len));

    return angle;
}

PYBIND11_MODULE(_vector, m) {
    m.def("get_angle", &get_angle, "This function calculates the angle between two vectors in the 2D Cartesian coordinate system.");
}