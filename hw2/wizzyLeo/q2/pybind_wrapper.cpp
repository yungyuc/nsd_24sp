#include <pybind11/pybind11.h>
#include "_vector.h"  // Include the header where calculateAngle is declared

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_angle", &calculateAngle, "Calculate the angle between two 2D vectors");
}
