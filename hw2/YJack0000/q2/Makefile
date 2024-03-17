CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC -undefined dynamic_lookup $(shell python3 -m pybind11 --includes) $(shell python3-config --cflags) $(shell python3-config --ldflags)
LIB_TARGET = cvector.so

all: $(LIB_TARGET)
$(LIB_TARGET): cvector.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: test clean

test: all
	python3 -m pytest -v

clean:
	rm -rf .pytest_cache/ __pycache__/
	rm -f *.o *.so
