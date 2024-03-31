# (Project Proposal) DeliveryOptimizer: A Simplified Home-to-Home Delivery Optimization Tool

## Basic Information

DeliveryOptimizer aims to provide a simplified yet efficient solution for
optimizing home-to-home delivery routes. The codebase will be hosted on GitHub
at: https://github.com/QuentinDucoulombier/DeliveryOptimizer

The project will be developed using a combination of C++ for computational
efficiency and Python for ease of use and data handling.

## Problem to Solve

The primary challenge addressed by DeliveryOptimizer is the optimization of
delivery routes for a single delivery vehicle, minimizing the total distance
traveled while ensuring each home is visited exactly once. Unlike traditional
delivery optimization problems, this simplified version does not consider
vehicle capacity constraints or specific delivery time windows.

## Prospective Users

The target users of DeliveryOptimizer include:

- Small to medium-sized enterprises (SMEs) operating in the e-commerce and
logistics sectors that require a straightforward tool for planning delivery
routes.

## System Architecture

DeliveryOptimizer will consist of two main components:

1. C++ Backend: This component will handle route calculations and optimizations.
It will generate a cost matrix for all pairs of delivery locations and apply
optimization algorithms to find the minimal route.
2. Python Frontend: The frontend will be responsible for data input and
visualization. Users will input delivery location data (e.g., addresses) through
a Python interface, and the optimized route will be visualized using libraries
like Matplotlib or Folium.

## API Description

The DeliveryOptimizer API will include:

- C++ Library: Functions to load delivery location data, calculate the cost
matrix, and determine the optimal route. The library will provide a clean and
efficient interface for route optimization algorithms.
- Python Wrapper: A Python wrapper around the C++ library, simplifying data
input and enabling easy visualization of the optimized route on a map.

To refer to, the potential architecture will be:

### C++ Library

The C++ API provides the following functions:

```cpp
// Load delivery location data
void load_delivery_locations(const std::vector<Location>& locations);

// Calculate the cost matrix
std::vector<std::vector<double>> calculate_cost_matrix();

// Determine the optimal route
std::vector<Location> determine_optimal_route(
    const std::vector<std::vector<double>>& cost_matrix);
```

### Python Wrapper

The Python API wraps around the C++ library, offering simplified access and
visualization:

```python
# Load delivery location data
def load_delivery_locations(locations: List[Tuple[float, float]]) -> None:

# Calculate the cost matrix
def calculate_cost_matrix() -> List[List[float]]:

# Determine the optimal route
def determine_optimal_route(cost_matrix: List[List[float]]) -> List[
    Tuple[float, float]]:

# Visualize the optimized route on a map
def visualize_optimized_route(route: List[Tuple[float, float]]) -> None:
```

## Engineering Infrastructure

- Use `make` to build.
- Use `git` for version control.
- Use `pytest` for testing.

## Schedule

- Week 1 (4/8): Define project requirements, design system architecture, plan
implementation strategy, and incorporate algorithm learning.
- Week 2-3 (4/15 - 4/22): Implement route optimization algorithms in C++,
including cost matrix generation and optimization techniques.
- Week 4-5 (4/29 - 5/6): Develop a Python interface for data input and
visualization of optimized routes.
- Week 6-7 (5/13 - 5/20): Integrate backend and frontend components, write unit
tests, and perform system testing.
- Week 8 (5/27): Document the code and prepare for presentation

## References

- https://en.wikipedia.org/wiki/Travelling_salesman_problem
- https://www.researchgate.net/publication/305679885_A_Traveling_Salesman_Problem_with_Pickups_and_Deliveries_Time_Windows_and_Draft_Limits_Case_Study_from_Chemical_Shipping