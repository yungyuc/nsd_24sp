CXX = g++
CXXFLAGS = -Wall -g

SOURCES = main.cpp line.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = linemain

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(EXECUTABLE)
	./$(EXECUTABLE)

check: $(EXECUTABLE)
	./$(EXECUTABLE) > result.txt

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) result.txt

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@