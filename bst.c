#include <stdio.h>
#include <stdlib.h>

// Binary search tree data structure

typedef struct node_t {
  int data;
  struct node_t *left;
  struct node_t *right;
} node_t;

typedef struct bst_t {
  int size;
  node_t *head;
} bst_t;

bst_t init_bst() {
  bst_t ret = {0, NULL};
  return ret;
}

void add(bst_t *tree, int d) {
  node_t *d_node = (node_t *)malloc(sizeof(node_t *));
  d_node->data = d;
  node_t **curr = &tree->head;
  while (*curr != NULL)
    curr = (d <= (*curr)->data) ? &(*curr)->left : &(*curr)->right;
  *curr = d_node;
  ++tree->size;
}

void rm(bst_t *tree, int d) {
  node_t **curr = &(tree->head);
  while (*curr != NULL && (*curr)->data != d) // find the node to be removed
    curr = (d <= (*curr)->data) ? &(*curr)->left : &(*curr)->right;
  if (*curr == NULL)
    return;

  if ((*curr)->left == NULL && (*curr)->right == NULL) {
    free(*curr);
    *curr = NULL;
    return;
  }

  // find removed node's inorder successor node (child)
  node_t *child;
  node_t *child_replacement; // child's children which will take the place of child
  if ((*curr)->left == NULL) {
    child = (*curr)->right;
    while (child->left != NULL)
      child = child->left;
    child_replacement = child->right;
  }
  else {
    child = (*curr)->left;
    while (child->right != NULL)
      child = child->right;
    child_replacement = child->left;
  }

  free(*curr);
  *curr = child;
  child = child_replacement;
  --tree->size;
}

void print_inorder(node_t *n) {
  if (n == NULL)
    return;
  print_inorder(n->left);
  printf("%d, ", n->data);
  print_inorder(n->right);
}

void print_tree_inorder(bst_t tree) {
  printf("[");
  print_inorder(tree.head);
  printf("]\n");
}

int main() {
  bst_t tree = init_bst();
  print_tree_inorder(tree);
  for (int i = 0; i < 10; ++i) {
    printf("Adding %d to tree\n", 10-i);
    add(&tree, 10-i);
    print_tree_inorder(tree);
    printf("\n");
  }
  printf("------------------------\n");
  for (int i = 0; i < 10; ++i) {
    printf("Removing %d to tree\n", 10-i);
    rm(&tree, 10-i);
    print_tree_inorder(tree);
    printf("\n");
  }
}
