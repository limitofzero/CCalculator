CC=g++
CFLAGS=-std=c++11

all: Test

Test: CalculatorTest.o libUnitTest++.a calculator.o
	$(CC) $(CFLAGS) CalculatorTest.o calculator.o -L. -lUnitTest++ -o Test
CalculatorTest.o: CalculatorTest.cpp
	$(CC) $(CFLAGS) -c CalculatorTest.cpp
calculator.o: ../calculator.cpp
	$(CC) $(CFLAGS) -c ../calculator.cpp
	cp ../calculator.o ./
	

