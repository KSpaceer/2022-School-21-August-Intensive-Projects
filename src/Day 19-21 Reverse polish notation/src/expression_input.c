#include "expression_input.h"

char *get_expression(int *error) {
  char *expression = NULL;
  int max_size = 0;
  int exp_size = 0;
  do {
    if (exp_size == max_size) {
      expression = expand_expression(expression, &max_size, error);
    }
    expression[exp_size] = getchar();
  } while ('\n' != expression[exp_size++] && 0 == *error);
  expression[exp_size - 1] = '\0';
  return expression;
}

char *expand_expression(char *expression, int *max_size, int *error) {
  char *tmp_exp = expression;
  if (*max_size) {
    *max_size = (int)((double)*max_size * 1.6);
  } else {
    *max_size = 32;
  }
  tmp_exp = realloc(tmp_exp, *max_size * sizeof(char));
  if (NULL == tmp_exp) {
    *error = 1;
  } else {
    expression = tmp_exp;
  }
  return expression;
}

void greeting_message(void) {
  printf("Welcome to the Inverse Polish Notation Calculator.\n");
  printf("Please, insert a mathematic expression using \'+\', \'-\', \'*\' and \'/\' operators\n");
  printf("and functions such as sin, cos, tan, ctg, sqrt and ln. Also you can use parentheses.\n");
}

