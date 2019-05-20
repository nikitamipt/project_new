
#include "stdio.h"

int main() {
    int x = 10;
    (x + 2)%3 > 0 ? printf("%d", (x+=2%3)) : printf("B");
    printf("%d", (-5)%2);
    }
