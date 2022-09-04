#include <stdio.h>
#include <stdlib.h>

int inputProperties(int *type, int *rows_amount, int *columns_amount);
int **singleAllocation(int rows_amount, int columns_amount, int *error);
int **doubleAllocation(int rows_amount, int columns_amount, int *error);
int **multipleAllocation(int rows_amount, int columns_amount, int *error);
void inputValues(int **matrix, int rows_amount, int columns_amount, int *error);
void sortMatrix(int **matrix, int rows_amount, int columns_amount, int *error);
void bubbleSort(int **matrix, int *rows_sums, int rows_amount);
void outputMatrix(int **matrix, int rows_amount, int columns_amount, int error);
void freeMemory(int **matrix, int rows_amount, int type);

int main(void) {
  int type = 0, rows_amount, columns_amount;
  int error = inputProperties(&type, &rows_amount, &columns_amount);
  int **matrix = NULL;
  if (1 == type) {
    matrix = singleAllocation(rows_amount, columns_amount, &error);
  } else if (2 == type) {
    matrix = doubleAllocation(rows_amount, columns_amount, &error);
  } else if (3 == type) {
    matrix = multipleAllocation(rows_amount, columns_amount, &error);
  }
  inputValues(matrix, rows_amount, columns_amount, &error);
  sortMatrix(matrix, rows_amount, columns_amount, &error);
  outputMatrix(matrix, rows_amount, columns_amount, error);
  freeMemory(matrix, rows_amount, type);
}

int inputProperties(int *type, int *rows_amount, int *columns_amount) {
  int error = 0;
  if (1 != scanf("%d", type) || *type < 1 || *type > 3) {
    error = 1;
  }
  if (error || 1 != scanf("%d", rows_amount) || *rows_amount <= 0) {
    error = 1;
  }
  if (error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0) {
    error = 1;
  }
  return error;
}

void inputValues(int **matrix, int rows_amount, int columns_amount,
                 int *error) {
  for (int i = 0; i < rows_amount && 0 == *error; i++) {
    for (int j = 0; j < columns_amount && 0 == *error; j++) {
      if (1 != scanf("%d", &(matrix[i][j]))) {
        *error = 1;
      }
    }
  }
}

void outputMatrix(int **matrix, int rows_amount, int columns_amount,
                  int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < rows_amount; i++) {
      for (int j = 0; j < columns_amount - 1; j++) {
        printf("%d ", matrix[i][j]);
      }
      int j = columns_amount - 1;
      printf("%d", matrix[i][j]);
      if (i < rows_amount - 1) {
        printf("\n");
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

int **doubleAllocation(int rows_amount, int columns_amount, int *error) {
  int **matrix = NULL;
  int *values = NULL;
  if (0 == *error) {
    matrix = malloc(rows_amount * sizeof(int *));
    values = malloc(rows_amount * columns_amount * sizeof(int));
  }
  if (NULL == matrix || NULL == values) {
    *error = 1;
  }
  for (int i = 0; i < rows_amount && 0 == *error; i++) {
    matrix[i] = values + columns_amount * i;
  }
  return matrix;
}

int **multipleAllocation(int rows_amount, int columns_amount, int *error) {
  int **matrix = NULL;
  if (0 == *error) {
    matrix = malloc(rows_amount * sizeof(int *));
  }
  if (NULL == matrix) {
    *error = 1;
  }
  for (int i = 0; i < rows_amount; i++) {
    matrix[i] = *error == 0 ? malloc(columns_amount * sizeof(int)) : NULL;
    if (NULL == matrix[i]) {
      *error = 1;
    }
  }
  return matrix;
}

void sortMatrix(int **matrix, int rows_amount, int columns_amount, int *error) {
  int *rows_sums = NULL;
  if (0 == *error) {
    rows_sums = malloc(rows_amount * sizeof(int));
  }
  if (*error || NULL == rows_sums) {
    *error = 1;
  } else {
    for (int i = 0; i < rows_amount; i++) {
      int sum = 0;
      for (int j = 0; j < columns_amount; j++) {
        sum += matrix[i][j];
      }
      rows_sums[i] = sum;
    }
    bubbleSort(matrix, rows_sums, rows_amount);
  }
  free(rows_sums);
}

void bubbleSort(int **matrix, int *rows_sums, int rows_amount) {
  for (int i = 0; i < rows_amount; i++) {
    for (int j = 0; j < rows_amount - i - 1; j++) {
      if (rows_sums[j] > rows_sums[j + 1]) {
        int temp = rows_sums[j];
        rows_sums[j] = rows_sums[j + 1];
        rows_sums[j + 1] = temp;
        int *temprow = matrix[j];
        matrix[j] = matrix[j + 1];
        matrix[j + 1] = temprow;
      }
    }
  }
}

void freeMemory(int **matrix, int rows_amount, int type) {
  if (1 == type) {
    free(matrix);
  } else if (2 == type && matrix != NULL) {
    int *values_beginning = matrix[0];
    for (int i = 0; i < rows_amount; i++) {
      if (matrix[i] < values_beginning) {
        values_beginning = matrix[i];
      }
    }
    free(values_beginning);
    free(matrix);
  } else if (3 == type && matrix != NULL) {
    for (int i = 0; i < rows_amount; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
}
