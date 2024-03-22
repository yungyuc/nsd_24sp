# Makefile for hw2/q2

# =============================================================================
# Requirements: 
# make: build the code
# 		When a source file changes (you can touch it), make needs to pick it up and rebuild
# make test: run the Python-based tests
# make clean: remove all the built and intermediate files
# =============================================================================

# Source files
CC_SRC := vector2D.cpp
SET_SRC := setup.py
TEST_SRC := test_vector.py

# Default target: build the code
.PHONY: default
default: clean $(SET_SRC)
	@python3 $(SET_SRC) build_ext --inplace

# Run the Python-based tests
.PHONY: test
test:
	@pytest

# Remove all the built and intermediate files
.PHONY: clean
clean:
	@-rm -f *.so
	@-rm -rf __pycache__ .pytest_cache angle.egg-info build

# When source files change, make should pick them up and rebuild
.PHONY: $(CC_SRC) $(SET_SRC) $(TEST_SRC)
$(CC_SRC): 
$(SET_SRC): 
$(TEST_SRC): 

