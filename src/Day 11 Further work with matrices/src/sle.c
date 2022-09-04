#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 0.000001

void sle(double **matrix, int rows, int columns, double **roots, int *error);
double **invert(double **matrix, int rows, int columns, int *error);
double det(double **matrix, int rows, int columns, int *error);
double **transpose(double **matrix, int rows, int columns, int *error);
double findCofactor(double **matrix, int rows_amount, int columns_amount,
                    int row, int columns, int *error);
int input(double ***matrix, int *n, int *m);
double **singleAllocation(int rows_amount, int columns_amount, int *error);
void swapRows(double **matrix, int row1, int row2);
double *extractColumn(double **matrix, int rows, int column, int *error);
void replaceColumn(double **matrix, const double *column, int rows_amount,
                   int column_index);
void copyColumn(double **matrix, double **matrix2, int rows, int column_index);
void copyMatrix(double **matrix1, double **matrix2, int rows, int columns);
void freeMemory(double **matrix, double *roots);
void outputRoots(double *roots, int rows, int error);

int main(void) {
  double **matrix = NULL;
  double *roots = NULL;
  int rows = 0, columns = 0;
  int error = 0;
  error = input(&matrix, &rows, &columns);
  if (!error) {
    sle(matrix, rows, columns, &roots, &error);
  }
  outputRoots(roots, rows, error);
  freeMemory(matrix, roots);
  return 0;
}

int input(double ***matrix, int *rows_amount, int *columns_amount) {
  int error = 0;
  if (1 != scanf("%d", rows_amount) || *rows_amount <= 0) {
    error = 1;
  }
  if (error || 1 != scanf("%d", columns_amount) || *columns_amount <= 0 ||
      *rows_amount != *columns_amount - 1) {
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

void outputRoots(double *roots, int rows, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < rows - 1; i++) {
      printf("%.6lf ", roots[i]);
    }
    printf("%.6lf", roots[rows - 1]);
  }
}

void sle(double **matrix, int rows, int columns, double **roots, int *error) {
  double **working_matrix = singleAllocation(rows, columns - 1, error);
  copyMatrix(matrix, working_matrix, rows, columns - 1);
  double *last_column = extractColumn(matrix, rows, columns - 1, error);
  double determinant = det(working_matrix, rows, columns - 1, error);
  *roots = malloc(rows * sizeof(double));
  if (*error || fabs(determinant) < EPSILON || NULL == *roots) {
    *error = 1;
  } else {
    for (int i = 0; i < rows; i++) {
      replaceColumn(working_matrix, last_column, rows, i);
      (*roots)[i] = det(working_matrix, rows, columns - 1, error) / determinant;
      copyColumn(working_matrix, matrix, rows, i);
    }
  }
  free(working_matrix);
  free(last_column);
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

double *extractColumn(double **matrix, int rows, int column, int *error) {
  double *extracted_column = malloc(rows * sizeof(double));
  if (NULL == extracted_column) {
    *error = 1;
  } else {
    for (int i = 0; i < rows; i++) {
      extracted_column[i] = matrix[i][column];
    }
  }
  return extracted_column;
}

void replaceColumn(double **matrix, const double *column, int rows_amount,
                   int column_index) {
  for (int i = 0; i < rows_amount; i++) {
    matrix[i][column_index] = column[i];
  }
}

void copyColumn(double **matrix, double **matrix2, int rows_amount,
                int column_index) {
  for (int i = 0; i < rows_amount; i++) {
    matrix[i][column_index] = matrix2[i][column_index];
  }
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

void freeMemory(double **matrix, double *roots) {
  free(matrix);
  free(roots);
}
