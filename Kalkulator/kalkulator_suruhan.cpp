#include <stdio.h>
#include <math.h>

int main() {
    int sum = 0, count = 0, input;
    double avg = 0.0;

    // Operasi dasar
    printf("10 + 5 = %d\n", 10 + 5);
    printf("10 - 5 = %d\n", 10 - 5);
    printf("10 * 5 = %d\n", 10 * 5);
    printf("10 / 5 = %d\n", 10 / 5);
    printf("10 div 5 = %d\n", 10 / 5);
    printf("10 mod 5 = %d\n", 10 % 5);
    printf("10 %% 5 = %d\n", 10 % 5);
    printf("10 ^ 5 = %.0f\n", pow(10, 5));
    
    // Operasi logaritma dan trigonometri
    printf("2 log 100 = %.2f\n", log10(100) / log10(2));
    printf("akar 100 = %.2f\n", sqrt(100));
    printf("sin 90 = %.2f\n", sin(M_PI / 2));
    printf("cos 90 = %.2f\n", cos(M_PI / 2));
    printf("tan 45 = %.2f\n", tan(M_PI / 4));
    printf("log 100 = %.2f\n", log10(100));
    printf("ln 100 = %.2f\n", log(100));
    
    // Faktorial
    int factorial = 1;
    for(int i = 1; i <= 5; ++i) {
        factorial *= i;
    }
    printf("faktorial 5 = %d\n", factorial);

    // Menghitung sum dan avg
    // Anda dapat menambahkan angka ke dalam array di bawah ini
    int numbers[] = {60, 65, 70, 0}; // 0 sebagai penanda akhir array
    for(int i = 0; numbers[i] != 0; i++) {
        sum += numbers[i];
        count++;
    }
    avg = (double)sum / count;
    printf("hitung sum = %d\n", sum);
    printf("hitung avg = %.2f\n", avg);

    return 0;
}
