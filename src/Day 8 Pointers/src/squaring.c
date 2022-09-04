#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n, int error);
void squaring(int *a, int n);

int main() {
  int data[NMAX], n, error;
  error = input(data, &n);
  if (!error) {
    squaring(data, n);
  }
  output(data, n, error);

  return 0;
}

int input(int *a, int *n) {
  int error = 0;
  if (1 != scanf("%d", n) || *n <= 0 || *n > NMAX) {
    error = 1;
  }
  int *p = a;
  for (int i = 0; i < *n && !error; i++, p++) {
    if (1 != scanf("%d", p)) {
      error = 1;
    }
  }
  return error;
}

void output(int *a, int n, int error) {
  // NOTHING
  if (error) {
    printf("n/a");
  } else {
    int *p = a;
    for (int i = 0; i < (n - 1); i++, p++) {
      printf("%d ", *p);
    }
    printf("%d", *p);
  }
}

void squaring(int *a, int n) {
  // NOTHING
  int *p = a;
  for (int i = 0; i < n; i++, p++) {
    *p = *p * *p;
  }
}
