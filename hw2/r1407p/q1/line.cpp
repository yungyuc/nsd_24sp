#include "line.hpp"

Line::Line(){
    points = {};
}

Line::Line(Line const & other){
    points = other.points;
}

Line::Line(Line && other){
    points = std::move(other.points);
}
Line& Line::operator=(Line const & other){
    points = other.points;
    return *this;
}

Line& Line::operator=(Line && other){
    points = std::move(other.points);
    return *this;
}

Line::Line(size_t size){
    points = vector<pair<float, float>>(size);
}

Line::~Line(){
    points.clear();
}
size_t Line::size() const{
    return points.size();
}

float const & Line::x(size_t it) const{
    return points[it].first;
}
float& Line::x(size_t it){
    return points[it].first;
}
float const & Line::y(size_t it) const{
    return points[it].second;
}
float& Line::y(size_t it){
    return points[it].second;
}
