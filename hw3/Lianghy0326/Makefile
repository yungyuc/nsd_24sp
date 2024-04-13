sources = _matrix.cpp
CXX = clang++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC -lblas `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LIB_TARGET = _matrix.so
MKLROOT=/usr/lib/x86_64-linux-gnu



LDFLAGS=${MKLROOT}/libmkl_def.so \
        ${MKLROOT}/libmkl_avx2.so \
        ${MKLROOT}/libmkl_core.so \
        ${MKLROOT}/libmkl_intel_lp64.so \
        ${MKLROOT}/libmkl_sequential.so \
        -lpthread -lm -ldl \
        -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64 
all: $(LIB_TARGET)


$(LIB_TARGET): $(sources)
	$(CXX)  $(CXXFLAGS) $(shell python3 -m pybind11 --includes) $(sources) -o $@


.PHONY: test
test: $(LIB_TARGET)
    env PYTHONPATH=".:$PYTHONPATH" python3 -m pytest -v

.PHONY: clean
clean:
	rm -rf $(LIB_TARGET) $(executable) __pycache__ .pytest* *.so