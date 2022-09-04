#include "graph_rendering.h"

void transform_to_matrix(int *arr, int **matrix) {
  for (int i = 0; i < HEIGHT; i++) {
    matrix[i] = arr + i * WIDTH;
  }
}

void find_dots(int **matrix, token *rpn_tokens, int rpn_tokens_size) {
  double x_step = (double)(RIGHT_BORDER - LEFT_BORDER) / (WIDTH - 1);
  double y_step = (double)(TOP_BORDER - BOTTOM_BORDER) / (HEIGHT - 1);
  double x_value = 0;
  for (int i = 0; i < WIDTH; i++, x_value += x_step) {
    double result = rpn_calculate(rpn_tokens, rpn_tokens_size, x_value);
    if (!isnan(result) && !isinf(result)) {
      int j = round((result + 1.)/y_step);
      if (j >= 0 && j < HEIGHT) {
        matrix[j][i] = 1;
      }
    }
  }
}

void rendering(int **matrix) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (0 == matrix[i][j]) {
        printf(".");
      } else {
        printf("*");
      }
    }
    printf("\n");
  }
}

void error_output(void) {
  printf("An error occured somewhere...\n");
}
