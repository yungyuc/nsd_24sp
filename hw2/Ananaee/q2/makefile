MODULE_NAME = _vector

CXX = c++

CXXFLAGS = -O3 -Wall -std=c++11 -fPIC -I/home/cytech/anaconda3/include/python3.11 -I/home/cytech/anaconda3/lib/python3.11/site-packages/pybind11/include

LDLIBS = `python3-config --extension-suffix`

SOURCES = _vector.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(MODULE_NAME)


$(MODULE_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o $(MODULE_NAME)$(LDLIBS) $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


test: $(MODULE_NAME)
	python3 -m pytest test_vector.py

clean:
	rm -f $(OBJECTS) $(MODULE_NAME)$(LDLIBS) vector.cpython-311-x86_64-linux-gnu.so

