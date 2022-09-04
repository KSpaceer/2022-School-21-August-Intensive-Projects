#include <stdio.h>
#include <stdlib.h>

int input(int ***matrix, int *rows_amount, int *columns_amount,
          int *operation_type);
void inputMatrix(int ***matrix, int *rows, int *columns, int *error);
int **singleAllocation(int rows_amount, int columns_amount, int *error);
void output(int **result, int result_rows, int result_columns, int error);
void sum(int **first_matrix, int first_rows, int first_columns,
         int **second_matrix, int second_rows, int second_columns,
         int ***result, int *result_rows, int *result_columns, int *error);
void transpose(int **matrix, int rows, int columns, int ***result,
               int *result_rows, int *result_columns, int *error);
void mul(int **first_matrix, int first_rows, int first_columns,
         int **second_matrix, int second_rows, int second_columns,
         int ***result, int *result_rows, int *result_columns, int *error);
void freeMemory(int **first_matrix, int **second_matrix, int **result);

int main(void) {
  int error = 0;
  int operation_type = 0;
  int first_rows = 0, first_columns = 0, second_rows = 0, second_columns = 0;
  int **first_matrix = NULL, **second_matrix = NULL;
  error = input(&first_matrix, &first_rows, &first_columns, &operation_type);
  if (!error && operation_type != 3) {
    error =
        input(&second_matrix, &second_rows, &second_columns, &operation_type);
  }
  int **result = NULL;
  int result_rows, result_columns;
  if (1 == operation_type) {
    sum(first_matrix, first_rows, first_columns, second_matrix, second_rows,
        second_columns, &result, &result_rows, &result_columns, &error);
  } else if (2 == operation_type) {
    mul(first_matrix, first_rows, first_columns, second_matrix, second_rows,
        second_columns, &result, &result_rows, &result_columns, &error);
  } else if (3 == operation_type) {
    transpose(first_matrix, first_rows, first_columns, &result, &result_rows,
              &result_columns, &error);
  }
  output(result, result_rows, result_columns, error);
  freeMemory(first_matrix, second_matrix, result);
  return 0;
}

int input(int ***matrix, int *rows_amount, int *columns_amount,
          int *operation_type) {
  int error = 0;
  if (0 == *operation_type) {
    if (1 != scanf("%d", operation_type) || *operation_type < 1 ||
        *operation_type > 3) {
      error = 1;
    }
  }
  inputMatrix(matrix, rows_amount, columns_amount, &error);

  return error;
}

void output(int **result, int result_rows, int result_columns, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < result_rows; i++) {
      for (int j = 0; j < result_columns - 1; j++) {
        printf("%d ", result[i][j]);
      }
      printf("%d", result[i][result_columns - 1]);
      if (i < result_rows - 1) {
        printf("\n");
      }
    }
  }
}

void inputMatrix(int ***matrix, int *rows_amount, int *columns_amount,
                 int *error) {
  if (*error || 1 != scanf("%d", rows_amount) || *rows_amount <= 0) {
    *error = 1;
  }
  if (*error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0) {
    *error = 1;
  }
  *matrix = singleAllocation(*rows_amount, *columns_amount, error);
  for (int i = 0; i < *rows_amount && 0 == *error; i++) {
    for (int j = 0; j < *columns_amount && 0 == *error; j++) {
      if (1 != scanf("%d", (*matrix)[i] + j)) {
        *error = 1;
      }
    }
  }
}

int **singleAllocation(int rows_amount, int columns_amount, int *error) {
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

void sum(int **first_matrix, int first_rows, int first_columns,
         int **second_matrix, int second_rows, int second_columns,
         int ***result, int *result_rows, int *result_columns, int *error) {
  if (*error || first_rows != second_rows || first_columns != second_columns) {
    *error = 1;
  } else {
    *result_rows = first_rows;
    *result_columns = first_columns;
    *result = singleAllocation(*result_rows, *result_columns, error);
    for (int i = 0; i < *result_rows && 0 == *error; i++) {
      for (int j = 0; j < *result_columns && 0 == *error; j++) {
        (*result)[i][j] = first_matrix[i][j] + second_matrix[i][j];
      }
    }
  }
}

void mul(int **first_matrix, int first_rows, int first_columns,
         int **second_matrix, int second_rows, int second_columns,
         int ***result, int *result_rows, int *result_columns, int *error) {
  if (*error || first_columns != second_rows) {
    *error = 1;
  } else {
    *result_rows = first_rows;
    *result_columns = second_columns;
    *result = singleAllocation(*result_rows, *result_columns, error);
    for (int i = 0; i < *result_rows && 0 == *error; i++) {
      for (int j = 0; j < *result_columns && 0 == *error; j++) {
        (*result)[i][j] = 0;
        for (int k = 0; k < first_columns && 0 == *error; k++) {
          (*result)[i][j] += first_matrix[i][k] * second_matrix[k][j];
        }
      }
    }
  }
}

void transpose(int **matrix, int rows, int columns, int ***result,
               int *result_rows, int *result_columns, int *error) {
  if (*error == 0) {
    *result_rows = columns;
    *result_columns = rows;
    *result = singleAllocation(*result_rows, *result_columns, error);
    for (int i = 0; i < *result_rows && 0 == *error; i++) {
      for (int j = 0; j < *result_columns && 0 == *error; j++) {
        (*result)[i][j] = matrix[j][i];
      }
    }
  }
}

void freeMemory(int **first_matrix, int **second_matrix, int **result) {
  free(first_matrix);
  free(second_matrix);
  free(result);
}
