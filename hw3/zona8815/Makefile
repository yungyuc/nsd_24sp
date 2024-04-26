# Makefile for hw3

# =========================================
# Requirements: 
# make / maek test: build the code and run the tests
# make clean: remove all
# =========================================

CC_SRC        = matrix.cpp
EXE_SRC       = _matrix$(shell python3-config --extension-suffix)
TEST_SRC      = test_matrix.py
PERFORM_SRC   = performance.py

CXX           = g++
CXX_FLAGS     = -std=c++17 -O3 -Wall -Wextra -shared -fPIC -m64 

BIND_FLAGS    = $(shell python3 -m pybind11 --includes)
LD_FLAGS      = -lblas 
LD_FLAGS     += $(shell python3-config --includes --ldflags)

MKL_COMPILER  = -I"${MKLROOT}/include"
MKL_LINKS     = -L${MKLROOT}/lib/intel64 -lmkl_rt -Wl,--no-as-needed -lpthread -lm -ldl

MKL_EXT         = $(MKL_COMPILER) $(MKL_LINKS) 

.PHONY : test
test: clean $(CC_SRC)
	$(CXX) $(CXX_FLAGS) $(MKL_EXT) $(BIND_FLAGS) $(CC_SRC) -o $(EXE_SRC) $(LD_FLAGS)
	@echo ""
	@echo " ***     COMPILE COMPLETED     *** "
	@echo " ***       TESTING START       *** "
	@echo ""
	-python3 -m pytest $(TEST_SRC)
	python3 $(PERFORM_SRC)

.PHONY : clean
clean :
	-rm -f *.so $(EXE_SRC)
	-rm -rf __pycache__ .pytest*

.PHONY : $(CC_SRC) $(TEST_SRC) $(PERFORM_SRC)
$(CC_SRC):
$(TEST_SRC):
$(PERFORM_SRC):
