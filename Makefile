CC=g++

CFLAGS=-std=c++11 -lstdc++

all: calculator

calculator: main.o calculator.o 
	$(CC) $(CFLAGS) main.o calculator.o -o calculator
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
calculator.o: calculator.cpp
	$(CC) $(CFLAGS) -c calculator.cpp
clean:
	rm -rf *.o calculator

