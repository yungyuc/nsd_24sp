#include <iostream>
#include <math.h>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

float calculate_angle(std::pair<float,float> point1, std::pair<float,float> point2){
    float x1 = point1.first;
    float y1 = point1.second;
    float x2 = point2.first;
    float y2 = point2.second;
    
    if(x1 ==0 && y1 == 0){
        throw std::invalid_argument("First point cannot be the origin");
    }
    if(x2 ==0 && y2 == 0){
        throw std::invalid_argument("Second point cannot be the origin");
    }
    float dot_product = x1*x2 + y1*y2;
    float len1 = sqrt(x1*x1 + y1*y1);
    float len2 = sqrt(x2*x2 + y2*y2);
    float cos_theta = dot_product/(len1 * len2);
    return acos(cos_theta);
}

PYBIND11_MODULE(angle, m) {
    m.doc() = "pybind11 angle plugin"; // optional module docstring
    m.def("calculate_angle", &calculate_angle, "A function which calculates the angle between two points");
}
