CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --cflags) $(shell python3-config --ldflags)
TARGET = _vector.so
SOURCE = _vector.cpp
all: $(TARGET)
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -shared -fPIC $^ -o $@

test: all
	python3 -m pytest -v

clean:
	rm -rf $(TARGET) __pycache__ .pytest_cache *.so _vector
.PHONY: test clean