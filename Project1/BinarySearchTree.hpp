#ifndef BinarySearchTree_DEFINE

typedef struct Link_ {
  Link_* previous;
  Link_* next;
  bool sentinel;
} Link;

#define BinarySearchTree_DEFINE(obj) \
\
typedef struct Node_##obj##_ { \
  Link link; \
  Node_##obj##_** backReference; \
  Node_##obj##_* left; \
  Node_##obj##_* right; \
  obj element; \
} Node_##obj; \
\
typedef struct BinarySearchTree_##obj##_Iterator_ { \
  Link* link; \
  void (*inc)(BinarySearchTree_##obj##_Iterator_*); \
  void (*dec)(BinarySearchTree_##obj##_Iterator_*); \
  obj (*deref)(BinarySearchTree_##obj##_Iterator_*); \
  bool (*comparator)(const obj &o1, const obj &o2); \
} BinarySearchTree_##obj##_Iterator; \
\
typedef struct BinarySearchTree_##obj##_ { \
  Node_##obj* root; \
  Node_##obj* sentinel; \
  char type[sizeof("BinarySearchTree_" #obj)]; \
  BinarySearchTree_##obj##_Iterator (*insert)(BinarySearchTree_##obj##_*, obj); \
  void (*erase)(BinarySearchTree_##obj##_*, BinarySearchTree_##obj##_Iterator); \
  BinarySearchTree_##obj##_Iterator (*begin)(BinarySearchTree_##obj##_*); \
  BinarySearchTree_##obj##_Iterator (*end)(BinarySearchTree_##obj##_*); \
  bool (*comparator)(const obj &o1, const obj &o2); \
  void (*delet)(BinarySearchTree_##obj##_* bst); \
} BinarySearchTree_##obj; \
\
BinarySearchTree_##obj* BinarySearchTree_##obj##_new(bool(*comparator)(const obj &o1, const obj &o2)); \
Node_##obj* Node_##obj##_new(obj element); \
BinarySearchTree_##obj##_Iterator Iterator_##obj##_new(BinarySearchTree_##obj* bst, Link* link); \
\
void BST_##obj##_delet(BinarySearchTree_##obj*); \
\
BinarySearchTree_##obj##_Iterator BST_##obj##_insert(BinarySearchTree_##obj* bst, obj element); \
void BST_##obj##_erase(BinarySearchTree_##obj* bst, BinarySearchTree_##obj##_Iterator iterator); \
BinarySearchTree_##obj##_Iterator BST_##obj##_begin(BinarySearchTree_##obj* bst); \
BinarySearchTree_##obj##_Iterator BST_##obj##_end(BinarySearchTree_##obj* bst); \
\
bool BinarySearchTree_##obj##_Iterator_equal(BinarySearchTree_##obj##_Iterator o1, BinarySearchTree_##obj##_Iterator o2); \
void Iterator_##obj##_inc(BinarySearchTree_##obj##_Iterator* iterator); \
void Iterator_##obj##_dec(BinarySearchTree_##obj##_Iterator* iterator); \
obj Iterator_##obj##_dereference(BinarySearchTree_##obj##_Iterator* iterator); \
\
void BST_##obj##_addLeftNode_##obj(BinarySearchTree_##obj* bst, Node_##obj* parent, Node_##obj* newNode_##obj); \
void BST_##obj##_addRightNode_##obj(BinarySearchTree_##obj* bst, Node_##obj* parent, Node_##obj* newNode_##obj); \
\
\
BinarySearchTree_##obj* BinarySearchTree_##obj##_new(bool(*comparator)(const obj &o1, const obj &o2)) { \
  BinarySearchTree_##obj* bst = (BinarySearchTree_##obj*) malloc(sizeof(BinarySearchTree_##obj)); \
  Node_##obj* sentinel = (Node_##obj*) malloc(sizeof(Node_##obj)); \
  sentinel->link.sentinel = true; \
  sentinel->link.next = &sentinel->link; \
  sentinel->link.previous = &sentinel->link; \
  bst->sentinel = sentinel; \
  bst->root = sentinel; \
  strcpy(bst->type, "BinarySearchTree_" #obj); \
  bst->comparator = comparator; \
  bst->insert = &BST_##obj##_insert; \
  bst->delet = &BST_##obj##_delet; \
  bst->erase = &BST_##obj##_erase; \
  bst->begin = &BST_##obj##_begin; \
  bst->end = &BST_##obj##_end; \
  return bst; \
} \
\
Node_##obj* Node_##obj##_new(obj element) { \
  Node_##obj* node = (Node_##obj*) malloc(sizeof(Node_##obj)); \
  node->element = element; \
  node->backReference = NULL; \
  node->left = NULL; \
  node->right = NULL; \
  node->link.previous = NULL; \
  node->link.next = NULL; \
  node->link.sentinel = false; \
  return node; \
} \
\
BinarySearchTree_##obj##_Iterator BST_##obj##_insert(BinarySearchTree_##obj* bst, obj element) { \
  Node_##obj* newNode = Node_##obj##_new(element); \
  if(bst->root->link.sentinel) { \
    newNode->link.previous = (Link*)bst->sentinel; \
    newNode->link.next = (Link*)bst->sentinel; \
    ((Link*)bst->sentinel)->previous = &newNode->link; \
    ((Link*)bst->sentinel)->next = &newNode->link; \
    bst->root = newNode; \
    newNode->backReference = &bst->root; \
  } else { \
    Node_##obj* node = bst->root; \
    while(true) { \
      if(BinarySearchTree_##obj##_Iterator_equal(Iterator_##obj##_new(bst, &node->link), Iterator_##obj##_new(bst, &newNode->link))) { \
        free(newNode); \
        return Iterator_##obj##_new(bst, (Link*)bst->sentinel); \
      } \
      if(bst->comparator(newNode->element, node->element)) { \
        if(node->left == NULL) { \
          BST_##obj##_addLeftNode_##obj(bst, node, newNode); \
          break; \
        } \
        node = node->left; \
      } else { \
        if(node->right == NULL) { \
          BST_##obj##_addRightNode_##obj(bst, node, newNode); \
          break; \
        } \
        node = node->right; \
      } \
    } \
  } \
\
  return Iterator_##obj##_new(bst, &newNode->link); \
} \
\
BinarySearchTree_##obj##_Iterator Iterator_##obj##_new(BinarySearchTree_##obj* bst, Link* link) { \
  BinarySearchTree_##obj##_Iterator iterator; \
  iterator.link = link; \
  iterator.inc = &Iterator_##obj##_inc; \
  iterator.dec = &Iterator_##obj##_dec; \
  iterator.deref = &Iterator_##obj##_dereference; \
  iterator.comparator = bst->comparator; \
  return iterator; \
} \
\
void BST_##obj##_delet(BinarySearchTree_##obj* bst) { \
  for(BinarySearchTree_##obj##_Iterator iterator = bst->begin(bst); \
      !BinarySearchTree_##obj##_Iterator_equal(iterator, bst->end(bst)); \
      iterator.inc(&iterator)) { \
    free((Node_##obj*)iterator.link); \
  } \
  free(bst->sentinel); \
  free(bst); \
} \
\
void BST_##obj##_erase(BinarySearchTree_##obj* bst, BinarySearchTree_##obj##_Iterator iterator) { \
  Node_##obj* node = (Node_##obj*)iterator.link; \
  Node_##obj* replacement = NULL; \
\
  if(node->left == NULL && node->right == NULL) { \
    *node->backReference = NULL; \
  } else { \
    if(node->left != NULL) { \
      replacement = node->left; \
    } else if(node->right != NULL) { \
      replacement = node->right; \
    } \
    *node->backReference = replacement; \
    *replacement->backReference = NULL; \
  } \
\
  node->link.previous->next = node->link.next; \
  node->link.next->previous = node->link.previous; \
\
  if(bst->root == node) { \
    if(replacement == NULL) { \
      bst->root = (Node_##obj*)bst->sentinel; \
    } else { \
      bst->root = replacement; \
    } \
  } \
\
  free(node); \
} \
\
BinarySearchTree_##obj##_Iterator BST_##obj##_begin(BinarySearchTree_##obj* bst) { \
  return Iterator_##obj##_new(bst, ((Link*)bst->sentinel)->next); \
} \
\
BinarySearchTree_##obj##_Iterator BST_##obj##_end(BinarySearchTree_##obj* bst) { \
  return Iterator_##obj##_new(bst, (Link*)bst->sentinel); \
} \
\
bool BinarySearchTree_##obj##_Iterator_equal(BinarySearchTree_##obj##_Iterator it1, BinarySearchTree_##obj##_Iterator it2) { \
  if(it1.link->sentinel && it2.link->sentinel) { \
    return true; \
  } else if (it1.link->sentinel || it2.link->sentinel) { \
    return false; \
  } else { \
    return !it1.comparator(it1.deref(&it1), it2.deref(&it2)) && !it2.comparator(it2.deref(&it2), it1.deref(&it1)); \
  } \
} \
\
void Iterator_##obj##_inc(BinarySearchTree_##obj##_Iterator* iterator) { \
  iterator->link = iterator->link->next; \
} \
\
void Iterator_##obj##_dec(BinarySearchTree_##obj##_Iterator* iterator) { \
  iterator->link = iterator->link->previous; \
} \
\
obj Iterator_##obj##_dereference(BinarySearchTree_##obj##_Iterator* iterator) { \
  Node_##obj* node = (Node_##obj*) iterator->link; \
  return node->element; \
} \
\
void BST_##obj##_addLeftNode_##obj(BinarySearchTree_##obj* bst, Node_##obj* parent, Node_##obj* newNode) { \
  parent->left = newNode; \
  newNode->backReference = &parent->left; \
  newNode->link.previous = parent->link.previous; \
  newNode->link.next = &parent->link; \
  parent->link.previous->next = &newNode->link; \
  parent->link.previous = &newNode->link; \
} \
\
void BST_##obj##_addRightNode_##obj(BinarySearchTree_##obj* bst, Node_##obj* parent, Node_##obj* newNode) { \
  parent->right = newNode; \
  newNode->backReference = &parent->right; \
  newNode->link.previous = &parent->link; \
  newNode->link.next = parent->link.next; \
  parent->link.next->previous = &newNode->link; \
  parent->link.next = &newNode->link; \
}

#endif
