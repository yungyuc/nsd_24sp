# make, make test, make clean
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -O3 -lm

all: 
	$(CXX) $(CXXFLAGS) -fPIC `python3 -m pybind11 --includes` _vector.cpp -shared -o _vector`python3-config --extension-suffix`

test: 
	python3 -m pytest
clean:
	rm -f *.so