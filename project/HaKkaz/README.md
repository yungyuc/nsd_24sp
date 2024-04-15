Point In Polygon
---

## Basic Information
GitHub repository: [Point in Polygon](https://github.com/HaKkaz/Point-in-Polygon)

The Point in Polygon problem is a fundamental problem in computational geometry
that involves determining whether a given point lies inside, outside, 
or on the boundary of a polygon.

## Problem to Solve
The basic point-in-polygon problem is easy to solve 
when the polygon is contain $N$ edges and there is only one point in each query, 
using the Ray Casting algorithm, with a time complexity of $O(N)$.

However, this library addresses a more advanced problem 
where each query may contain $M$ points, 
and it solves it with a time complexity of $O((N+M) \log_{2}{(N+M)})$.

### Ray Casting Algorithm
The way of finding whether the point is inside or outside a simple polygon 
is to test how many times a ray, 
starting from the point and going in any fixed direction,
intersects the edges of the polygon. 
If the point is on the outside of the polygon 
the ray will intersect its edge an even number of times.

In more complex scenarios, such as advanced tasks, 
where multiple points are involved in a single query, 
an additional step is required. 
This involves sorting the polygon's edges and 
utilizing a balanced tree structure capable of supporting rank queries 
to efficiently track the number of intersections of each point.

## Prospective Users
For users who need to develop geospatial software, 
many software services now require the use of mapping functionality, 
especially applications involving location or geographic information. 
This is particularly true when dividing areas, 
as seen in services like Uber, Airbnb, Pokemon GO, etc.


## System Architeure
- Using ``C++`` to implement the algorithm.
- Using ``pybind11`` to make API in python.

## API Description

- `C++` Types
```cpp
template<typename T>
class Point {
    T x, y;
}

template<typename T>
class Segment {
    Point<T> a,b;
    int id;
}

template<typename T>
class Polygon {
    private:
        std::vector< vector<Segment<T>> > polygons;
    public:
        std::vector<bool> points_in_polygon(std::vector<Segment<T>> q_points);
}
```

- `Python` APIs:
    - `Polygon(points: List[Point])`: create a polygon.
    - `polygon.solve(Queries: List[Point])`: solve the query contain multiple points.

## Engineering Infrastructure
- Use ``CMake`` to build the binaries.
- Use ``git`` for version control.
- Use ``pytest`` for testing the performance and correctness.


## Schedule
- Week 1 (4/8): Research the advanced point-in-polygon algorihm.
- Week 2 (4/15): Implement the C++ version `class Polygon`, `class Point` and `Makefile`.
- Week 3 (4/22): Implement the C++ version of point-in-polygon algorithm.
- Week 4 (4/29): Not in Taiwan. 
- Week 5 (5/6): Wrap the API function and write unit test.
- Week 6 (5/13): Test for performance.
- Week 7 (5/20): Complete README.md.
- Week 8 (5/27): Prepare for presentation

## References
- https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm