#include "rpn_data_structures.h"

stack *stack_init(void) {
  stack *token_stack = malloc(sizeof(stack));
  if (NULL != token_stack) {
    token_stack->size = 0;
    token_stack->top = NULL;
  }
  return token_stack;
}

void push(stack *token_stack, token value) {
  node *new_node = malloc(sizeof(node));
  if (NULL != new_node) {
    new_node->data = value;
    new_node->next = token_stack->top;
    token_stack->top = new_node;
    token_stack->size++;
  }
}

token pop(stack *token_stack) {
  token extracted = {.type = 0, .i_value = 0};
  if (token_stack->top) {
    extracted = token_stack->top->data;
    node *popped = token_stack->top;
    token_stack->top = token_stack->top->next;
    token_stack->size--;
    free(popped);
  }
  return extracted;
}

void destroy_stack(stack *token_stack) {
  node *cur_node = NULL;
  while (NULL != token_stack->top) {
    cur_node = token_stack->top;
    token_stack->top = token_stack->top->next;
    free(cur_node);
  }
  free(token_stack);
}
