main: main.o
	g++ main.o -o main
main.o:
	g++ -c main.cpp