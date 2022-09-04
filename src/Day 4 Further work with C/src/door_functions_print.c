#include <math.h>
#include <stdio.h>

double AgnesiWitch(double x);
double BernoulliLemniscate(double x);
double QuadraticHyperbola(double x);
void PrintAgnesiWitch(void);
void PrintBernoulliLemniscate(void);
void PrintQuadraticHyperbola(void);

int main(void) {
  PrintAgnesiWitch();
  printf("==========================================");
  PrintBernoulliLemniscate();
  printf("==========================================");
  PrintQuadraticHyperbola();
  return 0;
}

void PrintAgnesiWitch(void) {
  double dif = 0.153248422;
  double unit = 0.0473411;
  for (int i = 20; i >= 0; i--) {
    double x = -3.14159265358979323846;
    for (int j = 0; j < 42; j++, x += dif) {
      double y = AgnesiWitch(x);
      if (y >= i * unit && y <= (i + 1) * unit) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void PrintBernoulliLemniscate(void) {
  double dif = 0.153248422;
  double unit = 0.0237905;
  printf("\n");
  for (int i = 20; i >= 0; i--) {
    double x = -3.14159265358979323846;
    for (int j = 0; j < 42; j++, x += dif) {
      double y = BernoulliLemniscate(x);
      if (y >= i * unit && y <= (i + 1) * unit) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void PrintQuadraticHyperbola(void) {
  double dif = 0.153248422;
  double unit = 8.11052;
  printf("\n");
  for (int i = 20; i >= 0; i--) {
    double x = -3.14159265358979323846;
    for (int j = 0; j < 42; j++, x += dif) {
      double y = QuadraticHyperbola(x);
      if (y >= i * unit && y <= (i + 1) * unit) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

double AgnesiWitch(double x) { return 1 / (1 + x * x); }

double BernoulliLemniscate(double x) {
  double result = 1 + 4 * x * x;
  result = sqrt(result) - x * x - 1;
  result = sqrt(result);
  return result;
}

double QuadraticHyperbola(double x) { return 1 / (x * x); }
