#include <stdio.h>
#include <math.h>

int main() {
    int a, b, sum = 0, count = 0, input;
    double avg = 0.0, x, y;

    // Meminta input dari pengguna
    printf("Masukkan nilai untuk a: ");
    scanf("%d", &a);
    printf("Masukkan nilai untuk b: ");
    scanf("%d", &b);

    // Operasi dasar dengan input pengguna
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d\n", a, b, a / b);
    printf("%d div %d = %d\n", a, b, a / b);
    printf("%d mod %d = %d\n", a, b, a % b);
    printf("%d %% %d = %d\n", a, b, a % b);
    
    // Meminta input untuk operasi eksponensial
    printf("Masukkan nilai untuk x (basis) dan y (eksponen): ");
    scanf("%lf %lf", &x, &y);
    printf("%.0f ^ %.0f = %.0f\n", x, y, pow(x, y));
    
    // Operasi logaritma dan trigonometri dengan input pengguna
    printf("Masukkan nilai untuk logaritma: ");
    scanf("%lf", &x);
    printf("2 log %.0f = %.2f\n", x, log10(x) / log10(2));
    printf("log %.0f = %.2f\n", x, log10(x));
    printf("ln %.0f = %.2f\n", x, log(x));
    printf("Masukkan nilai untuk akar kuadrat: ");
    scanf("%lf", &x);
    printf("akar %.0f = %.2f\n", x, sqrt(x));
    
    // Operasi trigonometri
    printf("sin 90 = %.2f\n", sin(M_PI / 2));
    printf("cos 90 = %.2f\n", cos(M_PI / 2));
    printf("tan 45 = %.2f\n", tan(M_PI / 4));
    
    // Faktorial
    int factorial = 1, n;
    printf("Masukkan nilai untuk faktorial: ");
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    printf("faktorial %d = %d\n", n, factorial);

    // Menghitung sum dan avg
    printf("Masukkan serangkaian angka yang diakhiri dengan -1: \n");
    while(1) {
        scanf("%d", &input);
        if(input == -1) break;
        sum += input;
        count++;
    }
    avg = (double)sum / count;
    printf("hitung sum = %d\n", sum);
    printf("hitung avg = %.2f\n", avg);

    return 0;
}
