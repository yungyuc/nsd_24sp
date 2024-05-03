CXX = g++
CXX_INCS = -I./include $(PYBIND_INC_FLAGS)
CXXFLAGS = -std=c++11 -O2 -Wall -fPIC -shared $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

MKL_INC = /usr/include/mkl

SRC_DIR = ./src

TARGET = _matrix

SRC = $(SRC_DIR)/_matrix.cpp

PERF_SRC = perf_matrix.py
PERF_OUTPUT = performance.txt
PYTEST = test_matrix.py
LIBS = _matrix$(PYTHON_SUF)

.PHONY: test clean

test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

perf: $(LIBS)
	rm -f $(PERF_OUTPUT)
	python3 $(PERF_SRC)

$(LIBS): $(SRC)
	$(CXX) $(CXX_INCS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -c -o $@ $<

clean:
	rm -f $(LIBS) $(SRC_DIR)/*.o