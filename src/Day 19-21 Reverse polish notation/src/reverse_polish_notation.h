#ifndef SRC_REVERSE_POLISH_NOTATION_H_
#define SRC_REVERSE_POLISH_NOTATION_H_
#include "rpn_data_structures.h"
#include <math.h>

token *to_rpn(token *tokens, int tokens_size, int *rpn_tokens_size);
int operator_handling(stack *op_stack, token or_token, int cur_token, token *rpn_tokens, int *rpn_tokens_size);
double rpn_calculate(token *rpn_tokens, int rpn_tokens_size, double x_value);
void unary_operation(stack *operand_stack, int operator_value);
void binary_operation(stack *operand_stack, int operator_value);



#endif  // SRC_REVERSE_POLISH_NOTATION_H_
