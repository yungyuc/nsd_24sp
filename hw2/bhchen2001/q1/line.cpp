#include"line.hpp"

/* constructors */

Line::Line(){
    _x = std::vector<float>();
    _y = std::vector<float>();
}

Line::Line(Line const & l){
    _x = l._x;
    _y = l._y;
}

Line::Line(size_t size){
    _x = std::vector<float>(size);
    _y = std::vector<float>(size);
}

/* copy assignment operators */

Line & Line::operator=(Line const & l){
    _x = l._x;
    _y = l._y;
    return *this;
}

/* move assignment operator */

Line & Line::operator=(Line && l){
    _x = std::move(l._x);
    _y = std::move(l._y);
    return *this;
}

/* destructor */

Line::~Line(){
    _x.clear();
    _y.clear();
}

/* member functions */

size_t Line::size() const{
    if(_x.size() != _y.size()){
        throw std::runtime_error("x and y size mismatch");
    }
    return _x.size();
}

float const & Line::x(size_t it) const{
    if(it >= _x.size()){
        throw std::out_of_range("x index out of range");
    }
    return _x.at(it);
}

float & Line::x(size_t it){
    if(it >= _x.size()){
        throw std::out_of_range("x index out of range");
    }
    return _x.at(it);
}

float const & Line::y(size_t it) const{
    if(it >= _y.size()){
        throw std::out_of_range("y index out of range");
    }
    return _y.at(it);
}

float & Line::y(size_t it){
    if(it >= _y.size()){
        throw std::out_of_range("y index out of range");
    }
    return _y.at(it);
}