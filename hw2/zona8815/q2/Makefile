# Makefile for hw2/q2

# =============================================================================
# Requirements: 
# make: build the code
# 		When a source file changes (you can touch it), make needs to pick it up and rebuild
# make test: run the Python-based tests
# make clean: remove all the built and intermediate files
# =============================================================================

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -Wextra -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

# Source files
CC_SRC := vector2D.cpp
EXE_SRC = _vector$(shell python3-config --extension-suffix)
TEST_SRC := test_vector.py

# Default target: build the code to shared library
.PHONY: default
default: clean $(CC_SRC)
	@$(CXX) $(CXXFLAGS) $(shell python3 -m pybind11 --includes) $(CC_SRC) -o $(EXE_SRC)

# Run the Python-based tests
.PHONY: test
test:
	@python3 -m pytest

# Remove all the built and intermediate files
.PHONY: clean
clean:
	@-rm -f *.so $(EXE_SRC)
	@-rm -rf __pycache__ .pytest*

# When source files change, make should pick them up and rebuild
.PHONY: $(CC_SRC) $(TEST_SRC)
$(CC_SRC): 
$(TEST_SRC): 

