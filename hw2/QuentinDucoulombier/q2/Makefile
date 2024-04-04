CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall -shared -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)
TARGET = _vector$(shell python3-config --extension-suffix)
SRC = _vector.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

test:
	python3 -m pytest

clean:
	rm -f $(TARGET) __pycache__ .pytest_cache -r *.so *.pyc
