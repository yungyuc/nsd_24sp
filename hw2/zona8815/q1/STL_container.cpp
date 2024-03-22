#include <iostream>
#include <vector>

class Line
{
public:
    // Default constructor
    Line() = default;

    // Copy constructor
    /* Line(const Line &other) : points(other.points) {} */
    Line(const Line &) = default;

    // Move constructor
    /* Line(Line &&other) noexcept : points(std::move(other.points)) {} */
    Line(Line &&) = default;

    // Copy assignment operator
    /* Line &operator=(const Line &other) {
        if (this != &other) {
            points = other.points;
        }
        return *this;
    } */
    Line &operator = (const Line &) = default;

    // Move assignment operator
    /* Line &operator=(Line &&other) noexcept {
        if (this != &other) {
            points = std::move(other.points);
        }
        return *this;
    } */
    Line &operator = (Line &&) = default;

    // Constructor with size
    Line(size_t size) : points(size) {}

    // Destructor
    ~Line() = default;

    // Function to return size
    size_t size() const {
        return points.size();
    }

    // Function to access x coordinate at index it
    float const &x(size_t it) const {
        return points[it].first;
    }

    float &x(size_t it) {
        return points[it].first;
    }

    // Function to access y coordinate at index it
    float const &y(size_t it) const {
        return points[it].second;
    }

    float &y(size_t it) {
        return points[it].second;
    }

private:
    // Member data: using vector of pairs to store (x, y) coordinates
    std::vector<std::pair<float, float>> points;
};

int main(int, char **) {
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}
