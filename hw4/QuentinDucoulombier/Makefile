# Compiler settings
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++11 -fPIC -m64
MKL_INC = /usr/include/mkl
PYBIND11_INCLUDES = $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDES = $(shell python3-config --includes --ldflags)
PYBIND11_FLAGS = $(PYTHON_INCLUDES) $(PYBIND11_INCLUDES)
PYTHON_EXT_SUFFIX = $(shell python3-config --extension-suffix)

# Library and Linker settings
LDFLAGS = -lblas -lmkl_rt

# Source and Target settings
EXE = matrix_performance
MODULE = _matrix$(PYTHON_EXT_SUFFIX)
SOURCES = main.cpp matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PYBIND_SOURCES = matrix.cpp pybind_matrix.cpp
PYBIND_OBJECTS = $(PYBIND_SOURCES:.cpp=.o)

# Test settings
TEST_SRC = test_matrix.py
PERF_SRC = perf_matrix.py
PERF_OUTPUT = performance.txt

# Targets
all: $(EXE) $(MODULE)

# Linking the executable for performance testing
$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Creating the Python module
$(MODULE): $(PYBIND_OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS) $(PYBIND11_FLAGS)

# Compiling C++ source files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) -I$(MKL_INC)

# Compiling Pybind11 source files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) -I$(MKL_INC) $(PYBIND11_FLAGS)

# Testing the Python module with PyTest
test: $(MODULE)
	python3 -m pytest -v $(TEST_SRC)

# Performance testing
perf: $(EXE)
	./$(EXE) > $(PERF_OUTPUT) 2>&1

# Clean the build directory
clean:
	rm -f $(EXE) $(MODULE) $(OBJECTS) $(PYBIND_OBJECTS)
	rm -rf __pycache__ .pytest_cache *.so *.txt

# Phony targets
.PHONY: all clean test perf
