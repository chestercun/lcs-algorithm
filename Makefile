all: main.o
	g++ -o ex1 main.o
main.0: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
