#include <math.h>
#include <stdio.h>

double AgnesiWitch(double x);
double BernoulliLemniscate(double x);
double QuadraticHyperbola(double x);

int main(void) {
  double x = -3.14159265358979323846;
  double dif = 0.153248422;
  for (int i = 0; i < 42; i++, x += dif) {
    double aw = AgnesiWitch(x);
    double bl = BernoulliLemniscate(x);
    double qh = QuadraticHyperbola(x);
    if (isnan(bl)) {
      printf("%.7lf | %.7lf | - | %.7lf\n", x, aw, qh);
    } else {
      if (i < 41) {
        printf("%.7lf | %.7lf | %.7lf | %.7lf\n", x, aw, bl, qh);
      } else {
        printf("%.7lf | %.7lf | %.7lf | %.7lf", x, aw, bl, qh);
      }
    }
  }
  return 0;
}

double AgnesiWitch(double x) { return 1 / (1 + x * x); }

double BernoulliLemniscate(double x) {
  double  result = 1 + 4 * x * x;
  result = sqrt(result) - x * x - 1;
  result = sqrt(result);
  return result;
}

double QuadraticHyperbola(double x) { return 1 / (x * x); }
