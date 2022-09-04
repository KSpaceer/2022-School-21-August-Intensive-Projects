#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result, int *error);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result, int *error);

int input(int ***matrix, int *n, int *m);
int **single_allocation(int rows_amount, int columns_amount, int *error);
int matrix_element_compare(const void *a, const void *b);
void output(int **matrix, int n, int m, int error, int emptyness);
void free_memory(int **matrix, int **result);

int main(void) {
  int **matrix = NULL, **result = NULL;
  int n = 0, m = 0;
  int error = 0;

  error = input(&matrix, &n, &m);

  result = single_allocation(n, m, &error);
  sort_vertical(matrix, n, m, result, &error);
  output(result, n, m, error, 0);
  if (!error) {
    sort_horizontal(matrix, n, m, result, &error);
    output(result, n, m, error, 1);
  }
  free_memory(matrix, result);
  return 0;
}

int input(int ***matrix, int *rows_amount, int *columns_amount) {
  int error = 0;
  if (1 != scanf("%d", rows_amount) || *rows_amount <= 0) {
    error = 1;
  }
  if (error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0) {
    error = 1;
  }
  *matrix = single_allocation(*rows_amount, *columns_amount, &error);
  for (int i = 0; i < *rows_amount && 0 == error; i++) {
    for (int j = 0; j < *columns_amount && 0 == error; j++) {
      if (1 != scanf("%d", (*matrix)[i] + j)) {
        error = 1;
      }
    }
  }
  return error;
}

void output(int **result, int rows, int columns, int error, int emptyness) {
  if (0 != error) {
    printf("n/a");
  } else {
    if (emptyness) {
      printf("\n\n");
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns - 1; j++) {
        printf("%d ", result[i][j]);
      }
      printf("%d", result[i][columns - 1]);
      if (i != rows - 1) {
        printf("\n");
      }
    }
  }
}

int **single_allocation(int rows_amount, int columns_amount, int *error) {
  int **matrix = NULL;
  if (0 == *error) {
    matrix = malloc(rows_amount * columns_amount * sizeof(int) +
                    rows_amount * sizeof(int *));
  }
  if (NULL == matrix) {
    *error = 1;
  }
  int *beginning = NULL != matrix ? (int *)(matrix + rows_amount) : NULL;
  for (int i = 0; i < rows_amount && 0 == *error; i++) {
    matrix[i] = beginning + columns_amount * i;
  }
  return matrix;
}

int matrix_elem_compare(const void *a, const void *b) {
  int a_num = *(int *)a;
  int b_num = *(int *)b;
  return a_num - b_num;
}

int *stringify_matrix(int **matrix, int rows, int columns, int *error) {
  int *matrix_string =
      *error == 0 ? malloc(rows * columns * sizeof(int)) : NULL;
  if (NULL == matrix_string) {
    *error = 1;
  } else {
    int string_index = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        matrix_string[string_index] = matrix[i][j];
        string_index++;
      }
    }
  }
  return matrix_string;
}

void sort_vertical(int **matrix, int rows, int columns, int **result,
                   int *error) {
  int *matrix_string = stringify_matrix(matrix, rows, columns, error);
  if (0 == *error) {
    int string_size = rows * columns;
    qsort(matrix_string, string_size, sizeof(int), matrix_elem_compare);
    int string_index = 0;
    int i = 0;
    int j = 0;
    int dir = 1;
    while (string_index < string_size) {
      result[i][j] = matrix_string[string_index];
      if ((1 == dir && rows - 1 == i) || (-1 == dir && 0 == i)) {
        j++;
        dir *= -1;
      } else {
        i += dir;
      }
      string_index++;
    }
  }
  free(matrix_string);
}

void sort_horizontal(int **matrix, int rows, int columns, int **result,
                     int *error) {
  int *matrix_string = stringify_matrix(matrix, rows, columns, error);
  if (0 == *error) {
    int string_size = rows * columns;
    qsort(matrix_string, string_size, sizeof(int), matrix_elem_compare);
    int string_index = 0;
    int i = 0;
    int j = 0;
    int dir = 1;
    while (string_index < string_size) {
      result[i][j] = matrix_string[string_index];
      if ((1 == dir && columns - 1 == j) || (-1 == dir && 0 == j)) {
        i++;
        dir *= -1;
      } else {
        j += dir;
      }
      string_index++;
    }
  }
  free(matrix_string);
}

void free_memory(int **matrix, int **result) {
  free(matrix);
  free(result);
}
