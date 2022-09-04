#ifndef SRC_EXPRESSION_PARSING_H_
#define SRC_EXPRESSION_PARSING_H_
#include "rpn_data_structures.h"
#include <string.h>
#include <stdlib.h>

token *parse(char *expression, int *error, int *tokens_size_ptr);
token unary_operator_extraction(char **expression, int *error);
token binary_operator_extraction(const char *expression, int *error);
token number_extraction(char **expression, int *error);
token *expand_tokens(token *tokens, int *tokens_max_size, int *error);



#endif  // SRC_EXPRESSION_PARSING_H_
