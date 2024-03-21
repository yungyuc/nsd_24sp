#include"Line.h"

Line::Line(){

}

Line::Line(size_t size){
    x_vals.resize(size, 0.0);
    y_vals.resize(size, 0.0);
}
