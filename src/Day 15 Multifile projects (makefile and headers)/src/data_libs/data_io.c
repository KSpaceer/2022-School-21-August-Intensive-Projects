#include "data_io.h"

int input(double **data, int *n) {
  int error = 0;
  if (1 != scanf("%d", n) || *n <= 0) {
    error = 1;
  } else {
    *data = malloc(*n * sizeof(double));
    if (NULL == *data) {
      error = 1;
    }
    for (int i = 0; i < *n && !error; i++) {
      if (1 != scanf("%lf", *data + i)) {
        error = 1;
      }
    }
  }
  return error;
}

void output(double *data, int n) {
  for (int i = 0; i < n - 1; i++) {
    printf("%.2lf ", data[i]);
  }
  printf("%.2lf", data[n - 1]);
}
