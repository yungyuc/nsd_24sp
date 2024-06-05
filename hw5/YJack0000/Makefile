CXX             = g++
FLAGS           = -O3 -Wall -shared -std=c++17 -fPIC

NUMPYINCLUDE=$(shell python3 -c 'import numpy; print(numpy.get_include())')

INCLUDES        = -I$(MKL_INCLUDE_DIR) $(PYINC) $(PYBIND11_INC) -I$(NUMPYINCLUDE)
LDFLAGS         = -lblas
MKL_INCLUDE_DIR = /usr/include/mkl

PYINC           = $(shell python3-config --includes)
PYBIND11_INC    = $(shell python3 -m pybind11 --includes)
PYSUFFIX        = $(shell python3-config --extension-suffix)
PYBIND11_MODULE = _matrix
PYTAR           = $(PYBIND11_MODULE)$(PYSUFFIX)

all: $(PYTAR)

$(PYTAR): mod.o matrix.o
	$(CXX) $(FLAGS) -o $(PYTAR) $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< $(INCLUDES) -o $@

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean