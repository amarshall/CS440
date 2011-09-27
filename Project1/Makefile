CC=g++ -Wall -g

all: Person.o test.o
	$(CC) Person.o test.o

test.o: test.cpp
	$(CC) -c test.cpp

Person.o: Person.cpp Person.hpp
	$(CC) -c Person.cpp

clean:
	rm -f *.out *.o core
