#include <cmath>
#include <stdexcept>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "vector2D.hpp"

Vector2D::Vector2D(double x, double y) : m_x(x), m_y(y) {
}

double Vector2D::X() const {
    return m_x;
}

double Vector2D::Y() const {
    return m_y;
}

double Vector2D::AngleBetween(const Vector2D &rhs) {
    if (std::fpclassify(this->Norm() * rhs.Norm()) == FP_ZERO) {
        throw std::invalid_argument("Zero length vector");
    }
    return acos(DotProduct(rhs) / (Norm() * rhs.Norm()));
}

double Vector2D::Norm() const {
    return sqrt(m_x * m_x + m_y * m_y);
}

double Vector2D::DotProduct(const Vector2D &rhs) const {
    return m_x * rhs.m_x + m_y * rhs.m_y;
}


namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.doc() = "Calculate angle between two vectors";
    py::class_<Vector2D>(m, "Vector2D")
        .def(py::init<double, double>())
        .def("angleBetween", &Vector2D::AngleBetween)
        .def("__repr__", [](const Vector2D &v) {
            return "<Vector2D [" + std::to_string(v.X()) + ", " + std::to_string(v.Y()) + "]>";
        }
    );
}
