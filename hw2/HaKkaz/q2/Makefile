CXX = g++
CXXFLAGS = -shared -std=c++14 -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --cflags) $(shell python3-config --ldflags)
LIB_TARGET = _vector.so

all: $(LIB_TARGET)
$(LIB_TARGET): _vector.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: test clean

test: all
	python3 -m pytest -v

clean:
	rm -f *.o *.so
	rm -rf .pytest_cache/ __pycache__/