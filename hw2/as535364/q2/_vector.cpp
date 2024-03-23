#include <pybind11/pybind11.h>
#include <iostream>
#include <cmath>
namespace py = pybind11;

double angle(double x1, double y1, double x2, double y2) {
  if (x1 == 0 && y1 == 0) throw std::invalid_argument("First vector is zero");
  if (x2 == 0 && y2 == 0) throw std::invalid_argument("Second vector is zero");
  // Calculate the angle between two vectors
  double dot = x1*x2 + y1*y2;
  double det = x1*y2 - y1*x2;
  return atan2(det, dot);
}

PYBIND11_MODULE(_vector, m) {
  m.doc() = "angle between two vectors";      // module doc string
  m.def("angle",                              // function name
        &angle,                               // function pointer
        "A function which calculatr the angle between two vectors" //function doc string
  );
}