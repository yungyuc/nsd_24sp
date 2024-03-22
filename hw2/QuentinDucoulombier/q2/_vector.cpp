#include <cmath>
#include <pybind11/pybind11.h>

namespace py = pybind11;

double calculateAngleRad(double x1, double y1, double x2, double y2) {
    double dotProduct = x1 * x2 + y1 * y2;
    double lenA = std::sqrt(x1 * x1 + y1 * y1);
    double lenB = std::sqrt(x2 * x2 + y2 * y2);

    // If the length of one of the vectors is 0, the angle is undefined
    if (lenA == 0 || lenB == 0) {
        return std::nan("");
    }
    
    // If the vectors are the same, the angle is 0
    if (x1 == x2 && y1 == y2) {
        return 0;
    }

    double cosAngle = dotProduct / (lenA * lenB);
    // Ensure cosAngle is in the range [-1, 1]
    cosAngle = std::max(std::min(cosAngle, 1.0), -1.0); 
    return std::acos(cosAngle);
}

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_angle", &calculateAngleRad, "Calculate the angle between two vectors");
}
