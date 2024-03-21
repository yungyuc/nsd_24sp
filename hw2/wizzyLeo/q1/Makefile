CXX = g++
CXXFLAGS = -std=c++11 -Wall

EXEC = line_program
SOURCES = main.cpp Line.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)

run: $(EXEC)
	./$(EXEC)

check: $(EXEC)
	./$(EXEC) > result.txt