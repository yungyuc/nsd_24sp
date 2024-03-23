CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(shell python3-config --includes)
LDFLAGS = $(shell python3-config --ldflags)

TARGET = _vector$(shell python3-config --extension-suffix)
SRC = pybind_wrapper.cpp _vector.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

test:
	pytest

clean:
	rm -f $(TARGET) *.so *.pyc
	rm -rf __pycache__ .pytest_cache
