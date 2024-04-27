CXX = g++
CXX_FLAGS = -std=c++11 -O2 -Wall -fPIC -shared
CXX_INCS = -I./include $(PYBIND_INC_FLAGS)

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)
MKL_INC = /opt/intel/oneapi/mkl/2023.2.2/include

Target = matrix
SRC = matrix.cpp
SRC_DIR = ./

PERF_SRC = perf_matrix.py
PERF_OUTPUT = performance.txt
PYTEST = test_matrix.py
LIBS = matrix$(PYTHON_SUF)

.PHONY: test clean

test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

perf: $(LIBS)
	rm -f $(PERF_OUTPUT)
	python3 $(PERF_SRC)

$(LIBS): $(SRC)
	$(CXX) $(CXX_INCS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIBS) $(SRC_DIR)/*.o