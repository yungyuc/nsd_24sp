#pragma once

class Vector2D {
public:
    Vector2D(double x = 0.0, double y = 0.0);
    double X() const;
    double Y() const;
    double AngleBetween(const Vector2D &rhs);
    double Norm() const;
    double DotProduct(const Vector2D &rhs) const;

private:
    double m_x, m_y;
};
