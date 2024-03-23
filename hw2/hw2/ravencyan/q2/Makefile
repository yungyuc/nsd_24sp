CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)

SRC = _vector.cpp
TARGET = $(SRC:.cpp=.so)

$(TARGET): $(SRC)
		$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: test clean

test:
		python3 -m pytest

clean:
		rm -f $(TARGET)
		rm -rf __pycache__ .pytest_cache