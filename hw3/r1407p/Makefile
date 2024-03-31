sources = _matrix.cpp
PROG_TARGET = matrix_test.py
LIB_TARGET = _matrix.so
CXX = clang++
CXXFLAGS = -std=c++11 -O3 -Wall -shared -fPIC -lblas `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
executable = _matrix$(shell python3-config --extension-suffix)

MKLROOT=/usr/lib/x86_64-linux-gnu
LDFLAGS=${MKLROOT}/libmkl_def.so \
		${MKLROOT}/libmkl_avx2.so \
		${MKLROOT}/libmkl_core.so \
		${MKLROOT}/libmkl_intel_lp64.so \
		${MKLROOT}/libmkl_sequential.so \
		-lpthread -lm -ldl \
	    -lblas -lmkl_rt -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64 

all: $(LIB_TARGET)

$(LIB_TARGET): $(sources)
	pip install pybind11
	$(CXX)  $(CXXFLAGS) $(LDFLAGS) $(shell python3 -m pybind11 --includes) $(sources) -o $(executable)

test: $(LIB_TARGET)
	python3 -m pytest -v

clean:
	rm -rf $(PROG_TARGET) $(LIB_TARGET) $(executable) __pycache__ .pytest* *.so
	