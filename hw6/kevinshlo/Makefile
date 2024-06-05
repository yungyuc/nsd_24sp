NAME := _matrix.so
INC := ./matrix.hpp 
SRC := ./mod.cpp ./matrix.cpp

CXX_FLAGS := -std=c++17 -O3 -shared -fPIC -I./
CXX_FLAGS += `python3-config --includes --ldflags`
CXX_FLAGS += `python3 -m pybind11 --includes`
CXX_FLAGS += -I$(shell python3 -c "import numpy; print(numpy.get_include())")
MKL_FLAGS := -DMKL
MKL_FLAGS += -m64 -Wl,--no-as-needed
MKL_FLAGS += -lmkl_rt -lpthread -lm -ldl -L${MKLROOT}/lib/intel64
MKL_FLAGS += -I"${MKLROOT}/include"

mkl: $(INC) $(SRC)
	pip install pybind11
	g++ $(SRC) -o $(NAME) $(CXX_FLAGS) $(MKL_FLAGS)

openblas: $(INC) $(SRC)
#	command -v apt-get > /dev/null 2>&1 && sudo apt-get -qy install libopenblas-dev || sudo dnf -qy install blas-devel openblas-devel
	pip install pybind11
	g++ $(SRC) -o $(NAME) $(CXX_FLAGS) -lopenblas

clean:
	rm -rf build __pycache__ .pytest_cache
	rm -f $(NAME)
