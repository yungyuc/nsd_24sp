#include "_vector.h"
#include <cmath>
#include <utility>

double calculateAngle(const std::pair<double, double>& vec1, const std::pair<double, double>& vec2) {
    double dot_product = vec1.first * vec2.first + vec1.second * vec2.second;
    double magnitude1 = std::sqrt(vec1.first * vec1.first + vec1.second * vec1.second);
    double magnitude2 = std::sqrt(vec2.first * vec2.first + vec2.second * vec2.second);
    return std::acos(dot_product / (magnitude1 * magnitude2));
}
