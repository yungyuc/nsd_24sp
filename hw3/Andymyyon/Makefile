CXX = g++
CXXFLAGS = -O3 -std=c++11
LIBS = -lmkl_rt
PYTHON = python3
PYBIND11_INCLUDE = $(shell $(PYTHON) -c "import pybind11; print(pybind11.get_include())")
PYTHON_INCLUDES = $(shell $(PYTHON)-config --includes)
PYBIND11_FLAGS = -I$(PYBIND11_INCLUDE) $(PYTHON_INCLUDES)
MKLROOT=/usr/lib/x86_64-linux-gnu

# Default target
all: matrix #_matrix

# Standalone executable
matrix:
	$(CXX) $(CXXFLAGS) -DSKIP_PYBIND11 -o matrix _matrix.cpp $(LIBS)

# Python module with pybind11
# _matrix:
# 	$(CXX) $(CXXFLAGS) $(PYBIND11_FLAGS) -o _matrix$(shell $(PYTHON)-config --extension-suffix) _matrix.cpp $(LIBS) -shared -fPIC
# _matrix:
# 	$(CXX) $(CXXFLAGS) $(PYBIND11_FLAGS) -o _matrix$(shell $(PYTHON)-config --extension-suffix) _matrix.cpp $(LIBS) -shared -fPIC
# 	echo "Renaming file to _matrix.so"
# 	mv _matrix$(shell $(PYTHON)-config --extension-suffix) _matrix.so

# Run tests
test:
	$(CXX) $(CXXFLAGS) $(PYBIND11_FLAGS) -o _matrix$(shell $(PYTHON)-config --extension-suffix) _matrix.cpp $(LIBS) -shared -fPIC
	echo "Renaming file to _matrix.so"
	mv _matrix$(shell $(PYTHON)-config --extension-suffix) _matrix.so
	$(PYTHON) -m pytest

# Clean up build artifacts
clean:
	rm -f performance.txt matrix _matrix.so
	find . -type d -name __pycache__ -exec rm -r {} +
	find . -type d -name .pytest_cache -exec rm -r {} +
	find . -type f -name '*.pyc' -delete