#include <pybind11/pybind11.h>
#include <cmath>
#include <utility> // For std::pair
#include <limits> // For std::numeric_limits


// Calculate the angle between two vectors represented as std::pair<float, float>
double calculateAngle(const std::pair<float, float>& v0, const std::pair<float, float>& v1) {
    // Calculate dot product
    float dotProduct = v0.first * v1.first + v0.second * v1.second;
    
    // Calculate magnitudes of the vectors
    float magnitudeV0 = std::sqrt(v0.first * v0.first + v0.second * v0.second);
    float magnitudeV1 = std::sqrt(v1.first * v1.first + v1.second * v1.second);
    
    // Check for zero-length vectors to prevent division by zero
    if (magnitudeV0 == 0.0f || magnitudeV1 == 0.0f) {
        // Return NaN to indicate error
        return std::numeric_limits<float>::quiet_NaN();
    }
    
    // Calculate cosine of the angle
    float cosAngle = dotProduct / (magnitudeV0 * magnitudeV1);
    
    // Clamp the value to prevent numerical issues with acos
    cosAngle = std::max(-1.0f, std::min(1.0f, cosAngle));
    
    // Calculate and return the angle in radians
    return std::acos(cosAngle);
}


namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.doc() = "calculateAngle(radians) between two vectors";
    m.def("calculateAngle", &calculateAngle, "Calculate the angle between two vectors");
}
