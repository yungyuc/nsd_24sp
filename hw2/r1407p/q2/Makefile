sources = _vector.cpp
executable = _vector$(shell python3-config --extension-suffix)

CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

all: $(sources)
	$(CXX) $(CXXFLAGS) $(shell python3 -m pybind11 --includes) $(sources) -o $(executable)

test:
	python3 -m pytest

clean:
	rm -rf $(executable) __pycache__ .pytest* *.so