#include <cmath>
#include <pybind11/pybind11.h>

namespace py = pybind11;

double angleCalculation(double ax, double ay, double bx, double by){
    double a_scal_b = ax*bx + ay*by;
    double a_norm = std::sqrt(ax*ax + ay*ay);
    double b_norm = std::sqrt(bx*bx + by*by);

    if (a_norm == 0 || b_norm == 0){
        return std::nan("");
    }
    
    if (ax == bx && ay == by){
        return 0;
    }

    double cos = a_scal_b / (a_norm * b_norm);
    cos = std::max(std::min(cos, 1.0), -1.0); 
    return std::acos(cos);

    if (cos > 1){
        cos = 1;
    }
    else if (cos < -1){
        cos = -1;
    }

    return std::acos(cos);

};



PYBIND11_MODULE(_vector,m){
    m.def("calculate_angle", &angleCalculation, "Calculate the angle between two 2D vectors");
}