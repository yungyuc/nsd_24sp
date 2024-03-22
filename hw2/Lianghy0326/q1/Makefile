CXX=g++
CXXFLAGS=-std=c++17 -Wall
SRC=main.cpp line.cpp
OBJ=$(SRC:.cpp=.o)
EXEC=main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC) result.txt

run: all
	./$(EXEC)

check: $(EXEC)
	./$(EXEC) > result.txt

.PHONY: all clean run check
