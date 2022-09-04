#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n, int error);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
  int n, data[NMAX], error;
  error = input(data, &n);
  output(data, n, error);
  if (!error) {
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
  }
  return 0;
}

int input(int *a, int *n) {
  int error = 0;
  if (1 != scanf("%d", n) || *n <= 0 || *n > NMAX) {
    error = 1;
  }
  for (int i = 0; i < *n && !error; i++, a++) {
    if (1 != scanf("%d", a)) {
      error = 1;
    }
  }
  return error;
}

void output(int *a, int n, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < (n - 1); i++, a++) {
      printf("%d ", *a);
    }
    printf("%d", *a);
  }
}

int max(int *a, int n) {
  int maximum = *a;
  for (int i = 0; i < n; i++, a++) {
    if (maximum < *a) {
      maximum = *a;
    }
  }
  return maximum;
}

int min(int *a, int n) {
  int minimum = *a;
  for (int i = 0; i < n; i++, a++) {
    if (minimum > *a) {
      minimum = *a;
    }
  }
  return minimum;
}

double mean(int *a, int n) {
  double mean_var = 0;
  for (int i = 0; i < n; i++, a++) {
    mean_var += *a;
  }
  mean_var /= n;
  return mean_var;
}

double variance(int *a, int n) {
  double variance_var = 0;
  double mean_var = mean(a, n);
  for (int i = 0; i < n; i++, a++) {
    variance_var += (*a - mean_var) * (*a - mean_var);
  }
  variance_var /= n;
  return variance_var;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
  printf("\n");
  printf("%d ", max_v);
  printf("%d ", min_v);
  printf("%.6lf ", mean_v);
  printf("%.6lf", variance_v);
}
