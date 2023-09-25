#include <stdio.h>
#include <stdlib.h>

// linked list data structure

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct LL {
  Node *head;
} LL;

void add_node(LL *ll, Node *added) { // more pointers = higher ground to modify variables?
  Node **curr = &(ll->head);
  while ((*curr) != NULL)
    curr = &((*curr)->next);
  *curr = added;
}

void rm_node(LL *ll, Node *rm_node) {
  Node **curr = &(ll->head);
  while (*curr != NULL && *curr != rm_node)
    curr = &((*curr)->next);
  if (*curr != NULL)
    *curr = rm_node->next;
}

void print_ll(LL *ll) {
  Node *curr = ll->head;
  printf("[");
  while (curr != NULL) {
    printf("%d, ", curr->data);
    curr = curr->next;
  }
  printf("]\n");
}

int main() {
  {
    LL ll = {NULL};
    const int L = 10;
    Node *ns = (Node *)malloc(sizeof(Node) * L);
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
    LL ll = {NULL};
    Node a = {0, NULL};
    add_node(&ll, &a);
    print_ll(&ll);
    rm_node(&ll, &a);
    print_ll(&ll);
  }

  return 0;
}
