#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 0.000001

double **invert(double **matrix, int rows, int columns, int *error);
double det(double **matrix, int rows, int columns, int *error);
double **transpose(double **matrix, int rows, int columns, int *error);
double findCofactor(double **matrix, int rows_amount, int columns_amount,
                    int row, int columns, int *error);
int input(double ***matrix, int *n, int *m);
double **singleAllocation(int rows_amount, int columns_amount, int *error);
void swapRows(double **matrix, int row1, int row2);
void copyMatrix(double **matrix1, double **matrix2, int rows, int columns);
void output(double **result, int result_rows, int result_columns, int error);
void freeMemory(double **matrix, double **inverse_matrix);

int main(void) {
  double **matrix = NULL, **inverse_matrix = NULL;
  int rows = 0, columns = 0;
  int error = 0;
  error = input(&matrix, &rows, &columns);
  if (!error) {
    if (rows > 1) {
      inverse_matrix = invert(matrix, rows, columns, &error);
    } else if (**matrix >= EPSILON) {
      inverse_matrix = malloc(sizeof(int*) + sizeof(int));
      *inverse_matrix = (double*)(inverse_matrix + 1);
      **inverse_matrix = 1/(**matrix);
    } else {
      error = 1;
    }
  }
  output(inverse_matrix, rows, columns, error);
  freeMemory(matrix, inverse_matrix);
  return 0;
}

int input(double ***matrix, int *rows_amount, int *columns_amount) {
  int error = 0;
  if (1 != scanf("%d", rows_amount) || *rows_amount <= 0) {
    error = 1;
  }
  if (error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0 ||
      *rows_amount != *columns_amount) {
    error = 1;
  }
  *matrix = singleAllocation(*rows_amount, *columns_amount, &error);
  for (int i = 0; i < *rows_amount && 0 == error; i++) {
    for (int j = 0; j < *columns_amount && 0 == error; j++) {
      if (1 != scanf("%lf", (*matrix)[i] + j)) {
        error = 1;
      }
    }
  }
  return error;
}

void output(double **result, int result_rows, int result_columns, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < result_rows; i++) {
      for (int j = 0; j < result_columns - 1; j++) {
        printf("%.6lf ", result[i][j]);
      }
      printf("%.6lf", result[i][result_columns - 1]);
      if (i < result_rows - 1) {
        printf("\n");
      }
    }
  }
}

double **singleAllocation(int rows_amount, int columns_amount, int *error) {
  double **matrix = NULL;
  if (0 == *error) {
    matrix = malloc(rows_amount * columns_amount * sizeof(double) +
                    rows_amount * sizeof(double *));
  }
  if (NULL == matrix) {
    *error = 1;
  }
  double *beginning = NULL != matrix ? (double *)(matrix + rows_amount) : NULL;
  for (int i = 0; i < rows_amount && 0 == *error; i++) {
    matrix[i] = beginning + columns_amount * i;
  }
  return matrix;
}

void copyMatrix(double **matrix1, double **matrix2, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix2[i][j] = matrix1[i][j];
    }
  }
}

double det(double **matrix, int rows, int columns, int *error) {
  double determinant = 1.;
  double sign = 1.;
  double **spare_matrix = singleAllocation(rows, columns, error);
  copyMatrix(matrix, spare_matrix, rows, columns);
  for (int i = 0; i < rows && fabs(determinant) >= EPSILON && 0 == *error;
       i++) {
    double diagonal_element = spare_matrix[i][i];
    int another_row = i;
    while (fabs(diagonal_element) < EPSILON && fabs(determinant) >= EPSILON) {
      if (fabs(spare_matrix[another_row][i]) >= EPSILON) {
        swapRows(spare_matrix, i, another_row);
        diagonal_element = spare_matrix[i][i];
        sign *= -1;
      }
      another_row++;
      if (rows == another_row) {
        determinant = 0.;
      }
    }
    for (int j = i + 1; j < rows && fabs(determinant) >= EPSILON; j++) {
      double multiplier = spare_matrix[j][i] / diagonal_element;
      for (int k = i; k < columns; k++) {
        spare_matrix[j][k] -= spare_matrix[i][k] * multiplier;
      }
    }
    determinant *= diagonal_element;
  }
  determinant =
      fabs(determinant) >= EPSILON ? sign * determinant : fabs(determinant);
  free(spare_matrix);
  return determinant;
}

void swapRows(double **matrix, int row1, int row2) {
  double *temp = matrix[row1];
  matrix[row1] = matrix[row2];
  matrix[row2] = temp;
}

double **transpose(double **matrix, int rows, int columns, int *error) {
  double **result = NULL;
  if (*error == 0) {
    result = singleAllocation(rows, columns, error);
    for (int i = 0; i < rows && 0 == *error; i++) {
      for (int j = 0; j < columns && 0 == *error; j++) {
        result[i][j] = matrix[j][i];
      }
    }
  }
  return result;
}

double **invert(double **matrix, int rows, int columns, int *error) {
  double **inverse_matrix = singleAllocation(rows, columns, error);
  double determinant = det(matrix, rows, columns, error);
  if (*error || fabs(determinant) < EPSILON) {
    *error = 1;
  } else {
    for (int i = 0; i < rows && 0 == *error; i++) {
      for (int j = 0; j < columns && 0 == *error; j++) {
        inverse_matrix[i][j] =
            findCofactor(matrix, rows, columns, i, j, error) / determinant;
      }
    }
    double **cofactor_matrix = inverse_matrix;
    inverse_matrix = transpose(inverse_matrix, rows, columns, error);
    free(cofactor_matrix);
  }
  return inverse_matrix;
}

double findCofactor(double **matrix, int rows_amount, int columns_amount,
                    int row, int column, int *error) {
  double **minor = singleAllocation(rows_amount - 1, columns_amount - 1, error);
  int m_i = 0;
  for (int i = 0; i < rows_amount; i++) {
    if (i != row) {
      int m_j = 0;
      for (int j = 0; j < columns_amount; j++) {
        if (j != column) {
          minor[m_i][m_j] = matrix[i][j];
          m_j++;
        }
      }
      m_i++;
    }
  }
  double cofactor = det(minor, rows_amount - 1, columns_amount - 1, error);
  if (fabs(cofactor) >= EPSILON) {
    cofactor = (row + column) % 2 ? -cofactor : cofactor;
  } else {
    cofactor = fabs(cofactor);
  }
  free(minor);
  return cofactor;
}

void freeMemory(double **matrix, double **inverse_matrix) {
  free(matrix);
  free(inverse_matrix);
}
