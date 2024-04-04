#include <iostream>
#include <vector>

class Line
{
public:
    Line() : _x(0), _y(0){};
    Line(Line const &) = default;
    Line(Line &&) = default;
    Line &operator=(Line const &) = default;
    Line &operator=(Line &&) = default;
    Line(size_t size) : _x(size), _y(size){};
    ~Line() = default;
    size_t size() const { return _x.size(); };
    float const &x(size_t it) const { return _x[it]; };
    float &x(size_t it) { return _x[it]; };
    float const &y(size_t it) const { return _y[it]; };
    float &y(size_t it) { return _y[it]; };

private:
    std::vector<float> _x, _y;
}; /* end class Line */

int main(int, char **)
{
    Line line(3);
    line.x(0) = 0;
    line.y(0) = 1;
    line.x(1) = 1;
    line.y(1) = 3;
    line.x(2) = 2;
    line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it) << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it) << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}
