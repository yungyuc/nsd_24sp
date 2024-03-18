#include <iostream>
#include <math.h>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

float calculate_angle(std::vector<float>& point1, std::vector<float>& point2){
    float x1 = point1[0];
    float y1 = point1[1];
    float x2 = point2[0];
    float y2 = point2[1];
    // std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    if(x1 ==0 && y1 == 0){
        throw std::invalid_argument("First point cannot be the origin");
    }
    if(x2 ==0 && y2 == 0){
        throw std::invalid_argument("Second point cannot be the origin");
    }
    float dot_product = x1*x2 + y1*y2;
    float len1 = std::sqrt(x1*x1 + y1*y1);
    float len2 = std::sqrt(x2*x2 + y2*y2);
    float cos_theta = dot_product/(len1 * len2);
    if (cos_theta >= 1.0f){
        cos_theta = 1;
    }else if (cos_theta <= -1.0f){
        cos_theta = -1;
    }

    // std::cout << cos_theta << std::endl;
    // std::cout << std::acos(cos_theta) << std::endl;
    float res = std::acos(cos_theta);
    return res;
}

PYBIND11_MODULE(angle, m) {
    m.doc() = "pybind11 angle plugin"; // optional module docstring
    m.def("calculate_angle", &calculate_angle, "A function which calculates the angle between two points");
}
