#include "stack.h"

struct stack *init(void) {
  struct stack *stack = malloc(sizeof(struct stack));
  stack->first = NULL;
  stack->last = NULL;
  return stack;
}

void push(struct stack *stack, int new_value) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->value = new_value;
  new_node->next = NULL;
  if (NULL == stack->first) {
    stack->first = new_node;
  } else {
    new_node->next = stack->last;
  }
  stack->last = new_node;
}

int pop(struct stack *stack) {
  int value = 0;
  if (stack->last != NULL) {
    struct node *last_node = stack->last;
    value = last_node->value;
    stack->last = last_node->next;
    free(last_node);
  }
  return value;
}

void destroy(struct stack *stack) {
  struct node *cur_node = stack->last;
  struct node *next_node = NULL;
  while (NULL != cur_node) {
    next_node = cur_node->next;
    free(cur_node);
    cur_node = next_node;
  }
  free(stack);
}
