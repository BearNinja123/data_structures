#include <stdio.h>
#include <stdlib.h>

// doubly linked list data structure

typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct LL {
  Node *head;
} LL;

void add_node(LL *ll, Node *added) { // more pointers = higher ground to modify variables?
  Node *curr = ll->head;
  if (curr == NULL) {
    ll->head = added;
    return;
  }

  while (curr->next != NULL)
    curr = curr->next;
  curr->next = added;
  added->prev = curr;
}

void rm_node(LL *ll, Node *rm_node) { // TODO: stinky
  Node *curr = ll->head;
  if (curr == NULL) {
    ll->head = NULL;
    return;
  }
  if (curr == rm_node) {
    ll->head = rm_node->next;
    if (ll->head != NULL)
      ll->head->prev = NULL;
    return;
  }

  while (curr->next != NULL && curr->next != rm_node)
    curr = curr->next;
  if (curr->next != NULL) {
    Node *skip = rm_node->next;
    curr->next = skip;
    if (skip != NULL)
      skip->prev = curr;
  }
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

void rev_ll(LL *ll) {
  Node **curr = &(ll->head);
  if (curr == NULL)
    return;

  while ((*curr)->next != NULL) {
    Node *tmp = (*curr)->next;
    (*curr)->next = (*curr)->prev;
    (*curr)->prev = tmp;
    *curr = tmp;
  }
  (*curr)->next = (*curr)->prev;
  (*curr)->prev = NULL;
}

int main() {
  {
    LL ll = {NULL};
    const int L = 10;
    Node *ns = (Node *)malloc(sizeof(Node) * L);
    for (int i = 0; i < L; ++i) {
      ns[i].data = i;
      ns[i].prev = NULL;
      ns[i].next = NULL;
      add_node(&ll, &ns[i]);
    }
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    printf("\n");

    rm_node(&ll, &ns[9]);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    printf("\n");

    rm_node(&ll, &ns[4]);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    printf("\n");

    rm_node(&ll, &ns[0]);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    rev_ll(&ll);
    print_ll(&ll);
    printf("-------------------------------------\n");
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
