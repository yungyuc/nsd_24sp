CXX = g++
CXXFLAGS = -Wall -std=c++11
EXEC = line_program
SOURCES = main.cpp Line.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)

run: all
	./$(EXEC)

check: all
	./$(EXEC) > result.txt
