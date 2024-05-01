#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int sum(int a, int b, int c) {
    return a + b + c;
}

float avg(int a, int b, int c) {
    return (float)(a + b + c) / 3;
}

int main(int argc, char *argv[]) {
    printf("10 + 5 = %d\n", 10 + 5);
    printf("10 - 5 = %d\n", 10 - 5);
    printf("10 * 5 = %d\n", 10 * 5);
    printf("10 div 5 = %d\n", 10 / 5);
    printf("10 mod 5 = %d\n", 10 % 5);
    printf("10 %% 5 = %d remainder %d\n", 10 / 5, 10 % 5);
    printf("10 ^ 5 = %.0f\n", pow(10, 5));
    printf("2 log 100 = %.2f\n", log10(100) / log10(2));
    printf("Akar 100 = %.0f\n", sqrt(100));
    printf("sin 90 = %.0f\n", sin(M_PI / 2));
    printf("cos 90 = %.0f\n", cos(M_PI / 2));
    printf("tan 45 = %.0f\n", tan(M_PI / 4));
    printf("log 100 = %.2f\n", log10(100));
    printf("ln 100 = %.2f\n", log(100));
    printf("Factorial 6 = %d\n", factorial(6));
    printf("Sum 60, 65, 70 = %d\n", sum(60, 65, 70));
    printf("Average 60, 65, 70 = %.2f\n", avg(60, 65, 70));

    return 0;
}
