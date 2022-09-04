#include "rpn_data_structures.h"
#include "expression_input.h"
#include "expression_parsing.h"
#include "reverse_polish_notation.h"
#include "graph_rendering.h"

int main(void) {
  greeting_message();
  int error = 0;
  char *expression = get_expression(&error);
  int original_tokens_size = 0;
  token *original_tokens = parse(expression, &error, &original_tokens_size);
  int rpn_tokens_size = original_tokens_size;
  token *rpn_tokens = NULL;
  if (!error) {
    rpn_tokens = to_rpn(original_tokens, original_tokens_size, &rpn_tokens_size);
    int screen_arr[HEIGHT][WIDTH] = {0};
    int *matrix[HEIGHT];
    transform_to_matrix((int*)screen_arr, matrix);
    find_dots(matrix, rpn_tokens, rpn_tokens_size);
    rendering(matrix);
  } else {
    error_output();
  }
  free(expression);
  free(original_tokens);
  free(rpn_tokens);
  return 0;
}
