CXX ?= g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: demo test
demo: src/main.cpp src/simplify.hpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o demo
test: tests/test.cpp src/simplify.hpp
	$(CXX) $(CXXFLAGS) tests/test.cpp -o run_tests && ./run_tests
clean:
	rm -f demo run_tests out.svg
