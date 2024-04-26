CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -fPIC -shared -m64 $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

MKL_INC = /usr/include/mkl

SRC = _matrix.cpp
PERF_SRC = perf_matrix.py
PERF_OUTPUT = performance.txt
PYTEST = test_matrix.py
LIBS = ./_matrix$(PYTHON_SUF)

.PHONY: test clean

test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

perf: $(LIBS)
	rm -f $(PERF_OUTPUT)
	python3 $(PERF_SRC)

$(LIBS): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIBS)