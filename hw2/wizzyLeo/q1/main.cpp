#include "Line.h"
#include <iostream>

int main(int, char **) {
    // Create a Line instance with 3 points
    Line line(3);

    // Set values for each point
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    // Copy construct line2 from line
    Line line2(line);

    // Modify the first point in line2
    line2.x(0) = 9;

    // Print details of line
    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    // Print details of line2
    std::cout << "line2: number of points = " << line2.size() << std::endl;
    for (size_t it = 0; it < line2.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}
