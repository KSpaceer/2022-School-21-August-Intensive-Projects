#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int inputProperties(int *type, int *rows_amount, int *columns_amount);
int **singleAllocation(int rows_amount, int columns_amount, int *error);
int **doubleAllocation(int rows_amount, int columns_amount, int *error);
int **multipleAllocation(int rows_amount, int columns_amount, int *error);
void inputValues(int **matrix, int rows_amount, int columns_amount, int type,
                 int *error);
void outputMatrix(int **matrix, int *rowmaxs, int *colmins, int rows_amount,
                  int columns_amount, int type, int error);
void freeMemory(int **matrix, int *rowmaxs, int *colmins, int rows_amount,
                int type);

void minMax(int **matrix, int rows_amount, int columns_amount, int **rowmaxs,
            int **colmins, int *error, int type);

int main(void) {
  int type = 0, rows_amount, columns_amount;
  int error = inputProperties(&type, &rows_amount, &columns_amount);
  int stat_matrix[MAXSIZE][MAXSIZE] = {0};
  int **matrix = (int **)stat_matrix;
  if (1 != type) {
    matrix = NULL;
  }
  if (2 == type) {
    matrix = singleAllocation(rows_amount, columns_amount, &error);
  } else if (3 == type) {
    matrix = doubleAllocation(rows_amount, columns_amount, &error);
  } else if (4 == type) {
    matrix = multipleAllocation(rows_amount, columns_amount, &error);
  }
  inputValues(matrix, rows_amount, columns_amount, type, &error);
  int *rowmaxs = NULL, *colmins = NULL;
  minMax(matrix, rows_amount, columns_amount, &rowmaxs, &colmins, &error, type);
  outputMatrix(matrix, rowmaxs, colmins, rows_amount, columns_amount, type,
               error);
  freeMemory(matrix, rowmaxs, colmins, rows_amount, type);
}

int inputProperties(int *type, int *rows_amount, int *columns_amount) {
  int error = 0;
  if (1 != scanf("%d", type) || *type < 1 || *type > 4) {
    error = 1;
  }
  if (error || 1 != scanf("%d", rows_amount) || *rows_amount <= 0 ||
      (1 == *type && *rows_amount > MAXSIZE)) {
    error = 1;
  }
  if (error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0 ||
      (1 == *type && *columns_amount > MAXSIZE)) {
    error = 1;
  }
  return error;
}

void inputValues(int **matrix, int rows_amount, int columns_amount, int type,
                 int *error) {
  for (int i = 0; i < rows_amount && 0 == *error; i++) {
    for (int j = 0; j < columns_amount && 0 == *error; j++) {
      int *element_address = type == 1
                                 ? (int *)(matrix + columns_amount * i + j)
                                 : (int *)(*(matrix + i) + j);
      if (1 != scanf("%d", element_address)) {
        *error = 1;
      }
    }
  }
}

void outputMatrix(int **matrix, int *rowmaxs, int *colmins, int rows_amount,
                  int columns_amount, int type, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < rows_amount; i++) {
      for (int j = 0; j < columns_amount - 1; j++) {
        int *element_address = type == 1
                                   ? (int *)(matrix + columns_amount * i + j)
                                   : (int *)(*(matrix + i) + j);
        printf("%d ", *element_address);
      }
      int j = columns_amount - 1;
      int *row_address = type == 1 ? (int *)(matrix + columns_amount * i + j)
                                   : (int *)(*(matrix + i) + j);
      printf("%d", *row_address);
      printf("\n");
    }
    for (int i = 0; i < rows_amount - 1; i++) {
      printf("%d ", rowmaxs[i]);
    }
    printf("%d\n", rowmaxs[rows_amount - 1]);
    for (int i = 0; i < columns_amount - 1; i++) {
      printf("%d ", colmins[i]);
    }
    printf("%d", colmins[columns_amount - 1]);
  }
}

int **singleAllocation(int rows_amount, int columns_amount, int *error) {
  int **matrix = NULL;
  matrix = malloc(rows_amount * columns_amount * sizeof(int) +
                  rows_amount * sizeof(int *));
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
  matrix = malloc(rows_amount * sizeof(int *));
  values = malloc(rows_amount * columns_amount * sizeof(int));
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
  matrix = malloc(rows_amount * sizeof(int *));
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

void freeMemory(int **matrix, int *rowmaxs, int *colmins, int rows_amount,
                int type) {
  if (2 == type) {
    free(matrix);
  } else if (3 == type) {
    free(matrix[0]);
    free(matrix);
  } else if (4 == type) {
    for (int i = 0; i < rows_amount; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
  free(rowmaxs);
  free(colmins);
}

void minMax(int **matrix, int rows_amount, int columns_amount, int **rowmaxs,
            int **colmins, int *error, int type) {
  if (0 == *error) {
    *rowmaxs = malloc(rows_amount * sizeof(int));
    *colmins = malloc(columns_amount * sizeof(int));
  }
  if (NULL == *rowmaxs || NULL == *colmins) {
    *error = 1;
  } else {
    for (int i = 0; i < rows_amount; i++) {
      int *element_address = type == 1 ? (int *)(matrix + columns_amount * i)
                                       : (int *)(*(matrix + i));
      (*rowmaxs)[i] = *element_address;
    }
    for (int i = 0; i < columns_amount; i++) {
      int *element_address =
          type == 1 ? (int *)(matrix + i) : (int *)(*matrix + i);
      (*colmins)[i] = *element_address;
    }
    for (int i = 0; i < rows_amount; i++) {
      for (int j = 0; j < columns_amount; j++) {
        int *element_address = type == 1
                                   ? (int *)(matrix + columns_amount * i + j)
                                   : (int *)(*(matrix + i) + j);
        if (*element_address > (*rowmaxs)[i]) {
          (*rowmaxs)[i] = *element_address;
        }
        if (*element_address < (*colmins)[j]) {
          (*colmins)[j] = *element_address;
        }
      }
    }
  }
}
