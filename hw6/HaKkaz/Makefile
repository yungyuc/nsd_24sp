SRC = _matrix.cpp
CXX = g++
PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
NUMPY_INC_FLAG = $(shell python3 -c "import numpy; print(numpy.get_include())")

CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -I. $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS) -I$(NUMPY_INC_FLAG) -I$(MKL_INC)
LDFLAGS = -lblas -lmkl_rt

LIBS = _matrix.so

MKL_INC = /usr/include/mkl

all: $(LIBS)

$(LIBS): $(SRC)
	pip install pybind11
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(LIBS) __pycache__ .pytest_cache *.so