#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hash map implementation

// linked list data structure
typedef struct Node {
  char *data;
  char *value;
  struct Node *next;
} Node;

typedef struct LL {
  Node *head;
  Node *tail;
} LL;

void insert_node(LL *ll, Node *added) {
  added->next = ll->head;
  ll->head = added;
}

void append_node(LL *ll, Node *added) {
  if (!ll->tail)
    ll->head = ll->tail = added;
  else {
    ll->tail->next = added;
    ll->tail = added;
  }
}

Node * value_node(LL *ll, char *data) {
  Node *curr = ll->head;
  while (curr) {
    //printf("curr %p %s %s %p %p\n", curr, curr->data, ll->tail->data, ll->tail->next, curr->next);
    if (strcmp(curr->data, data) == 0)
      return curr;
    curr = curr->next;
  }
  return NULL; // not found
}

void print_ll(LL *ll) {
  Node *curr = ll->head;
  printf("[");
  while (curr) {
    printf("%s, ", curr->data);
    curr = curr->next;
  }
  printf("]\n");
}

// hash map
typedef struct Map {
  int max_size;
  LL *idxs;
} Map; 

unsigned long
hash(char *str) { // https://stackoverflow.com/questions/7666509/hash-function-for-string#7666577
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

Map make_map(int max_size) {
  LL *idxs = (LL *)calloc(max_size, sizeof(LL)); // must use calloc since it essentially assigns all elements to linked lists with null heads
  Map ret = {max_size, idxs};
  return ret;
}

void set_insert_value(Map m, char *c) {
  Node *n = (Node *)malloc(sizeof(Node *));
  n->data = c;
  n->next = NULL;
  LL *place_ll = &(m.idxs[hash(c) % m.max_size]);
  if (!value_node(place_ll, c))
    append_node(place_ll, n);
}

void map_insert_value(Map m, char *c, char *v) {
  Node *n = (Node *)malloc(sizeof(Node *));
  n->data = c;
  n->value = v;
  n->next = NULL;
  LL *place_ll = &(m.idxs[hash(c) % m.max_size]);
  Node *update_node = value_node(place_ll, c);
  if (!update_node)
    append_node(place_ll, n);
  else {
    update_node->value = v;
    free(n);
  }
}

int contains(Map m, char *c) {
  LL *place_ll = &(m.idxs[hash(c) % m.max_size]);
  return value_node(place_ll, c) != NULL;
}

void remove_value(Map m, char *c) {
  LL *place_ll = &(m.idxs[hash(c) % m.max_size]);

  // remove value in linked list, equivalent to rm_node but comparing values instead of mem addresses
  Node **curr = &(place_ll->head);
  Node *past = NULL;
  while (*curr && strcmp((*curr)->data, c) != 0) {
    past = *curr;
    curr = &(*curr)->next;
  }
  if (place_ll->tail && strcmp(place_ll->tail->data, c) == 0)
    place_ll->tail = past;
  if (*curr) {
    Node *rm_node = *curr;
    *curr = rm_node->next;
    free(rm_node);
  }
}

char * map_get(Map m, char *c) {
  LL *place_ll = &(m.idxs[hash(c) % m.max_size]);
  Node *n = value_node(place_ll, c);
  return n ? n->value : NULL;
}

void print_set(Map m) {
  Node *curr;
  printf("{");
  for (int i = 0; i < m.max_size; ++i) {
    curr = m.idxs[i].head;
    while (curr) {
      printf("%s, ", curr->data);
      curr = curr->next;
    }
  }
  printf("}\n");
}

void print_map(Map m) {
  Node *curr;
  printf("{");
  for (int i = 0; i < m.max_size; ++i) {
    curr = m.idxs[i].head;
    while (curr) {
      printf("%s: %s, ", curr->data, curr->value);
      curr = curr->next;
    }
  }
  printf("}\n");
}

void free_map(Map m) {
  Node *curr;
  for (int i = 0; i < m.max_size; ++i) {
    curr = m.idxs[i].head;
    Node *rm;
    while (curr) {
      rm = curr;
      curr = curr->next;
      free(rm);
    }
  }
  free(m.idxs);
}

int main() {
  Map m = make_map((int)(1<<10));
  map_insert_value(m, "hi", "a");
  map_insert_value(m, "joe", "a");
  map_insert_value(m, "johnny", "a");
  map_insert_value(m, "johnny", "b");
  map_insert_value(m, "alpha", "a");
  map_insert_value(m, "alpha", "b");
  map_insert_value(m, "alpha", "c");
  map_insert_value(m, "alpha", "d");
  map_insert_value(m, "alpha", "e");
  print_set(m);
  print_map(m);
  printf("Map contains %s: %d\n", "hi", contains(m, "hi"));
  printf("Map contains %s: %d\n", "joe", contains(m, "joe"));
  printf("Map contains %s: %d\n", "johnny", contains(m, "johnny"));
  printf("Map contains %s: %d\n", "alpha", contains(m, "alpha"));
  printf("Map contains %s: %d\n", "Alpha", contains(m, "Alpha"));
  printf("Map[%s]: %s\n", "hi", map_get(m, "hi"));
  printf("Map[%s]: %s\n", "joe", map_get(m, "joe"));
  printf("Map[%s]: %s\n", "johnny", map_get(m, "johnny"));
  printf("Map[%s]: %s\n", "alpha", map_get(m, "alpha"));
  printf("Map[%s]: %s\n", "Alpha", map_get(m, "Alpha"));
  printf("Remove alpha\n");
  remove_value(m, "alpha");
  print_map(m);
  printf("Attempt to remove alpha again\n");
  remove_value(m, "alpha");
  print_map(m);
  printf("Map[%s]: %s\n", "alpha", map_get(m, "alpha"));
  printf("Map[alpha] = bravo\n");
  map_insert_value(m, "alpha", "bravo");
  print_map(m);
  printf("Remove alpha\n");
  remove_value(m, "alpha");
  print_map(m);
  printf("Remove hi\n");
  remove_value(m, "hi");
  print_map(m);
  printf("Remove joe\n");
  remove_value(m, "joe");
  print_map(m);
  printf("Remove johnny\n");
  remove_value(m, "johnny");
  print_map(m);
  free_map(m);
  return 0;
}
