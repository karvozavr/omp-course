all: build binaries

build: 
	mkdir build

binaries: build/task01 build/task02 build/task03 build/task04

build/%: src/%.cpp
	g++ -std=c++17 -fopenmp -o $@ $< 

%PHONY: clean
clean: 
	rm -rf build

