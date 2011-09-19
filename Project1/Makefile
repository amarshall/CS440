CC=g++ -Wall

all: Person.o BinarySearchTree.o test.cpp
	$(CC) Person.o BinarySearchTree.o test.cpp

Person.o: Person.cpp Person.hpp
	$(CC) -c Person.cpp

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.hpp
	$(CC) -c BinarySearchTree.cpp

clean:
	rm -f *.out *.o core
