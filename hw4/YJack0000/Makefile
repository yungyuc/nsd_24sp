CXX             = g++
SRC             = _matrix.cpp _allocator.cpp _pybind.cpp
FLAGS           = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES        = -I$(MKL_INCLUDE_DIR) $(PYINC) $(PYBIND11_INC)
LDFLAGS         = -lblas -lmkl_rt $(PYLIB)
MKL_INCLUDE_DIR = /usr/include/mkl

PYINC           = $(shell python3-config --includes)
PYBIND11_INC    = $(shell python3 -m pybind11 --includes)
PYLIB           = $(shell python3-config --ldflags)
PYSUFFIX        = $(shell python3-config --extension-suffix)
PYBIND11_MODULE = _matrix _allocator _pybind
PYTAR           = $(PYBIND11_MODULE)$(PYSUFFIX)

all: $(PYTAR)

$(PYTAR): $(SRC)
	$(CXX) $(FLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)
.PHONY: all

test: $(PYTAR)
	python3 test_matrix.py
	python3 -m pytest -v -s test_matrix.py
.PHONY: test

perf: all
	python3 performance.py
.PHONY: perf

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean
