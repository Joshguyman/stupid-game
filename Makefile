main: build/objs/main.o
	g++ -o build/bin/main build/objs/main.o -lraylib

build/objs/main.o: src/main.cpp
	g++ -c -o build/objs/main.o src/main.cpp
