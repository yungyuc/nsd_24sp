CXX=g++
CXXFLAGS=-std=c++17 -Wall -I/opt/homebrew/include/pybind11
SRC=main.cpp line.cpp

line.o: line.cpp line.hpp
	$(CXX) $(CXXFLAGS) -c line.cpp
main.o: main.cpp line.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

OBJ=$(SRC:.cpp=.o)
EXEC=main

# 如果你有使用 pybind11 的動態綁定，並需要鏈接Python庫或其他庫，也可以在這裡指定
# LDFLAGS=-L/your/library/path -lyour_library

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC) result.txt

run: all
	./$(EXEC)

check: $(EXEC)
	./$(EXEC) > result.txt

.PHONY: all clean run check
