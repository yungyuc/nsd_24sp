#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <cmath>
// #include <pybind11/stl.h>

namespace py = pybind11;

double radian_angle(std::pair<double, double> a, std::pair<double, double> b)
{
    double norme_a = sqrt( a.first*a.first + a.second*a.second);
    double norme_b = sqrt( b.first*b.first + b.second*b.second);
    double produit_scalaire = a.first*b.first + a.second*b.second;

    std::cout << norme_a << std::endl;
    std::cout << norme_b << std::endl;
    std::cout << produit_scalaire << std::endl;

    if (norme_a == 0.0f || norme_b == 0.0f ) {
        std::cout << "Indefined angle " << std::endl;
        
        return -1;

    }

    double div = produit_scalaire/(norme_a*norme_b);

    if (div < -1.0f || div > 1.0f) {
        std::cout << "Indefined angle" << std::endl;
        return -1;
    }
   
    double res_angle = acos(div);

    return res_angle;


    
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("radian_angle", &radian_angle, "Calculate the angle (in radians) between two vectors");
}

