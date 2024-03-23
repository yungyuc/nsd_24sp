#include <utility>
#include <vector>
#include <cstddef>
#include <stdexcept>

class Line {
private:
    size_t n;
    std::vector<std::pair<float, float>> cord;
    void checkIdx(size_t i) const;
public:
    size_t size() const { return n; }
    Line (size_t n): n(n) {
        cord.resize(n);
    }
    ~Line() {
        cord.clear();
    }
    Line(const Line &line): n(line.n), cord(line.cord) {}
    Line& operator=(const Line &line);
    float &x(size_t i) { checkIdx(i); return cord[i].first; }
    const float &x(size_t it) const { checkIdx(it); return cord[it].first; }
    float &y(size_t i) { checkIdx(i); return cord[i].second; }
    const float &y(size_t it) const { checkIdx(it); return cord[it].second; }
};