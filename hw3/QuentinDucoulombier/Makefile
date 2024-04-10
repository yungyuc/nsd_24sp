# Name of the executable
PROG := exe

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++11
# Include MKL headers and link flags. Adjust these paths according to your MKL installation.
MKLROOT := /opt/intel/oneapi/mkl/latest
CXXFLAGS += -I$(MKLROOT)/include
LDFLAGS := -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

# Source files and object files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Targets
all: $(PROG)

# Linking
$(PROG): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Run the PROG
run: $(PROG)
	./$(PROG)

# Check the PROG
check: $(PROG)
	./$(PROG) > result.txt

# Clean the directory
clean:
	rm -f $(PROG) $(OBJECTS) result.txt

# Phony targets
.PHONY: all run check clean
