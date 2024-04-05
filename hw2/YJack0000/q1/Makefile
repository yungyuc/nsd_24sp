CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXEC = main

.PHONY: all run check clean

all: $(EXEC)

$(EXEC): main.o line.o
	$(CXX) $(CXXFLAGS) -o $(EXEC) main.o line.o

main.o: main.cpp line.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

line.o: line.cpp line.hpp
	$(CXX) $(CXXFLAGS) -c line.cpp

run: $(EXEC)
	./$(EXEC)

check: $(EXEC)
	./$(EXEC) > result.txt

clean:
	rm -f $(EXEC) main.o line.o
