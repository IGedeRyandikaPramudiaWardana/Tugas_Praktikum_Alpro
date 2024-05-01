#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int n) {
    if (n >= 1)
        return n * factorial(n - 1);
    else
        return 1;
}

int main(int argc, char *argv[]) {
    double num, base, exponent, sum = 0, value;
    int count = 0, n;

    // Meminta input untuk operasi logaritma
    printf("Masukkan nilai untuk logaritma: ");
    scanf("%lf", &num);
    printf("2 log %.0f = %.2f\n", num, log10(num) / log10(2));
    printf("log %.0f = %.2f\n", num, log10(num));
    printf("ln %.0f = %.2f\n", num, log(num));

    // Meminta input untuk akar kuadrat
    printf("Masukkan nilai untuk akar kuadrat: ");
    scanf("%lf", &num);
    printf("akar %.0f = %.2f\n", num, sqrt(num));

    // Meminta input untuk operasi trigonometri
    printf("Masukkan derajat untuk sin: ");
    scanf("%lf", &num);
    printf("sin %.0f = %.2f\n", num, sin(num * M_PI / 180));

    printf("Masukkan derajat untuk cos: ");
    scanf("%lf", &num);
    printf("cos %.0f = %.2f\n", num, cos(num * M_PI / 180));

    printf("Masukkan derajat untuk tan: ");
    scanf("%lf", &num);
    printf("tan %.0f = %.2f\n", num, tan(num * M_PI / 180));

    // Meminta input untuk faktorial
    printf("Masukkan nilai untuk faktorial: ");
    scanf("%d", &n);
    printf("faktorial %d = %d\n", n, factorial(n));

    // Meminta input untuk sum dan avg
    printf("Masukkan serangkaian angka yang diakhiri dengan -1: \n");
    while(1) {
        scanf("%lf", &value);
        if(value == -1) break;
        sum += value;
        count++;
    }
    printf("hitung sum = %.2f\n", sum);
    printf("hitung avg = %.2f\n", sum / count);

    return 0;
}
