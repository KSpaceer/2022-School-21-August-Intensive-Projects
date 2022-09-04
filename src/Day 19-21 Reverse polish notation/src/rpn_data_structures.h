#ifndef SRC_RPN_DATA_STRUCTURES_H_
#define SRC_RPN_DATA_STRUCTURES_H_
#include <stdlib.h>

#define NUMBER 0
#define VARIABLE 1
#define OPERATOR 2

#define PLUS 0
#define BINARY_MINUS 1
#define MULTIPLICATION 2
#define DIVISION 3
#define CLOSING_PARENTHESIS 4
#define OPENING_PARENTHESIS 5
#define UNARY_MINUS 6
#define SIN 7
#define COS 8
#define TAN 9
#define CTG 10
#define SQRT 11
#define LN 12

typedef struct token {
  int type;
  union {
    int i_value;
    double d_value;
  };
  int priority;
} token;

typedef struct node {
  token data;
  struct node *next;
} node;

typedef struct stack {
  int size;
  node *top;
} stack;

stack *stack_init(void);
void push(stack *token_stack, token value);
token pop(stack *token_stack);
void destroy_stack(stack *token_stack);


#endif  // SRC_RPN_DATA_STRUCTURES_H_
