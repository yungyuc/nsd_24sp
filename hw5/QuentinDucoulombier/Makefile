# Compiler settings
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -shared -fPIC
MKL_INC = /usr/include/mkl
PYBIND11_INCLUDES = $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDES = $(shell python3-config --includes)
PYTHON_LDFLAGS = $(shell python3-config --ldflags)
PYBIND11_FLAGS = $(PYTHON_INCLUDES) $(PYBIND11_INCLUDES)
PYTHON_EXT_SUFFIX = $(shell python3-config --extension-suffix)

# Library and Linker settings
LDFLAGS = -lblas -lmkl_rt $(PYTHON_LDFLAGS)

# Source and Target settings
MODULE = _matrix$(PYTHON_EXT_SUFFIX)
SOURCES = ../mod.cpp matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Include settings
INCLUDES = -I./ -I$(MKL_INC) $(PYBIND11_INCLUDES) $(PYTHON_INCLUDES)

# Test settings
TEST_SRC = test_matrix.py

# Targets
all: $(MODULE)

# Creating the Python module
$(MODULE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

# Compiling C++ source files
%.o: %.cpp matrix.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

# Testing the Python module with PyTest
test: $(MODULE)
	python3 -m pytest -v $(TEST_SRC)

# Clean the build directory
clean:
	rm -f $(MODULE) $(OBJECTS)
	rm -rf __pycache__ .pytest_cache *.so *.txt

# Phony targets
.PHONY: all clean test
