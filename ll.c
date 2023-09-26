#include <stdio.h>
#include <stdlib.h>

// linked list data structure

typedef struct node_t {
  int data;
  struct node_t *next;
} node_t;

typedef struct ll_t {
  node_t *head;
} ll_t;

void add_node(ll_t *ll, node_t *added) { // more pointers = higher ground to modify variables?
  node_t **curr = &(ll->head);
  while ((*curr) != NULL)
    curr = &((*curr)->next);
  *curr = added;
}

void rm_node(ll_t *ll, node_t *rm_node) {
  node_t **curr = &(ll->head);
  while (*curr != NULL && *curr != rm_node)
    curr = &((*curr)->next);
  if (*curr != NULL)
    *curr = rm_node->next;
}

void print_ll(ll_t *ll) {
  node_t *curr = ll->head;
  printf("[");
  while (curr != NULL) {
    printf("%d, ", curr->data);
    curr = curr->next;
  }
  printf("]\n");
}

int main() {
  {
    ll_t ll = {NULL};
    const int L = 10;
    node_t *ns = (node_t *)malloc(sizeof(node_t) * L);
    for (int i = 0; i < L; ++i) {
      ns[i].data = i;
      add_node(&ll, &ns[i]);
    }
    print_ll(&ll);
    rm_node(&ll, &ns[9]);
    print_ll(&ll);
    rm_node(&ll, &ns[4]);
    print_ll(&ll);
    rm_node(&ll, &ns[0]);
    print_ll(&ll);
  }

  {
    ll_t ll = {NULL};
    node_t a = {0, NULL};
    add_node(&ll, &a);
    print_ll(&ll);
    rm_node(&ll, &a);
    print_ll(&ll);
  }

  return 0;
}
