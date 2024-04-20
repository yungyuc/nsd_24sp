Hardware Aging Acceleration
------------------------------------

Accelerate the hardware aging simulation of the CNN MAC (Multiply Accumulate) operations. 

Basic Information
-----------------

In the research of the AI Accelerator, we sometimes need to focus on the 
different results of the CNN MAC operations which 
caused by the hardware aging to judge the reliability. With the aging of 
the MOS, the each operation result of the MAC operations will become 
different, result in that we need to build the truthtable for all inputs. 

The whole simulation time will be very long since we need to find the output 
from the truthtable, even though we just simulate a simple 2D convolution. 
Therefore, we want to focus on how to speed up the time for the simulation. 

Here are some information for this work: 

- **GitHub Repository**
    - `Hardware Aging Acceleration <https://github.com/zona8815/Hardware-Aging-Acceleration>`__
- **Coding**
    - C++ and Python
- **Aging truthtable**
    - MOSRA (MOSFET Model Reliability Analysis)

Problem to Solve
----------------

To do the IEEE 754 Standard multiplication, the signed bit refers to the 
logic AND, the exponent refers to the 8 bits adder, and the fraction refers 
to the 23 bits multiplier. 

Since more than 85% of the runtime overhead stuck in the self-defined MAC 
operations by the multiplication of the fraction bits, the runtime now is 
800 seconds per data of two convolutions model that built by ourselves. 

As we want to speed up the simulation time, we can list some problems: 

1. **The truthtable**: 
    The aging effects on MOS will be simulate from MOSRA in advanced, 
    then build the truthtable. We mainly focus on the operation of the 
    multiplication since the correctness is impact serious than the 
    operation of the addition. 
2. **Speed up**: 
    We will try the best to find the ways to speed up the whole processes, 
    and compare those results to find the best performance one. For example, 
    we may use pybind11 to bind python and C++, and do some tricks in the 
    C++ program to get better performance. 
3. **Accuracy**: 
    While focus on the speed of simulation, we still need to ensure the 
    accuracy of the results. We will do some unit tests for this problem. 

Prospective Users
-----------------

This work is mainly for whom focus on aging of the AI Accelerator, including: 

- **Hardware designers and researchers**: 
    They can simulate the problems caused by the aging of MOS efficiently. 
- **My lab partners**

System Architecture
-------------------

We can seperate this work into few categories: 

- Aging simulation results (in advanced): MOSRA
- Calculation of MAC operation: C++
- CNN: Python
- Combination: Pybind11

API Description
---------------

- **The truthtable by the aging**

.. code-block:: cpp

    // truthtable.h
    int TableHalfAdder(int a, int b);
    int TableFullAdder(int a, int b, int c);

- **Calculation of MAC operation**

.. code-block:: cpp

    // multiplier.h 
    Multiplier::Multiplier() : a_(0), b_(0), c_(0) {}

    Multiplier::Multiplier(std::size_t a, std::size_t b, std::size_t c)
    : a_(a), b_(b), c_(c) {}

    Multiplier::~Multiplier() {}

    std::size_t Multiplier::a() const { return a_; }
    std::size_t Multiplier::b() const { return b_; }
    std::size_t Multiplier::c() const { return c_; }

    Multiplier HalfAdder(std::size_t a, std::size_t b);
    Multiplier FullAdder(std::size_t a, std::size_t b, std::size_t c);

- **CNN (2D convolution)**

.. code-block:: python
    
    # myconv2d.py
    # self-defined convolution
    import torch
    from torch.nn.modules.utils import _pair

    class MyConv2d(torch.nn.modules.conv._ConvNd): 
        def __init__(self, in_channels, out_channels, kernel_size, stride=1,
                    padding=0, dilation=1, groups=1,
                    bias=True, padding_mode='zeros'):
        
        def conv2d_forward(self, input, weight):
        
        def forward(self, input):
        
    def myconv2d(input, weight, bias=None, stride=1, padding=0, dilation=1, groups=1):

Engineering Infrastructure
--------------------------

- **System build**
    - CMake
- **Version control**
    - Git
    - GitHub
- **Testing**
    - Pytest
- **Documents**
    - Markdown

Schedule
--------

Week 1 (04/08)

- Build the truthtable

Week 2 (04/15)

- Build the CNN architecture in Python
- Complete the requirements in ``CMakeLists.txt``
- Build the unit tests

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

Week 6 (05/13)

- Try to speed up the multiplication operation
- Visualization the comparision

Week 7 (05/20)

- Try to speed up the multiplication operation
- Visualization the comparision
- Complete the todo lists above
- Examine the API format and ``CMakeLists.txt`` is reasonable or not
- Prepare presentation (1/2)

Week 8 (05/27)

- Flexible week
- Test the whole project
- Prepare presentation (2/2)

References 
----------

- `HSPICE® User Guide: Simulation and Analysis Version B-2008.09, September 2008 
<https://cseweb.ucsd.edu/classes/wi10/cse241a/assign/hspice_sa.pdf>`__


