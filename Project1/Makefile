CC=g++ -Wall -g

all: Person.o BinarySearchTree.o test.o
	$(CC) Person.o BinarySearchTree.o test.o

test.o: test.cpp
	$(CC) -c test.cpp

Person.o: Person.cpp Person.hpp
	$(CC) -c Person.cpp

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.hpp
	$(CC) -c BinarySearchTree.cpp

clean:
	rm -f *.out *.o core
