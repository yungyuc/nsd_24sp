CXX = g++
# flags from https://pybind11.readthedocs.io/en/stable/basics.html
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

SRC = _vector.cpp
TARGET = _vector`python3-config --extension-suffix`

.PHONY: test clean

test: $(TARGET)
	pytest

clean:
	rm -f $(TARGET)
	rm -rf __pycache__

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) `python3 -m pybind11 --includes` $(SRC) -o $(TARGET) `python3-config --includes --ldflags`