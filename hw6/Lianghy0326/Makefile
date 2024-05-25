# Source and header files
SRC = matrix.cpp
INC = matrix.hpp  

# Compiler and flags
CXX = clang++

# Include numpy
NUMPY_INC_FLAG = $(shell python3 -c "import numpy; print(numpy.get_include())")

# Include MKL (set this to the correct MKL include path on your system)
MKL_INC = /usr/include/mkl

# Compilation flags
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -I. -I$(NUMPY_INC_FLAG) -I$(MKL_INC) `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

# Library target
LIB_TARGET = _matrix.so

# Default target
all: $(LIB_TARGET)

# Rule to build the shared library( # Install dependencies )
$(LIB_TARGET): $(SRC) $(INC)
	pip install pybind11
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

# Testing
.PHONY: test
test: $(LIB_TARGET)
	env PYTHONPATH=".:$$PYTHONPATH" python3 -m pytest -v

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(LIB_TARGET) __pycache__ .pytest_cache *.so
