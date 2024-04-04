CXX = g++ # compiler

CXXFLAGS = -std=c++14 # compiler flags

sources = main.cpp line.cpp # source files
results = result.txt # result files
objects = $(sources:.cpp=.o) # object files
executable = main # executable name

all: $(executable) # build executable

$(executable): $(objects) # link object files to executable
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp # compile source files to object files
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(executable) # run the executable
	./$(executable)

check: $(executable) # run the executable with valgrind
	./$(executable) > $(results)

clean: # remove object files and executable
	rm -rf $(objects) $(executable) $(results) 


