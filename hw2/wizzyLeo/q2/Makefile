CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(shell /usr/bin/python3 -m pybind11 --includes)
LDFLAGS = $(shell /usr/bin/python3-config --ldflags)
TARGET = _vector$(shell /usr/bin/python3-config --extension-suffix)

all: $(TARGET)

$(TARGET): pybind_wrapper.cpp _vector.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

test:
	pytest

clean:
	rm -f $(TARGET) *.so *.pyc
	rm -rf __pycache__ .pytest_cache
