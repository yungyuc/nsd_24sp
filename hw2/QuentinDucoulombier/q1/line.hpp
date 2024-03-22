#pragma once
#include <vector>
#include <cstddef>

class Line {
public:
    // Default constructor
    Line();
    // Constructor with size
    Line(size_t size);
    // Copy constructor
    Line(const Line& other);
    // Move constructor
    Line(Line&& other) noexcept;
    // Copy assignment operator
    Line& operator=(const Line& other);
    // Move assignment operator
    Line& operator=(Line&& other) noexcept;
    // Destructor (Virtual for proper cleanup since std::vector will automatically clean up its resources)
    virtual ~Line();

    // Get the number of points
    size_t size() const;
    // Get the x coordinate of a point
    const float& x(size_t it) const;
    // Set the x coordinate of a point
    float& x(size_t it);
    // Get the y coordinate of a point
    const float& y(size_t it) const;
    // Set the y coordinate of a point
    float& y(size_t it);

private:
    // Coordinates of the points
    std::vector<float> m_x_coords;
    std::vector<float> m_y_coords;
};
