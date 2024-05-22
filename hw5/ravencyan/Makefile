CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall -shared -fPIC
LDFLAGS = -lblas -lmkl_rt
PYINC = $(shell python3-config --includes --ldflags)
PYBIND11_INC = $(shell python3 -m pybind11 --includes)
MKL_PATH = /usr/include/mkl
INCLUDES = -I./ -I$(MKL_PATH) $(PYINC) $(PYBIND11_INC)

TARGET = _matrix.so
INC = ./matrix.hpp
SRC = ../mod.cpp ./matrix.cpp

all: $(TARGET)

$(TARGET): $(INC) $(SRC)
		pip install pybind11
		$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

test: $(TARGET)
		python3 test_matrix.py
		python3 -m pytest -v -s test_matrix.py
.PHONY: test

clean:
		rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean