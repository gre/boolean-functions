#include "btree.h"

struct _BoolNode {
  int val; // si left != 0, val prends la valeur de la variable concerné. Sinon val prends une valeure booléenne de feuille
  struct _BoolNode* left; // si 0
  struct _BoolNode* right; // si 1
};

struct _BoolTree {
  BoolNode* root;
};

BoolTree* btree_createTreeWith(BoolNode* root) {
  BoolTree* tree = malloc(sizeof(*tree));
  tree->root = root;
  return tree;
}

BoolNode* btree_newNode(BoolNode* l, char var, BoolNode* r) {
  BoolNode* node = malloc(sizeof(*node));
  node -> val = var;
  node -> left = l;
  node -> left = r;
  return node;
}

BoolNode* btree_newLeaf(int b) {
  BoolNode* node = malloc(sizeof(*node));
  node -> val = b;
  node -> left = 0;
  node -> left = 0;
  return node;
}
