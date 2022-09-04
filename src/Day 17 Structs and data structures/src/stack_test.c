#include "stack.h"
#include <stdio.h>

char *push_test(void);
char *pop_test(void);
struct stack *init_stack(int size);

int main(void) {
  printf("%s\n", push_test());
  printf("%s\n", pop_test());
  return 0;
}

struct stack *init_stack(int size) {
  struct stack *stack = init();
  for (int i = 0; i < size; i++) {
    push(stack, i);
  }
  return stack;
}

char *push_test(void) {
  struct stack *stack = init_stack(7);
  push(stack, 7);
  push(stack, 8);
  int i = 8;
  int fail = 0;
  struct node *cur_node = stack->last;
  while (NULL != cur_node && !fail) {
    if (cur_node->value != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
      i--;
    }
  }
  destroy(stack);
  return fail ? "FAIL" : "SUCCESS";
}

char *pop_test(void) {
  struct stack *stack = init_stack(7);
  pop(stack);
  int popped_value = pop(stack);
  int i = 4;
  int fail = 0;
  struct node *cur_node = stack->last;
  while (NULL != cur_node && !fail) {
    if (cur_node->value != i) {
      fail = 1;
    } else {
      cur_node = cur_node->next;
      i--;
    }
  }
  fail += i != -1 || popped_value != 5;
  destroy(stack);
  return fail ? "FAIL" : "SUCCESS";
}
