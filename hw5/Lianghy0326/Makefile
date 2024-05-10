SRC = ../mod.cpp ./matrix.cpp
INC = ./matrix.hpp  

CXX = clang++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC -lblas `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LIB_TARGET = _matrix.so

$(LIB_TARGET): $(INC) $(SRC)
    pip install pybind11
    $(CXX) $(CXXFLAGS) $(SRC) -o $@

.PHONY: test
test: $(LIB_TARGET)
    env PYTHONPATH=".:$PYTHONPATH" python3 -m pytest -v

.PHONY: clean
clean:
    rm -rf $(LIB_TARGET) __pycache__ .pytest* *.so
