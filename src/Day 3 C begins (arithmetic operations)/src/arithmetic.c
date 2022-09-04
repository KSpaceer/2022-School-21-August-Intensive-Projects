#include <stdio.h>

int sum(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main(void) {
    int a = 0;
    int b = 0;
    char term = 0;
    if (3 != scanf("%d %d%c", &a, &b, &term) || term != '\n') {
        printf("n/a");
    } else {
        int result = sum(a, b);
        printf("%d ", result);
        result = sub(a, b);
        printf("%d ", result);
        result = mul(a, b);
        printf("%d ", result);
        if (0 == b) {
            printf("n/a");
        } else {
            result = div(a, b);
            printf("%d", result);
        }
    }
    return 0;
}

int sum(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }
