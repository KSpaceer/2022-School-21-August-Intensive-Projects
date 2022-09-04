#include "reverse_polish_notation.h"

token *to_rpn(token *tokens, int tokens_size, int *rpn_tokens_size) {
  stack *operator_stack = stack_init();
  token *rpn_tokens = malloc(tokens_size * sizeof(token));
  int cur_token = 0;
  for (int i = 0; i < tokens_size; i++) {
    if (NUMBER == tokens[i].type || VARIABLE == tokens[i].type) {
      rpn_tokens[cur_token++] = tokens[i];
    } else {
      cur_token = operator_handling(operator_stack, tokens[i], cur_token,
                                    rpn_tokens, rpn_tokens_size);
    }
  }
  while (operator_stack->top) {
    rpn_tokens[cur_token++] = pop(operator_stack);
  }
  destroy_stack(operator_stack);
  return rpn_tokens;
}

int operator_handling(stack *op_stack, token or_token, int cur_token,
                      token *rpn_tokens, int *rpn_tokens_size) {
  if (or_token.i_value > 4) {
    push(op_stack, or_token);
  } else if (or_token.i_value != 4) {
    while (op_stack->top &&
           (op_stack->top->data.i_value > 5 ||
            (op_stack->top->data.i_value < 4 && op_stack->top->data.priority >= or_token.priority))) {
      rpn_tokens[cur_token++] = pop(op_stack);
    }
    push(op_stack, or_token);
  } else {
    while (op_stack->top &&
           op_stack->top->data.i_value != OPENING_PARENTHESIS) {
      rpn_tokens[cur_token++] = pop(op_stack);
    }
    pop(op_stack);
    *rpn_tokens_size -= 2;
  }
  return cur_token;
}

double rpn_calculate(token *rpn_tokens, int rpn_tokens_size, double x_value) {
  stack *operand_stack = stack_init();
  for (int i = 0; i < rpn_tokens_size; i++) {
    if (NUMBER == rpn_tokens[i].type) {
      push(operand_stack, rpn_tokens[i]);
    } else if (VARIABLE == rpn_tokens[i].type) {
      token var_token = {.type = NUMBER, .d_value = x_value, .priority = 0};
      push(operand_stack, var_token);
    } else if (rpn_tokens[i].i_value > 4) {
      unary_operation(operand_stack, rpn_tokens[i].i_value);
    } else {
      binary_operation(operand_stack, rpn_tokens[i].i_value);
    }
  }
  token result_token = pop(operand_stack);
  destroy_stack(operand_stack);
  return result_token.d_value;
}

void unary_operation(stack *operand_stack, int operator_value) {
  token operand_token = pop(operand_stack);
  token updated_token = {.type = NUMBER, .d_value = 0., .priority = 0};
  if (UNARY_MINUS == operator_value) {
    updated_token.d_value = -1 * operand_token.d_value;
  } else if (SIN == operator_value) {
    updated_token.d_value = sin(operand_token.d_value);
  } else if (COS == operator_value) {
    updated_token.d_value = cos(operand_token.d_value);
  } else if (TAN == operator_value) {
    updated_token.d_value = tan(operand_token.d_value);
  } else if (CTG == operator_value) {
    updated_token.d_value = 1. / tan(operand_token.d_value);
  } else if (SQRT == operator_value) {
    updated_token.d_value = sqrt(operand_token.d_value);
  } else if (LN == operator_value) {
    updated_token.d_value = log(operand_token.d_value);
  }
  push(operand_stack, updated_token);
}

void binary_operation(stack *operand_stack, int operator_value) {
  token right_operand = pop(operand_stack);
  token left_operand = pop(operand_stack);
  token result_token = {.type = NUMBER, .d_value = 0., .priority = 0};
  if (PLUS == operator_value) {
    result_token.d_value = left_operand.d_value + right_operand.d_value;
  } else if (BINARY_MINUS == operator_value) {
    result_token.d_value = left_operand.d_value - right_operand.d_value;
  } else if (MULTIPLICATION == operator_value) {
    result_token.d_value = left_operand.d_value * right_operand.d_value;
  } else if (DIVISION == operator_value) {
    result_token.d_value = left_operand.d_value / right_operand.d_value;
  }
  push(operand_stack, result_token);
}
