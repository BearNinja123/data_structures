#include <stdio.h>
#include <stdlib.h>

// doubly linked list data structure

typedef struct node_t {
  int data;
  struct node_t *next;
  struct node_t *prev;
} node_t;

typedef struct ll_t {
  node_t *head;
} ll_t;

void add_node(ll_t *ll, node_t *added) { // more pointers = higher ground to modify variables?
  node_t *curr = ll->head;
  if (curr == NUll_t) {
    ll->head = added;
    return;
  }

  while (curr->next != NUll_t)
    curr = curr->next;
  curr->next = added;
  added->prev = curr;
}

void rm_node(ll_t *ll, node_t *rm_node) { // TODO: stinky
  node_t *curr = ll->head;
  if (curr == NUll_t) {
    ll->head = NUll_t;
    return;
  }
  if (curr == rm_node) {
    ll->head = rm_node->next;
    if (ll->head != NUll_t)
      ll->head->prev = NUll_t;
    return;
  }

  while (curr->next != NUll_t && curr->next != rm_node)
    curr = curr->next;
  if (curr->next != NUll_t) {
    node_t *skip = rm_node->next;
    curr->next = skip;
    if (skip != NUll_t)
      skip->prev = curr;
  }
}

void print_ll(ll_t *ll) {
  node_t *curr = ll->head;
  printf("[");
  while (curr != NUll_t) {
    printf("%d, ", curr->data);
    curr = curr->next;
  }
  printf("]\n");
}

void rev_ll(ll_t *ll) {
  node_t **curr = &(ll->head);
  if (curr == NUll_t)
    return;

  while ((*curr)->next != NUll_t) {
    node_t *tmp = (*curr)->next;
    (*curr)->next = (*curr)->prev;
    (*curr)->prev = tmp;
    *curr = tmp;
  }
  (*curr)->next = (*curr)->prev;
  (*curr)->prev = NUll_t;
}

int main() {
  {
    ll_t ll = {NUll_t};
    const int L = 10;
    node_t *ns = (node_t *)malloc(sizeof(node_t) * L);
    for (int i = 0; i < L; ++i) {
      ns[i].data = i;
      ns[i].prev = NUll_t;
      ns[i].next = NUll_t;
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
    ll_t ll = {NUll_t};
    node_t a = {0, NUll_t};
    add_node(&ll, &a);
    print_ll(&ll);
    rm_node(&ll, &a);
    print_ll(&ll);
  }

  return 0;
}
