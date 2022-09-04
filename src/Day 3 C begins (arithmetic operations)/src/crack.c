#include <stdio.h>

int main(void) {
    double x = 0.;
    double y = 0.;
    char term = 0;
    if (3 != scanf("%lf %lf%c", &x, &y, &term) || term != '\n') {
        printf("n/a");
    } else if ((x * x + y * y) < 25.) {
        printf("GOTCHA");
    } else {
        printf("MISS");
    }
    return 0;
}
