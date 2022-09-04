#include <math.h>
#include <stdio.h>

double ImportantFunction(double x);

int main(void) {
    double x = 0.;
    char term = 0;
    if (2 != scanf("%lf%c", &x, &term) || term != '\n') {
        printf("n/a");
    } else if (x == 0.0 || x < 0.) {
        printf("n/a");
    } else {
        double y = ImportantFunction(x);
        printf("%.1lf", y);
    }
}

double ImportantFunction(double x) {
    double y = 0.;
    double temp = 0.;
    y = 0.007 * pow(x, 4.);
    temp = 22.8 * cbrt(x) - 1000.;
    temp *= x;
    temp += 3.;
    temp /= x * x / 2;
    y += temp;
    temp = 10. + x;
    temp = pow(temp, 2. / x);
    y -= x * temp;
    y -= 1.01;
    return y;
}
