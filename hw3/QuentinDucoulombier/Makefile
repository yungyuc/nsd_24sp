# Set the executable name
PROG := exe
LIBS := ./_matrix$(PYTHON_SUF)

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -O2 -Wall -fPIC -shared -m64
LDFLAGS := -lblas -lmkl_rt

# Python and MKL settings
PYBIND_INC_FLAGS := $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS := $(shell python3-config --includes --ldflags)
PYTHON_SUF := $(shell python3-config --extension-suffix)
MKL_INC := /usr/include/mkl

# Source files
SRC := matrix.cpp pybind_matrix.cpp main.cpp

# Test and performance files
PERF_OUTPUT := performance.txt
PYTEST := test_matrix.py

# Phony targets
.PHONY: all run clean test perf

# Default build target
all: $(PROG) $(LIBS)

# Executable and library builds
$(LIBS): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS) -o $@ $^ $(LDFLAGS)

$(PROG): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS) -o $@ $^ $(LDFLAGS)

# Run tests
test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

# Performance benchmark
perf: $(PROG)
	./$(PROG) > $(PERF_OUTPUT) 2>&1

# Run program
run: $(PROG)
	./$(PROG)

# Clean up build and cache files
clean:
	rm -f $(PROG) $(LIBS)
	find . -type d -name __pycache__ -exec rm -r {} +
	find . -type f -name '*.pyc' -delete
	-rm -rf __pycache__ .pytest_cache
