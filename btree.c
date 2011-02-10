#include "btree.h"

// Plus de détail sur l'exo 20 fait en cours
typedef struct _BoolNode {
  int val;
  struct _BoolNode* left;
  struct _BoolNode* right;
} BoolNode;

struct _BoolTree {
  BoolNode* root;
};
