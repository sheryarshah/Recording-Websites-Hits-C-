program: main.o
	g++ -o program main.o
main.o: main.cpp header.h class.h
	g++ -c main.cpp
