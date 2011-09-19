#include "BinarySearchTree.hpp"
#include <stdlib.h>

BinarySearchTree_MyClass* BinarySearchTree_MyClass_new(bool(*comparator)(const MyClass &o1, const MyClass &o2)) {
  BinarySearchTree_MyClass* bst = (BinarySearchTree_MyClass*) malloc(sizeof(BinarySearchTree_MyClass));
  bst->type = "MyClass";
  bst->comparator = comparator;
  return bst;
}

BinarySearchTree_MyClass_Iterator insert(BinarySearchTree_MyClass* bst, MyClass* element) {

}

BinarySearchTree_MyClass_Iterator begin(BinarySearchTree_MyClass* bst) {

}

BinarySearchTree_MyClass_Iterator end(BinarySearchTree_MyClass* bst) {

}

bool BinarySearchTree_MyClass_Iterator_equal(BinarySearchTree_MyClass_Iterator it1, BinarySearchTree_MyClass_Iterator it2) {

}

void addLeftNode(Node* parent, MyClass* element) {

}

void addRightNode(Node* parent, MyClass* element) {

}
