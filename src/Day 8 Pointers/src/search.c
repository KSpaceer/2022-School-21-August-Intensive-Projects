/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>

#define NMAX 30

int input(int *a, int *n);
void output(int desired, int error);
int find(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n, double mean_var);
int isEven(int number);
int compareWithMean(double mean_var, int number);
int threeSigmas(double mean_var, double variance_var, int number);

int main(void) {
  int data[NMAX], n, error, desired = 0;
  error = input(data, &n);
  if (!error) {
    desired = find(data, n);
  }
  output(desired, error);
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

void output(int desired, int error) {
  if (error) {
    printf("n/a");
  } else {
    printf("%d", desired);
  }
}

int find(int *a, int n) {
  int desired = 0;
  double mean_var = mean(a, n);
  double variance_var = variance(a, n, mean_var);
  for (int i = 0; i < n && !desired; i++, a++) {
    if (isEven(*a) && compareWithMean(mean_var, *a) &&
        threeSigmas(mean_var, variance_var, *a) && *a != 0) {
      desired = *a;
    }
  }
  return desired;
}

double mean(int *a, int n) {
  double mean_var = 0;
  for (int i = 0; i < n; i++, a++) {
    mean_var += *a;
  }
  mean_var /= n;
  return mean_var;
}

double variance(int *a, int n, double mean_var) {
  double variance_var = 0;
  for (int i = 0; i < n; i++, a++) {
    variance_var += (*a - mean_var) * (*a - mean_var);
  }
  variance_var /= n;
  return variance_var;
}

int isEven(int number) { return number % 2 - 1; }

int compareWithMean(double mean_var, int number) {
  return (double)number >= mean_var;
}

int threeSigmas(double mean_var, double variance_var, int number) {
  return (double)number <= mean_var + 3 * sqrt(variance_var);
}
