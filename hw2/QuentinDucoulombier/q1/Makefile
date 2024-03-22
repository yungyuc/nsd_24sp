# Name of the executable
PROG := exe

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++11

# Source files and object files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Targets
all: $(PROG)

# Linking
$(PROG): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

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
