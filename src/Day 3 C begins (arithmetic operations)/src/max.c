#include <stdio.h>

int max(int a, int b);

int main(void) {
    int a = 0;
    int b = 0;
    char term = 0;
    if (3 != scanf("%d %d%c", &a, &b, &term) || term != '\n') {
        printf("n/a");
    } else {
        printf("%d", max(a, b));
    }
    return 0;
}

int max(int a, int b) { return a > b ? a : b; }
