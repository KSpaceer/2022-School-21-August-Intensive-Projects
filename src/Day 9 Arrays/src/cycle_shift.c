#include <stdio.h>

#define MAXN 10

int input(int *A, int *n, int *c);
void cycle(int *A, int n, int c);
void output(int *A, int n, int error);

int main(void) {
  int n, A[MAXN], c;
  int error = input(A, &n, &c);
  if (!error && c != 0) {
    cycle(A, n, c);
  }
  output(A, n, error);
  return 0;
}

int input(int *A, int *n, int *c) {
  int error = 0;
  if (1 != scanf("%d", n) || *n <= 0 || *n > MAXN) {
    error = 1;
  }
  for (int i = 0; i < *n && !error; i++) {
    if (1 != scanf("%d", &(A[i]))) {
      error = 1;
    }
  }
  if (!error && 1 != scanf("%d", c)) {
    error = 1;
  }
  return error;
}

void cycle(int *A, int n, int c) {
  c = c > 0 ? c % n : c % n + n;
  for (int i = 0; i < n - c; i++) {
    for (int j = i, k = 0; k < c; j = (n + j - 1) % n, k++) {
      int temp = A[j];
      A[j] = A[(n + j - 1) % n];
      A[(n + j - 1) % n] = temp;
    }
  }
}

void output(int *A, int n, int error) {
  if (error) {
    printf("n/a");
  } else {
    for (int i = 0; i < n - 1; i++) {
      printf("%d ", A[i]);
    }
    printf("%d", A[n - 1]);
  }
}
