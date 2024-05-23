CXX = g++
CXX_INCS = -I./include -I$(PYBIND_INC_FLAGS) -I$(NUMPY_INC_FLAG)
CXXFLAGS = -std=c++11 -O3 -Wall -fPIC -shared $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)
NUMPY_INC_FLAG = $(shell python3 -c 'import numpy; print(numpy.get_include())')

MKL_INC = /usr/include/mkl

SRC_DIR = ./src
SRC = $(SRC_DIR)/matrix.cpp
PYTEST = test_matrix.py
LIBS = ./_matrix$(PYTHON_SUF)

.PHONY: test clean

test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

$(LIBS): $(SRC)
	$(CXX) $(CXX_INCS) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIBS)