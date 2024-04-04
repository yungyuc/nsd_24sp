CXX = g++
CXXFLAGS = -Wall -Wextra

SRC = main.cpp line.cpp
OBJ = $(SRC:.cpp=.o)
EXE = main

OUTPUT_FILE = result.txt

.PHONY: run check clean
default: run

run: $(EXE)
	./$(EXE)

check: $(EXE)
	./$(EXE) > $(OUTPUT_FILE)

clean:
	rm -f $(OBJ) $(EXE) $(OUTPUT_FILE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@