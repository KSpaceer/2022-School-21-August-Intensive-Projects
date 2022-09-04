#include <stdio.h>

int Fib(int n);

int main(void) {
  int n = 0;
  char term = 0;
  if (2 != scanf("%d%c", &n, &term) || term != '\n' || n <= 0) {
    printf("n/a");
  } else {
    n = Fib(n);
    if (n <= 0) {
      printf("n/a");
    } else {
      printf("%d", n);
    }
  }
}

int Fib(int n) {
  if (n == 1 || n == 2) {
    return 1;
  }
  return Fib(n - 1) + Fib(n - 2);
}
