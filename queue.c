#include <stdio.h>
#include <stdlib.h>

// Queue data structure

typedef struct Queue {
  int max_size;
  int front, size;
  int *data;
} Queue;

Queue init_queue() {
  int *data = (int *)malloc(sizeof(int));
  Queue ret = {1, 0, 0, data}; // init queue to have max size of 1
  return ret;
}

void add(Queue *s, int d) {
  if (s->size == s->max_size) { // double data array size if overflow
    int *new_data = (int *)malloc(2 * s->max_size * sizeof(int));
    for (int i = 0; i < s->max_size; ++i) {
      new_data[i] = s->data[(s->front + i) % s->max_size];
    }
    free(s->data);
    s->data = new_data;
    s->max_size *= 2;
    s->front = 0;
  }
  s->data[(s->front + s->size++) % s->max_size] = d;
}

int peek(Queue s) { return s.data[s.front]; }
int poll(Queue *s) {
  s->front = (s->front + 1) % s->max_size;
  --s->size;
  return s->data[s->front];
}

void print_queue(Queue s) {
  printf("[");
  for (int i = 0; i < s.size; ++i)
    printf("%d, ", s.data[(s.front+i) % s.max_size]);
  printf("]\n");
}

int main() {
  Queue s = init_queue();
  print_queue(s);
  for (int i = 0; i < 10; ++i) {
    printf("adding %d to queue\n", i);
    add(&s, i);
    printf("queue peek: %d\n", peek(s));
    print_queue(s);
  }
  for (int i = 0; i < 10; ++i) {
    printf("queue poll: %d\n", poll(&s));
    print_queue(s);
  }
  return 0;
}
