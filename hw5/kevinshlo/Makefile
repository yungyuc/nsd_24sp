INC := ./matrix.hpp 
SRC := ../mod.cpp ./matrix.cpp

CXX_FLAGS := -std=c++17 -O3 -shared -fPIC
CXX_FLAGS += `python3-config --includes --ldflags`
CXX_FLAGS += `python3 -m pybind11 --includes`
# CXX_FLAGS += -I$(shell python3 -c "import numpy; print(numpy.get_include())")

mkl: $(INC) $(SRC)
	python setup.py -q build_ext --inplace

openblas: $(INC) $(SRC)
	pip install pybind11
	g++ $(CXX_FLAGS) -lopenblas -I./ $(SRC) -o _matrix.so

clean:
	rm -rf build __pycache__ .pytest_cache
	rm -f _matrix*.so
