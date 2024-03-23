CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes)

# Update the include path based on your system's Python and pybind11 installation
INCLUDE_PATH = -I/opt/homebrew/include -I/opt/homebrew/include/python3.12 -I/opt/homebrew/lib/python3.12/site-packages/pybind11/include

LDFLAGS = $(shell python3-config --ldflags) -undefined dynamic_lookup
TARGET = _vector$(shell python3-config --extension-suffix)

all: $(TARGET)

$(TARGET): pybind_wrapper.cpp _vector.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) $(LDFLAGS) $^ -o $@

test:
	pytest

clean:
	rm -f $(TARGET)
