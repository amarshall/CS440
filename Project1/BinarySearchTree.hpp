#ifndef JAM_BinarySearchTree_MyClass_HPP
#define JAM_BinarySearchTree_MyClass_HPP

struct MyClass {
  double num;
};

typedef struct Link_ {
  Link_* previous;
  Link_* next;
} Link;

typedef struct Node_ {
  Link link;
  Node_* backReference;
  Node_* left;
  Node_* right;
} Node;

typedef struct BinarySearchTree_MyClass_Iterator_ {
  MyClass* (*inc)(BinarySearchTree_MyClass_Iterator_*);
  MyClass* (*dec)(BinarySearchTree_MyClass_Iterator_*);
  MyClass (*deref)(BinarySearchTree_MyClass_Iterator_*);
} BinarySearchTree_MyClass_Iterator;

typedef struct BinarySearchTree_MyClass_ {
  Node* root;
  const char* type;
  BinarySearchTree_MyClass_Iterator (*insert)(BinarySearchTree_MyClass_*, MyClass);
  BinarySearchTree_MyClass_Iterator (*begin)(BinarySearchTree_MyClass_*);
  BinarySearchTree_MyClass_Iterator (*end)(BinarySearchTree_MyClass_*);
  bool (*comparator)(const MyClass &o1, const MyClass &o2);
  void (*erase)(BinarySearchTree_MyClass_* bst, BinarySearchTree_MyClass_Iterator iterator);
  void (*delet)(BinarySearchTree_MyClass_* bst);
} BinarySearchTree_MyClass;

BinarySearchTree_MyClass* BinarySearchTree_MyClass_new(bool(*comparator)(const MyClass &o1, const MyClass &o2));

BinarySearchTree_MyClass_Iterator insert(BinarySearchTree_MyClass* bst, MyClass* element);
BinarySearchTree_MyClass_Iterator begin(BinarySearchTree_MyClass* bst);
BinarySearchTree_MyClass_Iterator end(BinarySearchTree_MyClass* bst);
bool BinarySearchTree_MyClass_Iterator_equal(BinarySearchTree_MyClass_Iterator, BinarySearchTree_MyClass_Iterator);

void addLeftNode(Node* parent, MyClass* element);
void addRightNode(Node* parent, MyClass* element);

#endif
