SRC = ../mod.cpp ./matrix.cpp
INC = ./matrix.hpp  

CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LDFLAGS = -lblas -lm  # Ensure linking against the math library and BLAS

LIB_TARGET = _matrix.so

$(LIB_TARGET): $(INC) $(SRC)
	pip install pybind11
	$(CXX) $(CXXFLAGS) -I./ $(SRC) -o $@ $(LDFLAGS)  # Include LDFLAGS here

.PHONY: test
test: $(LIB_TARGET)
	env PYTHONPATH=".:$PYTHONPATH" python3 -m pytest -v

.PHONY: clean
clean:
	rm -rf $(LIB_TARGET) __pycache__ .pytest* *.so
