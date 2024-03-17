#ifndef __LINE_HPP__
#define __LINE_HPP__
#include <vector>

class Line {
public:
  Line();
  Line(Line const &);
  Line(Line &&);
  Line &operator=(Line const &);
  Line &operator=(Line &&);
  Line(std::size_t size);
  ~Line();
  std::size_t size() const;
  float const &x(std::size_t it) const;
  float &x(std::size_t it);
  float const &y(std::size_t it) const;
  float &y(std::size_t it);

private:
  std::vector<float> _x;
  std::vector<float> _y;
};

#endif
