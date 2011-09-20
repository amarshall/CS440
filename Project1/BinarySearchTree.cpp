#include "BinarySearchTree.hpp"
#include <stdlib.h>

BinarySearchTree_MyClass* BinarySearchTree_MyClass_new(bool(*comparator)(const MyClass &o1, const MyClass &o2)) {
  BinarySearchTree_MyClass* bst = (BinarySearchTree_MyClass*) malloc(sizeof(BinarySearchTree_MyClass));
  bst->type = "MyClass";
  bst->comparator = comparator;
  return bst;
}

Node* Node_new(MyClass element) {
  Node* node = (Node*) malloc(sizeof(Node));
  node->element = element;
  node->backReference = NULL;
  node->left = NULL;
  node->right = NULL;
  node->link.previous = NULL;
  node->link.next = NULL;
  return node;
}

BinarySearchTree_MyClass_Iterator insert(BinarySearchTree_MyClass* bst, MyClass element) {
  Node* newNode = Node_new(element);
  if(bst->root == NULL) {
    addLeftNode(bst, newNode, bst->sentinel);
    addRightNode(bst, newNode, bst->sentinel);
    bst->root = newNode;
  } else {
    Node* node = bst->root;
    while(true) {
      if(bst->comparator(element, node->element)) {
        if(node->left == NULL) {
          addLeftNode(bst, node, newNode);
          break;
        }
        node = node->left;
      } else {
        if(node->left == NULL) {
          addRightNode(bst, node, newNode);
          break;
        }
        node = node->right;
      }
    }
  }

  return Iterator_new(bst, &newNode->link);
}

BinarySearchTree_MyClass_Iterator Iterator_new(BinarySearchTree_MyClass* bst, Link* link) {
  BinarySearchTree_MyClass_Iterator iterator;
  iterator.link = link;
  iterator.inc = &Iterator_inc;
  iterator.dec = &Iterator_dec;
  iterator.deref = &Iterator_dereference;
  iterator.comparator = bst->comparator;
  return iterator;
}

BinarySearchTree_MyClass_Iterator begin(BinarySearchTree_MyClass* bst) {
  return Iterator_new(bst, &bst->root->link);
}

BinarySearchTree_MyClass_Iterator end(BinarySearchTree_MyClass* bst) {
  return Iterator_new(bst, &bst->sentinel->link);
}

bool BinarySearchTree_MyClass_Iterator_equal(BinarySearchTree_MyClass_Iterator it1, BinarySearchTree_MyClass_Iterator it2) {
  return it1.comparator(it1.deref(&it1), it2.deref(&it1));
}

void Iterator_inc(BinarySearchTree_MyClass_Iterator* iterator) {
  iterator->link = iterator->link->next;
}

void Iterator_dec(BinarySearchTree_MyClass_Iterator* iterator) {
  iterator->link = iterator->link->previous;
}

MyClass Iterator_dereference(BinarySearchTree_MyClass_Iterator* iterator) {
  Node* node = (Node*) iterator->link;
  return node->element;
}

void addLeftNode(BinarySearchTree_MyClass* bst, Node* parent, Node* newNode) {
  parent->left = newNode;
  newNode->backReference = &parent->left;
  newNode->link.previous = parent->link.previous;
  newNode->link.next = &parent->link;
  parent->link.previous = &newNode->link;
  if(newNode->link.previous == NULL) {
    bst->first = newNode;
  }
}

void addRightNode(BinarySearchTree_MyClass* bst, Node* parent, Node* newNode) {
  parent->right = newNode;
  newNode->backReference = &parent->right;
  newNode->link.previous = &parent->link;
  newNode->link.next = parent->link.next;
  parent->link.next = &newNode->link;
}
