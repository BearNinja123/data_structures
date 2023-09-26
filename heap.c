#include <stdio.h>
#include <stdlib.h>

// Min heap data structure

typedef struct heap_t {
  int max_size;
  int size;
  int *data;
} heap_t;

heap_t init_heap() {
  int *data = (int *)malloc(sizeof(int));
  heap_t ret = {1, 0, data};
  return ret;
}

void swap(heap_t *h, int i1, int i2) {
  int tmp = h->data[i1];
  h->data[i1] = h->data[i2];
  h->data[i2] = tmp;
}

void siftup(heap_t *h, int index) {
  int child, parent;
  child = h->data[index];
  parent = h->data[index/2];
  while (index != 0 && child < parent) {
    swap(h, index, index/2);
    index /= 2;
    parent = h->data[index/2];
  }
}

void siftdown(heap_t *h, int index) {
  int l_child, r_child, min_idx;
  int parent = h->data[index];
  while (index < h->size / 2) {
    l_child = h->data[index * 2];
    r_child = (index * 2 + 1 < h->size) ? h->data[index * 2 + 1] : (1 << 31) - 1;
    min_idx = index * 2 + (l_child < r_child ? 0 : 1); 

    if (parent > h->data[min_idx]) {
      swap(h, index, min_idx);
      index = min_idx;
    }
    else
      return;
  }
}

void push(heap_t *h, int d) {
  if (h->size == h->max_size) {
    int *data = (int *)malloc(2 * h->max_size * sizeof(int));
    for (int i = 0; i < h->max_size; ++i)
      data[i] = h->data[i];
    free(h->data);
    h->data = data;
    h->max_size *= 2;
  }
  h->data[h->size++] = d;
  siftup(h, h->size - 1);
}

int pop(heap_t *h) {
  swap(h, 0, --h->size);
  siftdown(h, 0);
  return h->data[h->size];
}

void print_heap(heap_t h) {
  printf("[");
  for (int i = 0; i < h.size; ++i)
    printf("%d, ", h.data[i]);
  printf("]\n");
}

int main() {
  heap_t h = init_heap();
  for (int i = 0; i < 10; ++i) {
    printf("Adding %d to heap\n", 10-i);
    push(&h, 10-i);
    print_heap(h);
    printf("\n");
  }
  printf("---------------------------\n");
  for (int i = 0; i < 10; ++i) {
    printf("Popped %d from heap\n", pop(&h));
    print_heap(h);
    printf("\n");
  }
}
