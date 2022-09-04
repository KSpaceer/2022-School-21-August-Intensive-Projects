#ifndef SRC_GRAPH_RENDERING_H_
#define SRC_GRAPH_RENDERING_H_
#include "rpn_data_structures.h"
#include "reverse_polish_notation.h"
#include <math.h>
#include <stdio.h>

#define LEFT_BORDER 0
#define RIGHT_BORDER (4 * M_PI)
#define BOTTOM_BORDER -1
#define TOP_BORDER 1

#define WIDTH 80
#define HEIGHT 25

void transform_to_matrix(int *arr, int **matrix);
void find_dots(int **matrix, token *rpn_tokens, int rpn_tokens_size);
void rendering(int **matrix);
void error_output(void);


#endif  // SRC_GRAPH_RENDERING_H_
