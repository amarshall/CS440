#ifndef JAM_BinarySearchTree_MyClass_HPP
#define JAM_BinarySearchTree_MyClass_HPP

struct MyClass {
  double num;
};

typedef struct Link_ {
  Link_* previous;
  Link_* next;
  bool sentinel;
} Link;

typedef struct Node_ {
  Link link;
  Node_** backReference;
  Node_* left;
  Node_* right;
  MyClass element;
} Node;

typedef struct BinarySearchTree_MyClass_Iterator_ {
  Link* link;
  void (*inc)(BinarySearchTree_MyClass_Iterator_*);
  void (*dec)(BinarySearchTree_MyClass_Iterator_*);
  MyClass (*deref)(BinarySearchTree_MyClass_Iterator_*);
  bool (*comparator)(const MyClass &o1, const MyClass &o2);
} BinarySearchTree_MyClass_Iterator;

typedef struct BinarySearchTree_MyClass_ {
  Node* root;
  Node* sentinel;
  const char* type;
  BinarySearchTree_MyClass_Iterator (*insert)(BinarySearchTree_MyClass_*, MyClass);
  void (*erase)(BinarySearchTree_MyClass_*, BinarySearchTree_MyClass_Iterator);
  BinarySearchTree_MyClass_Iterator (*begin)(BinarySearchTree_MyClass_*);
  BinarySearchTree_MyClass_Iterator (*end)(BinarySearchTree_MyClass_*);
  bool (*comparator)(const MyClass &o1, const MyClass &o2);
  void (*delet)(BinarySearchTree_MyClass_* bst);
} BinarySearchTree_MyClass;

BinarySearchTree_MyClass* BinarySearchTree_MyClass_new(bool(*comparator)(const MyClass &o1, const MyClass &o2));
Node* Node_new(MyClass element);
BinarySearchTree_MyClass_Iterator Iterator_new(BinarySearchTree_MyClass* bst, Link* link);

void delet(BinarySearchTree_MyClass*);

BinarySearchTree_MyClass_Iterator insert(BinarySearchTree_MyClass* bst, MyClass element);
void erase(BinarySearchTree_MyClass* bst, BinarySearchTree_MyClass_Iterator iterator);
BinarySearchTree_MyClass_Iterator begin(BinarySearchTree_MyClass* bst);
BinarySearchTree_MyClass_Iterator end(BinarySearchTree_MyClass* bst);

bool BinarySearchTree_MyClass_Iterator_equal(BinarySearchTree_MyClass_Iterator o1, BinarySearchTree_MyClass_Iterator o2);
void Iterator_inc(BinarySearchTree_MyClass_Iterator* iterator);
void Iterator_dec(BinarySearchTree_MyClass_Iterator* iterator);
MyClass Iterator_dereference(BinarySearchTree_MyClass_Iterator* iterator);

void addLeftNode(BinarySearchTree_MyClass* bst, Node* parent, Node* newNode);
void addRightNode(BinarySearchTree_MyClass* bst, Node* parent, Node* newNode);

#endif
