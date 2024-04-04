#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include<utility>

/* calculate the angle between two vectors in 2d Cartesian coordinate system */
double _vec_angle(std::pair<double, double> v1, std::pair<double, double> v2){
    /* magnitude */
    double m1 = sqrt(v1.first * v1.first + v1.second * v1.second);
    double m2 = sqrt(v2.first * v2.first + v2.second * v2.second);

    /* zero magnitude (length) */
    if(m1 == 0 || m2 == 0) return -1;

    /* dot product */
    double dot = v1.first * v2.first + v1.second * v2.second;

    /* angle */
    double angle = acos(dot / (m1 * m2));

    return angle;
}

PYBIND11_MODULE(_vector, m){
    m.doc() = "angle between two vectors in 2d Cartesian coordinate system";
    m.def("_vec_angle", &_vec_angle, "calculate the angle between two vectors in 2d Cartesian coordinate system");
}