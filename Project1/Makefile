CC=g++ -Wall

all: Person.o BinarySearchTree.o test.cpp
	$(CC) Person.o BinarySearchTree.o test.cpp

internal: Person.o main.cpp
	$(CC) Person.o main.cpp

Person.o: Person.cpp Person.hpp
	$(CC) -c Person.cpp

Binarysearchtree.o: BinarySearchTree.cpp BinarySearchTree.hpp
	$(CC) -c BinarySearchTree.cpp

clean:
	rm -f *.out *.o core
