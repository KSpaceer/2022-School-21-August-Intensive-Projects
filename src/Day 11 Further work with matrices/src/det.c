#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.000001

double det(double **matrix, int rows, int columns);
int input(double ***matrix, int *n, int *m);
double **singleAllocation(int rows_amount, int columns_amount, int *error);
void swapRows(double **matrix, int row1, int row2);
void output(double det, int error);
void freeMemory(double **matrix);

int main(void) {
  double **matrix = NULL;
  int rows = 0, columns = 0;
  int error = 0;
  double determinant = 0;
  error = input(&matrix, &rows, &columns);
  if (!error) {
    determinant = det(matrix, rows, columns);
  }
  output(determinant, error);
  freeMemory(matrix);
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

void output(double det, int error) {
  if (error) {
    printf("n/a");
  } else {
    printf("%.6lf", det);
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

double det(double **matrix, int rows, int columns) {
  double determinant = 1.;
  double sign = 1.;
  for (int i = 0; i < rows && fabs(determinant) >= EPSILON; i++) {
    double diagonal_element = matrix[i][i];
    int another_row = i;
    while (fabs(diagonal_element) < EPSILON && fabs(determinant) >= EPSILON) {
      if (fabs(matrix[another_row][i]) >= EPSILON) {
        swapRows(matrix, i, another_row);
        diagonal_element = matrix[i][i];
        sign *= -1;
      }
      another_row++;
      if (rows == another_row) {
        determinant = 0.;
      }
    }
    for (int j = i + 1; j < rows && fabs(determinant) >= EPSILON; j++) {
      double multiplier = matrix[j][i] / diagonal_element;
      for (int k = i; k < columns; k++) {
        matrix[j][k] -= matrix[i][k] * multiplier;
      }
    }
    determinant *= diagonal_element;
  }
  determinant = fabs(determinant) >= EPSILON ? sign * determinant : fabs(determinant);
  return determinant;
}

void swapRows(double **matrix, int row1, int row2) {
  double *temp = matrix[row1];
  matrix[row1] = matrix[row2];
  matrix[row2] = temp;
}

void freeMemory(double **matrix) { free(matrix); }
