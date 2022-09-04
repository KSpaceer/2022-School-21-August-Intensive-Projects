#include "expression_parsing.h"


token *parse(char *expression, int *error, int *tokens_size_ptr) {
  int is_operator = 1;
  token *tokens = NULL;
  int tokens_size = 0;
  int tokens_max_size = 0;
  int parentheses_balance = 0;
  while (*expression && 0 == *error) {
    if (tokens_size == tokens_max_size) {
      tokens = expand_tokens(tokens, &tokens_max_size, error);
    }
    if (*expression == ' ') {
    } else if (*expression >= '0' && *expression <= '9') {
      tokens[tokens_size++] = number_extraction(&expression, error);
      is_operator--;
    } else if (*expression == '(') {
      token new_token = {.type = OPERATOR, .i_value = OPENING_PARENTHESIS, .priority = 0};
      tokens[tokens_size++] = new_token;
      parentheses_balance++;
    } else if (*expression == ')') {
      token new_token = {.type = OPERATOR, .i_value = CLOSING_PARENTHESIS, .priority = 0};
      tokens[tokens_size++] = new_token;
      parentheses_balance--;
    } else if (*expression == 'x') {
      token new_token = {.type = VARIABLE};
      tokens[tokens_size++] = new_token;
      is_operator--;
    } else if (1 == is_operator) {
      tokens[tokens_size++] = unary_operator_extraction(&expression, error);
    } else if (0 == is_operator) {
      tokens[tokens_size++] = binary_operator_extraction(expression, error);
      is_operator++;
    }
    if (parentheses_balance < 0 || (is_operator != 0 && is_operator != 1)) {
      *error = 1;
    }
    expression++;
  }
  if (0 != parentheses_balance || is_operator != 0) {
    *error = 1;
  }
  *tokens_size_ptr = tokens_size;
  return tokens;
}

token unary_operator_extraction(char **expression, int *error) {
  token uo_token = {.type = OPERATOR};
  if (**expression == '-') {
    uo_token.i_value = UNARY_MINUS;
  } else if (**expression == 's') {
    if (0 == strncmp(*expression, "sin(", 4)) {
      uo_token.i_value = SIN;
      *expression += 2;
    } else if (0 == strncmp(*expression, "sqrt(", 5)) {
      uo_token.i_value = SQRT;
      *expression += 3;
    } else {
      *error = 1;
    }
  } else if (**expression == 'c') {
    if (0 == strncmp(*expression, "cos(", 4)) {
      uo_token.i_value = COS;
      *expression += 2;
    } else if (0 == strncmp(*expression, "ctg(", 4)) {
      uo_token.i_value = CTG;
      *expression += 2;
    } else {
      *error = 1;
    }
  } else if (0 == strncmp(*expression, "tan(", 4)) {
    uo_token.i_value = TAN;
    *expression += 2;
  } else if (0 == strncmp(*expression, "ln(", 3)) {
    uo_token.i_value = LN;
    *expression += 1;
  } else {
    *error = 1;
  }
  return uo_token;
}

token binary_operator_extraction(const char *expression, int *error) {
  token bo_token = {.type = OPERATOR};
  if (*expression == '-') {
    bo_token.i_value = BINARY_MINUS;
    bo_token.priority = 1;
  } else if (*expression == '+') {
    bo_token.i_value = PLUS;
    bo_token.priority = 1;
  } else if (*expression == '/') {
    bo_token.i_value = DIVISION;
    bo_token.priority = 2;
  } else if (*expression == '*') {
    bo_token.i_value = MULTIPLICATION;
    bo_token.priority = 2;
  } else {
    *error = 1;
  }
  return bo_token;
}

token *expand_tokens(token *tokens, int *tokens_max_size, int *error) {
  token *tmp_tokens = tokens;
  if (*tokens_max_size) {
    *tokens_max_size = (int)((double)*tokens_max_size * 1.6);
  } else {
    *tokens_max_size = 8;
  }
  tmp_tokens = realloc(tmp_tokens, *tokens_max_size * sizeof(token));
  if (NULL == tmp_tokens) {
    *error = 1;
  } else {
    tokens = tmp_tokens;
  }
  return tokens;
}

token number_extraction(char **expression, int *error) {
  char *number_ending_ptr = *expression;
  int dot_count = 0;
  token number_token = {.type = NUMBER, .d_value = 0., .priority = 0};
  while ((*number_ending_ptr >= '0' && *number_ending_ptr <= '9') || *number_ending_ptr == '.') {
    if (*number_ending_ptr == '.') {
      dot_count++;
    }
    number_ending_ptr++;
  }
  if (dot_count > 1 || *(number_ending_ptr - 1) == '.') {
    *error = 1;
  } else {
    char old_symbol = *number_ending_ptr;
    *number_ending_ptr = '\0';
    double number = atof(*expression);
    *number_ending_ptr = old_symbol;
    number_token.d_value = number;
  }
  *expression = number_ending_ptr - 1;
  return number_token;
}

