# Makefile for hw2/q1

# =============================================================================
# Requirements: 
# make: build the code
# 		When a source file changes (you can touch it), make needs to pick it up and rebuild
# make run: produce the correct terminal output, without crashing
# make check: redirect the terminal output to a file result.txt
# make clean: remove all the built and intermediate files
# =============================================================================

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = STL_container.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = STL_container

# Default target: build the code
.PHONY: default
default: $(EXEC)

# Build the executable
$(EXEC): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): $(SRCS)

# Run the executable, produce correct terminal output
.PHONY: run
run: $(EXEC)
	@./$(EXEC)

# Redirect terminal output to result.txt
.PHONY: check
check: $(EXEC)
	@./$(EXEC) > result.txt

# Remove all built and intermediate files
.PHONY: clean
clean:
	@-rm -f $(OBJS) $(EXEC) result.txt

