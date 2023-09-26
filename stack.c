#include <stdio.h>
#include <stdlib.h>

// stack_t data structure

typedef struct stack_t {
  int max_size;
  int size;
  int *data;
} stack_t;

stack_t init_stack() {
  int *data = (int *)malloc(sizeof(int));
  stack_t ret = {1, 0, data}; // init stack to have max size of 1
  return ret;
}

void push(stack_t *s, int d) {
  if (s->size == s->max_size) { // double data array size if overflow
    int *new_data = (int *)malloc(2 * s->max_size * sizeof(int));
    for (int i = 0; i < s->max_size; ++i)
      new_data[i] = s->data[i];
    free(s->data);
    s->data = new_data;
    s->max_size *= 2;
  }
  s->data[s->size++] = d;
}

int peek(stack_t s) { return s.data[s.size-1]; }
int pop(stack_t *s) { return s->data[--s->size]; }

void print_stack(stack_t s) {
  printf("[");
  for (int i = 0; i < s.size; ++i)
    printf("%d, ", s.data[i]);
  printf("]\n");
}

int main() {
  stack_t s = init_stack();
  print_stack(s);
  for (int i = 0; i < 10; ++i) {
    printf("adding %d to stack\n", i);
    push(&s, i);
    printf("stack peek: %d\n", peek(s));
    print_stack(s);
  }
  for (int i = 0; i < 10; ++i) {
    printf("stack pop: %d\n", pop(&s));
    print_stack(s);
  }
  return 0;
}
