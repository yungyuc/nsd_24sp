# Name of the executable and Python module
PROG := exe
MODULE := _matrix
TEST_SRC := test_matrix.py

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++11 -fPIC
# Include MKL headers and link flags. Adjust these paths according to your MKL installation.
MKLROOT := /opt/intel/oneapi/mkl/latest
CXXFLAGS += -I$(MKLROOT)/include
LDFLAGS := -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

# Pybind11 and Python configuration
PYTHON := python3
PYBIND11_INCLUDE := $(shell $(PYTHON) -m pybind11 --includes)
PYTHON_INCLUDES := $(shell $(PYTHON)-config --includes)
PYBIND11_FLAGS := $(PYTHON_INCLUDES) -I$(PYBIND11_INCLUDE)
EXT_SUFFIX := $(shell $(PYTHON)-config --extension-suffix)

# Source files and object files
SOURCES := matrix.cpp main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
PYBIND_SOURCES := matrix.cpp pybind_matrix.cpp
PYBIND_OBJECTS := $(PYBIND_SOURCES:.cpp=.o)

# Targets
all: $(PROG) $(MODULE)

# Linking the executable
$(PROG): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creating the Python module
$(MODULE):
	$(CXX) $(CXXFLAGS) $(PYBIND11_FLAGS) -o $(MODULE)$(EXT_SUFFIX) $(PYBIND_SOURCES) $(LDFLAGS) -shared

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Run the PROG
run: $(PROG)
	./$(PROG)

# Test the Python module with PyTest
test: clean $(MODULE)
	@echo " ***       TESTING START       *** "
	python3 -m pytest $(TEST_SRC)

# Clean the directory
clean:
	rm -f $(PROG) $(OBJECTS) $(MODULE)$(EXT_SUFFIX) $(PYBIND_OBJECTS)
	find . -type d -name __pycache__ -exec rm -r {} +
	find . -type f -name '*.pyc' -delete
	-rm -rf __pycache__ .pytest_cache

# Phony targets
.PHONY: all run clean test
