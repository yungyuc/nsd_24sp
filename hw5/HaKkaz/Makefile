CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -fPIC -shared -m64 $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)
NUMPY_INC_FLAG = $(shell python3 -c 'import numpy; print(numpy.get_include())')

MKL_INC = /usr/include/mkl

SRC = ../mod.cpp ./matrix.cpp
LIBS = ./_matrix$(PYTHON_SUF)


$(LIBS): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -I$(NUMPY_INC_FLAG) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIBS)