# make, make test, make clean
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -lm $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
TARGET = _vector$(shell python3-config --extension-suffix) 

all: 
	$(CXX) $(CXXFLAGS) -fPIC _vector.cpp -shared -o $(TARGET)

test: 
	python3 -m pytest
clean:
	rm -rf $(TARGET) *.pyc __pycache__ .pytest_cache