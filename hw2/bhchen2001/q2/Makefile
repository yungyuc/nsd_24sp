CXX = g++
# flags from https://pybind11.readthedocs.io/en/stable/basics.html
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

SRC = _vector.cpp
TARGET = $(SRC:.cpp=.so)

.PHONY: test clean

test: $(TARGET)
	python3 -m pytest -v

clean:
	rm -f $(TARGET)
	rm -rf __pycache__

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(shell python3 -m pybind11 --includes) $(SRC) -o $(TARGET) $(shell python3-config --includes --ldflags)