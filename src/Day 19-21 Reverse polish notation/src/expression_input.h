#ifndef SRC_EXPRESSION_INPUT_H_
#define SRC_EXPRESSION_INPUT_H_
#include <stdio.h>
#include <stdlib.h>

char *get_expression(int *error);
char *expand_expression(char *expression, int *max_size, int *error);
void greeting_message(void);

#endif  // SRC_EXPRESSION_INPUT_H_
