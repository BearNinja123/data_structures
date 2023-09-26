#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hash map implementation

// linked list data structure
typedef struct node_t {
  char *data;
  char *value;
  struct node_t *next;
} node_t;

typedef struct ll_t {
  node_t *head;
  node_t *tail;
} ll_t;

void insert_node(ll_t *ll, node_t *added) {
  added->next = ll->head;
  ll->head = added;
}

void append_node(ll_t *ll, node_t *added) {
  if (!ll->tail)
    ll->head = ll->tail = added;
  else {
    ll->tail->next = added;
    ll->tail = added;
  }
}

node_t * value_node(ll_t *ll, char *data) {
  node_t *curr = ll->head;
  while (curr) {
    //printf("curr %p %s %s %p %p\n", curr, curr->data, ll->tail->data, ll->tail->next, curr->next);
    if (strcmp(curr->data, data) == 0)
      return curr;
    curr = curr->next;
  }
  return NULL; // not found
}

void print_ll(ll_t *ll) {
  node_t *curr = ll->head;
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
  ll_t *idxs;
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
  ll_t *idxs = (ll_t *)calloc(max_size, sizeof(ll_t)); // must use calloc since it essentially assigns all elements to linked lists with null heads
  Map ret = {max_size, idxs};
  return ret;
}

void set_insert_value(Map m, char *c) {
  node_t *n = (node_t *)malloc(sizeof(node_t *));
  n->data = c;
  n->next = NULL;
  ll_t *place_ll = &(m.idxs[hash(c) % m.max_size]);
  if (!value_node(place_ll, c))
    append_node(place_ll, n);
}

void map_insert_value(Map m, char *c, char *v) {
  node_t *n = (node_t *)malloc(sizeof(node_t *));
  n->data = c;
  n->value = v;
  n->next = NULL;
  ll_t *place_ll = &(m.idxs[hash(c) % m.max_size]);
  node_t *update_node = value_node(place_ll, c);
  if (!update_node)
    append_node(place_ll, n);
  else {
    update_node->value = v;
    free(n);
  }
}

int contains(Map m, char *c) {
  ll_t *place_ll = &(m.idxs[hash(c) % m.max_size]);
  return value_node(place_ll, c) != NULL;
}

void remove_value(Map m, char *c) {
  ll_t *place_ll = &(m.idxs[hash(c) % m.max_size]);

  // remove value in linked list, equivalent to rm_node but comparing values instead of mem addresses
  node_t **curr = &(place_ll->head);
  node_t *past = NULL;
  while (*curr && strcmp((*curr)->data, c) != 0) {
    past = *curr;
    curr = &(*curr)->next;
  }
  if (place_ll->tail && strcmp(place_ll->tail->data, c) == 0)
    place_ll->tail = past;
  if (*curr) {
    node_t *rm_node = *curr;
    *curr = rm_node->next;
    free(rm_node);
  }
}

char * map_get(Map m, char *c) {
  ll_t *place_ll = &(m.idxs[hash(c) % m.max_size]);
  node_t *n = value_node(place_ll, c);
  return n ? n->value : NULL;
}

void print_set(Map m) {
  node_t *curr;
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
  node_t *curr;
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
  node_t *curr;
  for (int i = 0; i < m.max_size; ++i) {
    curr = m.idxs[i].head;
    node_t *rm;
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
