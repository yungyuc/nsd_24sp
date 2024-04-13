# Name of the executable and Python module
PROG := exe
TEST_SRC := test_matrix.py

# Compiler and flags
CXX := g++
CXXFLAGS := -O3 -Wall -m64 -std=c++11 -fPIC $(shell pkg-config --cflags mkl-dynamic-lp64-iomp)
# Include MKL headers and link flags. Adjust these paths according to your MKL installation.
MKL_INC := /usr/include/mkl
#CXXFLAGS += -I$(MKL_INC)

# Library paths and the libraries to link against
LDFLAGS := $(shell pkg-config --libs mkl-dynamic-lp64-iomp)

# Pybind11 and Python configuration
PYTHON := python3
PYBIND11_INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)
PYTHON_INCLUDES := $(shell $(PYTHON)-config --includes)
PYBIND11_FLAGS := $(PYTHON_INCLUDES) $(PYBIND11_INCLUDES)
EXT_SUFFIX := $(shell $(PYTHON)-config --extension-suffix)
MODULE := _matrix$(EXT_SUFFIX)

# Source files and object files
SOURCES := matrix.cpp main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
PYBIND_SOURCES := matrix.cpp pybind_matrix.cpp
PYBIND_OBJECTS := $(PYBIND_SOURCES:.cpp=.o)

# Targets
all: $(PROG) $(MODULE)

# Linking the executable
$(PROG): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Creating the Python module
$(MODULE): $(PYBIND_OBJECTS)
	$(CXX) -shared -o $@ $^ $(LDFLAGS) 

# Compiling
%.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) -I$(MKL_INC) $(PYBIND11_FLAGS) $<

# Run the PROG
run: $(PROG)
	./$(PROG)

# Test the Python module with PyTest
test: $(MODULE)
	@echo " ***       TESTING START       *** "
	python3 -m pytest $(TEST_SRC)

# Performance testing
perf: $(PROG)
	./$(PROG) >> performance.txt 2>&1
	./$(PROG) > performance.txt 2>&1

# Clean the directory
clean:
	rm -f $(PROG) $(OBJECTS) $(MODULE) $(PYBIND_OBJECTS)
	find . -type d -name __pycache__ -exec rm -r {} +
	find . -type f -name '*.pyc' -delete
	-rm -rf __pycache__ .pytest_cache

# Phony targets
.PHONY: all run clean test perf
