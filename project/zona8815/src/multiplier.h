// multiplier.h

#include <stdexcept>
#include "truthtable.h"

class Multiplier {
public:
    // default constructor
    Multiplier();

    // constructor with value
    Multiplier(std::size_t a, std::size_t b, std::size_t c);

    // deconstructor
    ~Multiplier();

    // getter
    std::size_t a() const;
    std::size_t b() const;
    std::size_t c() const;

private: 
    std::size_t a_, b_, c_;
};

Multiplier::Multiplier() : a_(0), b_(0), c_(0) {}

Multiplier::Multiplier(std::size_t a, std::size_t b, std::size_t c)
  : a_(a), b_(b), c_(c) {}

Multiplier::~Multiplier() {}

std::size_t Multiplier::a() const { return a_; }
std::size_t Multiplier::b() const { return b_; }
std::size_t Multiplier::c() const { return c_; }

Multiplier HalfAdder(std::size_t a, std::size_t b);
Multiplier FullAdder(std::size_t a, std::size_t b, std::size_t c);
