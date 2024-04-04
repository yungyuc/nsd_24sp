Hardware Aging Acceleration
------------------------------------

Accelerate the hardware aging simulation of the CNN MAC operations. 

Basic Information
-----------------

In the research of the AI Accelerator, we sometimes need to focus on the 
different results of the CNN MAC operations which caused by the hardware 
aging to judge the reliability. With the aging of the MOS, the each operation 
result of the MAC operations will become different, result in that we need 
to build the truthtable for all inputs. 

The whole simulation time will be very long since we need to find the output 
from the truthtable, even though we just simulate a simple 2D convolution. 
Therefore, we want to focus on how to speed up the time for the simulation. 

Here are some information for this work: 

- GitHub Repository: `Hardware Aging Acceleration <https://github.com/zona8815/Hardware-Aging-Acceleration>`__
- Coding
    - C++ and Python
- Aging truthtable
    - MOSRA

Problem to Solve
----------------

As we want to speed up the simulation time, we can list some problems: 

1. The truthtable: 
    The aging effects on MOS will be simulate from MOSRA in advanced, 
    then build the truthtable. We mainly focus on the operation of the 
    multiplication since the correctness is impact serious than the 
    operation of the addition. 
2. Speed up: 
    We will try the best to find the ways to speed up the whole processes, 
    and compare those results to find the best performance one. 
3. Accuracy: 
    While focus on the speed of simulation, we still need to ensure the 
    accuracy of the results. We will do some unit tests for this problem. 

Prospective Users
-----------------

This work is mainly for whom focus on aging of the AI Accelerator, including: 

- Hardware designers and researchers: 
    They can simulate the problems caused by the aging of MOS efficiently. 
- My lab partners

System Architecture
-------------------

We can seperate this work into few categories: 

- Aging simulation results (in advanced): MOSRA
- Calculation of MAC operation: C++
- CNN: Python
- Combination: Pybind11

API Description
---------------

- Calculation of MAC operation: `truthtable.h <https://github.com/zona8815/Hardware-Aging-Acceleration/blob/main/src/truthtable.h>`__,  `multiplier.h <https://github.com/zona8815/Hardware-Aging-Acceleration/blob/main/src/multiplier.h>`__
- CNN (2D convolution): `myconv2d.py <https://github.com/zona8815/Hardware-Aging-Acceleration/blob/main/src/myconv2d.py>`__

Engineering Infrastructure
--------------------------

- System build
    - CMake
- Version control
    - Git
    - GitHub
- Testing
    - Pytest
- Documents
    - Markdown

Schedule
--------

Week 1 (04/08)

- Build the truthtable

Week 2 (04/15)

- Build the CNN architecture in Python
- Complete the requirements in ``CMakeLists.txt``

Week 3 (04/22)

- Build the multiplication operation in C++
- Search for the methods to speed up
- Build the unit tests

Week 4 (04/29)

- Try to speed up the multiplication operation
- Combine with the Pybind11
- Build the unit tests

Week 5 (05/06)

- Try to speed up the multiplication operation
- Complete the todo lists above
- Examine the API format and ``CMakeLists.txt`` is reasonable or not
    - Adjust if they need

Week 6 (05/13)

- Try to speed up the multiplication operation
- Visualization the comparision

Week 7 (05/20)

- Try to speed up the multiplication operation
- Visualization the comparision
- Complete the todo lists above
- Examine the API format and ``CMakeLists.txt`` is reasonable or not
    - Adjust if they need
- Prepare presentation (1/2)

Week 8 (05/27)

- Flexible week
- Test the whole project
- Prepare presentation (2/2)

References 
----------

- `HSPICE® User Guide: Simulation and Analysis Version B-2008.09, September 2008 
<https://cseweb.ucsd.edu/classes/wi10/cse241a/assign/hspice_sa.pdf>`__


