#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include <stdlib.h>

struct node {
  int value;
  struct node* next;
};

struct stack {
  struct node* first;
  struct node* last;
};

struct stack* init(void);
void push(struct stack* stack, int new_value);
int pop(struct stack* stack);
void destroy(struct stack* stack);

#endif  // SRC_STACK_H_


