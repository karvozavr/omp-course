all: build binaries

build: 
	mkdir build

binaries: build/task01 build/task02 build/task03

build/%: src/%.cpp
	g++ -std=c++20 -fopenmp -o $@ $< 

%PHONY: clean
clean: 
	rm -rf build

