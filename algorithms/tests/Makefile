all: test


test_files: build
	./run <input.txt >output.txt

test: build
	./run

CXX=g++-mp-4.6
INCLUDES=-I/Users/ignat/Documents/Github/debug_output/
DEFINES=#-DDEBUG_OUTPUT
CXXFLAGS=-fno-optimize-sibling-calls -fno-strict-aliasing -lm -O2 -std=gnu++0x -D DEBUG_OUTPUT

GDBFLAGS=#-ggdb

build:
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) $(INCLUDES) $(DEFINES)  main.cpp -o run

clean:
	rm run
