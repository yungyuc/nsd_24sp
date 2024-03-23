CXX = g++
CXXFLAGS = -std=c++14

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = main

all: $(exe) 

$(exe): $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(obj) $(exe) 

run: $(exe)
	./$(exe)

check: $(exe)
	./$(exe) > result.txt