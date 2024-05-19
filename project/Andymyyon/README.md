### Project Name:
**Dynamic Airspace Management System (DAMS)**

### Basic Information
- **GitHub Repository URL**: [https://github.com/Andymyyon/DAMS]
- **About Statement**: "Optimizing airspace allocation for air traffic control
through dynamic Voronoi diagram partitioning to ensure safety and efficiency in
air traffic management."

### Problem to Solve
- **Field**: Aviation, Air Traffic Management
- **Background**: Air Traffic Management (ATM) is essential for ensuring the
safety and efficiency of aircraft operations within the global airspace system.
Traditional ATM systems face challenges in balancing controller workloads,
especially in areas of high traffic density or during peak operational times.
Dynamic allocation of airspace can offer a solution by adjusting sector sizes
and responsibilities in real-time to ensure an equitable distribution of
workload among air traffic controllers.
- **Physics/Mathematics**: This project will leverage computational geometry,
specifically Voronoi diagrams (in 2D), to partition airspace dynamically based on the
geographic locations of Air Traffic Control (ATC) towers or centers and the
positions of aircraft in flight.
- **Algorithm/Numerical Method**: We will use Voronoi diagram generation
algorithms for dynamic airspace partitioning, coupled with real-time data
processing and load-balancing algorithms to assess and adjust the distribution
of air traffic control workload.

### Prospective Users
- The primary users of DAMS will be air traffic controllers and ATC operations
managers, who will utilize the system to monitor and manage the dynamic
allocation of airspace sectors, thus enhancing their situational awareness and
decision-making capabilities.
- The system can also be beneficial for aviation safety analysts and airspace
planners in optimizing airspace structures and workflows.

### System Architecture
- **Input**: The system will take real-time and historical air traffic data
(including aircraft positions, velocities, and flight plans) and ATC capacity
and location data as inputs.
- **Operations**: DAMS will parse and process the input data, compute dynamic
Voronoi diagrams for airspace partitioning, assess workloads, and allocate or
reallocate airspace sectors accordingly.
- **Output**: The system will produce updated airspace sector maps and workload
distribution reports. Alerts for manual intervention or adjustment by human
controllers may also be generated.
- **Interface**: Instead of a web-based dashboard, DAMS will offer a command-line
interface (CLI) as I don't think I will have time to implement a proper GUY
 This will allow users to interact with
the system, input data, and view results.
- **Constraints**: The system assumes the availability and accuracy of real-time
air traffic data. It also relies on computational efficiency to handle dynamic
updates.
- **Modularization**: The system will be modularized into several components,
including data ingestion, Voronoi computation, workload assessment, and user
interface modules.

### API Description
- DAMS will utilize C++ for performance-critical components, such as the core
algorithms for Voronoi diagram computation and workload analysis, while Python
will be used for data ingestion, interfacing with the C++ components, and
developing the user interface (CLI/GUI).

### Engineering Infrastructure
- **Build System**: The project will use Make for building the C++ components,
defined in a `Makefile`, which will specify how to compile the components and
integrate them with the Python parts of the project.
- **Documentation**: Documentation will be generated using Doxygen, particularly
for the C++ codebase, to provide detailed, auto-generated API documentation.
Efforts will be made to integrate Python documentation with Sphinx.

### Schedule
- Week 1: Project setup, initial literature review, and data source identification.
- Week 2: Basic implementation of Voronoi diagram algorithm in C++.
- Week 3: Development of data ingestion and preprocessing modules in Python.
- Week 4: Integration of C++ and Python components; initial testing.
- Week 5: Development of workload assessment algorithms.
- Week 6: User interface development
- Week 7: Final testing and minor bugs fixing (I will test my code continuously through the development for major bugs)
- Week 8: Final review, documentation completion, and project presentation
preparation.
