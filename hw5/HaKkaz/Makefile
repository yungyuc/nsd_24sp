SRC =../mod.cpp matrix.cpp 
CXX = g++
PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -lblas $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
LIBS = _matrix.so

NUMPY_INC_FLAG= $(shell python3 -c "import numpy; print(numpy.get_include())")

all: $(LIBS)

$(LIBS): $(SRC)
	pip install pybind11
	$(CXX)  $(CXXFLAGS) -I./ -I$(NUMPY_INC_FLAG) $(SRC) -o $@



.PHONY: clean
clean:
	rm -rf $(LIBS) $(executable) __pycache__ .pytest* *.so