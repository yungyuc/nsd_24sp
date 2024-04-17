# CXX = g++
# CXXFLAGS = -std=c++11 -O3 -Wall -fPIC -shared -m64 $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
# LDFLAGS = -lblas -lmkl_rt

# PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
# PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
# PYTHON_SUF = $(shell python3-config --extension-suffix)

# MKL_INC = /opt/intel/oneapi/mkl/2024.1/include

# SRC = matrix.cpp main.cpp
# PERF_SRC = performance.py
# PERF_OUTPUT = performance.txt
# PYTEST = test_matrix.py
# LIBS = ./_matrix$(PYTHON_SUF)

# .PHONY: test clean

# test: $(LIBS) $(PYTEST)
# 	python3 -m pytest -v



# perf: $(LIBS)
# 	rm -f $(PERF_OUTPUT)
# 	python3 $(PERF_SRC)

# $(LIBS): $(SRC)
# 	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

# clean:
# 	rm -f $(LIBS)
# 	rm -f matrixmain _matrix$(shell $(PYTHON)-config --extension-suffix) *.o
# 	find . -type d -name __pycache__ -exec rm -r {} +
# 	find . -type d -name .pytest_cache -exec rm -r {} +
# 	find . -type f -name '*.pyc' -delete

CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -fPIC -shared -m64 $(PYBIND_INC_FLAGS) $(PYTHON_LIB_FLAGS)
LDFLAGS = -lblas -lmkl_rt

PYBIND_INC_FLAGS = $(shell python3 -m pybind11 --includes)
PYTHON_LIB_FLAGS = $(shell python3-config --includes --ldflags)
PYTHON_SUF = $(shell python3-config --extension-suffix)

MKL_INC = /opt/intel/oneapi/mkl/2024.1/include

SRC = matrix.cpp main.cpp
PERF_SRC = performance.py
PERF_OUTPUT = performance.txt
PYTEST = test_matrix.py
LIBS = ./_matrix$(PYTHON_SUF)
EXEC = matrixmain

.PHONY: test clean run

test: $(LIBS) $(PYTEST)
	python3 -m pytest -v

run: $(EXEC)
	./$(EXEC)

perf: $(LIBS)
	rm -f $(PERF_OUTPUT)
	python3 $(PERF_SRC)

$(LIBS): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKL_INC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(LIBS) $(EXEC)
	rm -f _matrix$(shell $(PYTHON)-config --extension-suffix) *.o
	find . -type d -name __pycache__ -exec rm -r {} +
	find . -type d -name .pytest_cache -exec rm -r {} +
	find . -type f -name '*.pyc' -delete