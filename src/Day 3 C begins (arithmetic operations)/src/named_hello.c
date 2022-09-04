#include <stdio.h>

int main(void) {
    int name = 0;
    char term = 0;
    if (2 == scanf("%d%c", &name, &term) && (term == '\n' || term == ' ')) {
        printf("Hello, %d!", name);
    }
    return 0;
}
