CC=g++ -Wall

all: Person.o Binarysearchtree.o test.cpp
	$(CC) Person.o Binarysearchtree.o test.cpp

internal: Person.o main.cpp
	$(CC) Person.o main.cpp

Person.o: person.cpp person.hpp
	$(CC) -c Person.cpp

Binarysearchtree.o: Binarysearchtree.cpp Binarysearchtree.hpp
	$(CC) -c Binarysearchtree.cpp

clean:
	rm -f *.out *.o core
