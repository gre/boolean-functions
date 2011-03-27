#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
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
  node -> right = r;
  return node;
}

BoolNode* btree_newLeaf(int b) {
  BoolNode* node = malloc(sizeof(*node));
  node -> val = b;
  node -> left = 0;
  node -> right = 0;
  return node;
}

int btree_equals(BoolNode* a, BoolNode* b) {
  if(a==0) return (b==0);
  if(a->left==0) return b!=0 && b->left==0 && a->val == b->val;
  return btree_equals(a->left, b->left) && btree_equals(a->right, b->right);
}

BoolNode* rec_btree_simplify(BoolNode* node) {
  if(node!=0 && node->left!=0) {
    node->left = rec_btree_simplify(node->left);
    node->right = rec_btree_simplify(node->right);
    if(btree_equals(node->left, node->right)) {
      return node->left;
    }
  }
  return node;
}

BoolTree* btree_simplify(BoolTree* tree) {
  tree->root = rec_btree_simplify(tree->root);
  return tree;
}

FunctionNode* btree_toFunctionNode(BoolNode* node) {
  // TODO
}
FunctionTree* btree_toFunctionTree(BoolTree* tree) {
  // TODO
}

/**
 * id = 1 at first call
 */
static void rec_btree_printDot(BoolNode* node, FILE* out) {
  if(node==0) return;
  if(node->left==0) {
    // Leaf
    fprintf(out, "  n%p [label=\"%d\"]\n", node, node->val);
  }
  else {
    // Node
    fprintf(out, "  n%p [label=\"%c\"]\n", node, (char)node->val);
    fprintf(out, "  n%p -- n%p\n", node, node->left);
    fprintf(out, "  n%p -- n%p\n", node, node->right);
    rec_btree_printDot(node->left, out);
    rec_btree_printDot(node->right, out);
  }
}

void btree_printDot(BoolTree* btree, FILE* out) {
  fprintf(out, "## Generated by Boolean Functions v%g\n", VERSION);
  fprintf(out, "graph {\n");
  rec_btree_printDot(btree->root, out);
  fprintf(out, "}\n");
}
