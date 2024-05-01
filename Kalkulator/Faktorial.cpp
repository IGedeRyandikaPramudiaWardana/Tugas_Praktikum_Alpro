#include <stdio.h>

unsigned long long faktorial(unsigned int n) {
    if (n == 0) return 1; // Basis rekursi: faktorial dari 0 adalah 1
    return n * faktorial(n - 1); // Langkah rekursi
}

int main() {
    unsigned int angka;
    printf("Masukkan angka: ");
    scanf("%u", &angka);
    printf("Faktorial dari %u adalah %llu\n", angka, faktorial(angka));
    return 0;
}
