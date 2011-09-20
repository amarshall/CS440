#include "BinarySearchTree.hpp"
#include <stdlib.h>
#include <stdio.h>

BinarySearchTree_MyClass* BinarySearchTree_MyClass_new(bool(*comparator)(const MyClass &o1, const MyClass &o2)) {
  BinarySearchTree_MyClass* bst = (BinarySearchTree_MyClass*) malloc(sizeof(BinarySearchTree_MyClass));
  Node* sentinel = (Node*) malloc(sizeof(Node));
  sentinel->link.sentinel = true;
  sentinel->link.next = &sentinel->link;
  sentinel->link.previous = &sentinel->link;
  bst->sentinel = sentinel;
  bst->root = sentinel;
  bst->type = "MyClass";
  bst->comparator = comparator;
  bst->insert = &insert;
  bst->delet = &delet;
  bst->erase = &erase;
  bst->begin = &begin;
  bst->end = &end;
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
  node->link.sentinel = false;
  return node;
}

BinarySearchTree_MyClass_Iterator insert(BinarySearchTree_MyClass* bst, MyClass element) {
  Node* newNode = Node_new(element);
  if(bst->root->link.sentinel) {
    newNode->link.previous = (Link*)bst->sentinel;
    newNode->link.next = (Link*)bst->sentinel;
    ((Link*)bst->sentinel)->previous = &newNode->link;
    ((Link*)bst->sentinel)->next = &newNode->link;
    bst->root = newNode;
  } else {
    Node* node = bst->root;
    while(true) {
      if(BinarySearchTree_MyClass_Iterator_equal(Iterator_new(bst, &node->link), Iterator_new(bst, &newNode->link))) {
        free(newNode);
        return Iterator_new(bst, (Link*)bst->sentinel);
      }
      if(bst->comparator(element, node->element)) {
        if(node->left == NULL) {
          addLeftNode(bst, node, newNode);
          break;
        }
        node = node->left;
      } else {
        if(node->right == NULL) {
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

void delet(BinarySearchTree_MyClass* bst) {
  for(BinarySearchTree_MyClass_Iterator iterator = bst->begin(bst);
      !BinarySearchTree_MyClass_Iterator_equal(iterator, bst->end(bst));
      iterator.inc(&iterator)) {
    free((Node*)iterator.link);
  }
  free(bst->sentinel);
  free(bst);
}

void erase(BinarySearchTree_MyClass* bst, BinarySearchTree_MyClass_Iterator iterator) {
  Node* node = (Node*)iterator.link;
  Node* replacement = NULL;

  if(node->left == NULL && node->right == NULL) {
    node->backReference = NULL;
  } else {
    if(node->left != NULL) {
      replacement = node->left;
    } else if(node->right != NULL) {
      replacement = node->right;
    }
    if(node->backReference != NULL) node->backReference = &replacement;
  }

  node->link.previous->next = node->link.next;
  node->link.next->previous = node->link.previous;

  if(bst->root == node) {
    if(replacement == NULL) {
      bst->root = (Node*)bst->sentinel;
    } else {
      bst->root = replacement;
    }
  }

  free(node);
}

BinarySearchTree_MyClass_Iterator begin(BinarySearchTree_MyClass* bst) {
  return Iterator_new(bst, ((Link*)bst->sentinel)->next);
}

BinarySearchTree_MyClass_Iterator end(BinarySearchTree_MyClass* bst) {
  return Iterator_new(bst, (Link*)bst->sentinel);
}

bool BinarySearchTree_MyClass_Iterator_equal(BinarySearchTree_MyClass_Iterator it1, BinarySearchTree_MyClass_Iterator it2) {
  if(it1.link->sentinel && it2.link->sentinel) {
    return true;
  } else if (it1.link->sentinel || it2.link->sentinel) {
    return false;
  } else {
    return !it1.comparator(it1.deref(&it1), it2.deref(&it2)) && !it2.comparator(it2.deref(&it2), it1.deref(&it1));
  }
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
  // printf("Inserting left\n");
  parent->left = newNode;
  newNode->backReference = &parent->left;
  newNode->link.previous = parent->link.previous;
  newNode->link.next = &parent->link;
  parent->link.previous->next = &newNode->link;
  parent->link.previous = &newNode->link;
  // printf("Current: %3.1f | ", newNode->element.num);
  // printf("Previous: %3.1f %d | ", ((Node*)newNode->link.previous)->element.num, newNode->link.next->sentinel);
  // printf("Next: %3.1f %d | ", ((Node*)newNode->link.next)->element.num, newNode->link.next->sentinel);
  // printf("Prev->cur: %3.1f | ", ((Node*)newNode->link.previous->next)->element.num);
  // printf("Next->cur: %3.1f\n", ((Node*)newNode->link.next->previous)->element.num);
}

void addRightNode(BinarySearchTree_MyClass* bst, Node* parent, Node* newNode) {
  // printf("Inserting right\n");
  parent->right = newNode;
  newNode->backReference = &parent->right;
  newNode->link.previous = &parent->link;
  newNode->link.next = parent->link.next;
  parent->link.next->previous = &newNode->link;
  parent->link.next = &newNode->link;
  // printf("Current: %3.1f | ", newNode->element.num);
  // printf("Previous: %3.1f %d | ", ((Node*)newNode->link.previous)->element.num, newNode->link.next->sentinel);
  // printf("Next: %3.1f %d | ", ((Node*)newNode->link.next)->element.num, newNode->link.next->sentinel);
  // printf("Prev->cur: %3.1f | ", ((Node*)newNode->link.previous->next)->element.num);
  // printf("Next->cur: %3.1f\n", ((Node*)newNode->link.next->previous)->element.num);
}
