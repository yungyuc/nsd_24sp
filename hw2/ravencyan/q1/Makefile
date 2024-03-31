CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRC = main.cpp line.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Make all .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Generate executable file
$(EXEC): $(OBJ)
		$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean run check

clean:
		rm -f $(OBJ) $(EXEC) result.txt

run: $(EXEC)
		./$(EXEC)

check: $(EXEC)
		./$(EXEC) > result.txt