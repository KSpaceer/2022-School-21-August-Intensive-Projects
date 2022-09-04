#include <stdio.h>

int GreatestPrimeDivisor(int a);
int IsDivisor(int div, int a);
int IsPrime(int p);

int main(void) {
  int a = 0;
  char term = 0;
  if (2 != scanf("%d%c", &a, &term) || term != '\n' || 0 == a || 1 == a || -1 == a) {
    printf("n/a");
  } else {
    int gpd = GreatestPrimeDivisor(a);
    printf("%d", gpd);
  }
  return 0;
}

int GreatestPrimeDivisor(int a) {
  int gpd = 0;
  a = a > 0 ? a : -a;
  for (int i = a; i > 1 && !gpd; i--) {
    if (IsDivisor(i, a) && IsPrime(i)) {
      gpd = i;
    }
  }
  return gpd;
}

int IsDivisor(int div, int a) {
  int result = 0;
  while (a > 0) {
    a -= div;
  }
  if (0 == a) {
    result = 1;
  }
  return result;
}

int IsPrime(int p) {
  int result = 1;
  for (int i = 2; i < p && result; i++) {
    if (IsDivisor(i, p) != 0) {
      result = 0;
    }
  }
  return result;
}
