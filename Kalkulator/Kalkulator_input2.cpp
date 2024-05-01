#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int factorial(int n) {
    if (n >= 1)
        return n * factorial(n - 1);
    else
        return 1;
}

int main() {
    char input[50];
    double num1, num2;
    int n;

    printf("Masukkan operasi (contoh: 'hitung 10 + 5'): ");
    fgets(input, 50, stdin); // Membaca string input

    // Memeriksa dan mengeksekusi operasi berdasarkan input
    if (sscanf(input, "hitung %lf + %lf", &num1, &num2) == 2) {
        printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
    } else if (sscanf(input, "hitung %lf - %lf", &num1, &num2) == 2) {
        printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
    } else if (sscanf(input, "hitung %lf * %lf", &num1, &num2) == 2) {
        printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
    } else if (sscanf(input, "hitung %lf / %lf", &num1, &num2) == 2) {
        printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
    } else if (sscanf(input, "hitung %d ^ %d", &n, &n) == 2) {
        printf("%d ^ %d = %.0f\n", n, n, pow(n, n));
    } else if (strstr(input, "log") && sscanf(input, "hitung %lf log %lf", &num1, &num2) == 2) {
        printf("log %.0f = %.2f\n", num2, log10(num2) / log10(num1));
    } else if (strstr(input, "akar") && sscanf(input, "hitung akar %lf", &num1) == 1) {
        printf("akar %.0f = %.2f\n", num1, sqrt(num1));
    } else if (strstr(input, "sin") && sscanf(input, "hitung sin %lf", &num1) == 1) {
        printf("sin %.0f = %.2f\n", num1, sin(num1 * M_PI / 180));
    } else if (strstr(input, "cos") && sscanf(input, "hitung cos %lf", &num1) == 1) {
        printf("cos %.0f = %.2f\n", num1, cos(num1 * M_PI / 180));
    } else if (strstr(input, "tan") && sscanf(input, "hitung tan %lf", &num1) == 1) {
        printf("tan %.0f = %.2f\n", num1, tan(num1 * M_PI / 180));
    } else if (strstr(input, "faktorial") && sscanf(input, "hitung faktorial %d", &n) == 1) {
        printf("faktorial %d = %d\n", n, factorial(n));
    } else {
        printf("Operasi tidak dikenali.\n");
    }

    return 0;
}
