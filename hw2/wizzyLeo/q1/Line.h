#ifndef LINE_H
#define LINE_H
#include <vector>

class Line {
public:
    Line() = default;
    explicit Line(size_t size) : x_vals(size), y_vals(size) {}
    Line(const Line&) = default;
    Line(Line&&) = default;
    Line& operator=(const Line&) = default;
    Line& operator=(Line&&) = default;
    ~Line() = default;

    size_t size() const;

    const float& x(size_t it) const;

    float& x(size_t it) ;

    const float& y(size_t it) const;

    float& y(size_t it);

private:
    std::vector<float> x_vals;
    std::vector<float> y_vals;
};

#endif