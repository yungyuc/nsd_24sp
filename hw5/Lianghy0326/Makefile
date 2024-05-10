SRC = ../mod.cpp matrix.cpp
CXX = clang++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC -lblas `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LIB_TARGET = _matrix.so
MKLROOT=/usr/lib/x86_64-linux-gnu

$(LIB_TARGET): $(SRC)
	pip install pybind11
	$(CXX)  $(CXXFLAGS) $(shell python3 -m pybind11 --includes) $(SRC) -o $@


.PHONY: test
test: $(LIB_TARGET)
    env PYTHONPATH=".:$PYTHONPATH" python3 -m pytest -v

.PHONY: clean
clean:
	rm -rf $(LIB_TARGET) $(executable) __pycache__ .pytest* *.so