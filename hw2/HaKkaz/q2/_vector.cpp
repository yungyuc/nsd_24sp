#include <pybind11/pybind11.h>
#include <utility>

using Dt = double;
using vector = std::pair<Dt,Dt>;

Dt dot(vector a, vector b)  { 
    return a.first*b.first + a.second*b.second; 
}

Dt angle_of_vector(const vector &v1, const vector &v2) {
    Dt v1_length = std::sqrt(dot(v1, v1));
    Dt v2_length = std::sqrt(dot(v2, v2));
    return acos(dot(v1, v2) / (v1_length * v2_length));
}


PYBIND11_MODULE(_vector, m) {
    m.doc() = "Calculate the angle between two vectors.";
    m.def("angle_of_vector", &angle_of_vector, "Calculate the angle between two vectors.");
}