#include "math.h"
#include "stdio.h"
void chislo(int *chislo) {
    printf("chislo in function = %d\n", *chislo);
    *chislo = 5;
    printf("chislo in function = %d\n", *chislo);
}


int main() {
    int x = 10;
    printf("sin(30) = %f, sin(3,1415/6) = %f\n", sin(30), sin(3.1415926535/6));
    printf("arcsin() = %f, Pi/6 = %f", asin(0.5), 3.141592/6);
    printf("4 = %f\n", sqrt(4));
}
