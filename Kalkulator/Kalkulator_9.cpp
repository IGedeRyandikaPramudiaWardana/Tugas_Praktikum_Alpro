#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Fungsi untuk menghitung faktorial
int factorial(int n) 
{
    if (n <= 1) return 1;
    else return n * factorial(n - 1);
}

// Fungsi utama
int main(int argc, char *argv[]) 
{
    
	if (argc != 3) 
	{
        printf("Penggunaan: %s <angka1> <perintah> <angka2>\n", argv[0]);
        return 1;
    }

    // Mengkonversi argumen pertama dan ketiga ke integer
    int angka1 = atoi(argv[1]);
    int angka2 = atoi(argv[3]);
    

    // Memilih operasi berdasarkan perintah
	
	if (strcmp(argv[2], "log2") == 0) 
	{
        printf("2 log %d = %.2f\n", angka2, log10(angka2) / log10(2));
    } 
	
	else if (strcmp(argv[2], "akar") == 0) 
	{
        printf("Akar %d = %.0f\n", angka2, sqrt(angka2));
    } 
	
	else if (strcmp(argv[2], "sin") == 0) 
	{
        printf("sin %d = %.2f\n", angka2, sin(angka2 * M_PI / 180));
    } 
	
	else if (strcmp(argv[2], "cos") == 0) 
	{
        printf("cos %d = %.2f\n", angka2, cos(angka2 * M_PI / 180));
    } 
	
	else if (strcmp(argv[2], "tan") == 0) 
	{
        printf("tan %d = %.2f\n", angka2, tan(angka2 * M_PI / 180));
    } 
	
	else if (strcmp(argv[2], "log") == 0) 
	{
        printf("log %d = %.2f\n", angka2, log10(angka2));
    } 
	
	else if (strcmp(argv[2], "ln") == 0) 
	{
        printf("ln %d = %.2f\n", angka2, log(angka2));
    } 
	
	else if (strcmp(argv[2], "faktorial") == 0) 
	{
        printf("Factorial %d = %d\n", angka2, factorial(angka2));
    } 
	
	else if (strcmp(argv[2], "jumlah") == 0) 
	{
        printf("Sum %d, %d, %d = %d\n", angka1, angka1 + 5, angka1 + 10, angka1 + angka1 + 5 + angka1 + 10);
    } 
	
	else if (strcmp(argv[2], "rata-rata") == 0) 
	{
        printf("Average %d, %d, %d = %.2f\n", angka1, angka1 + 5, angka1 + 10, (angka1 + angka1 + 5 + angka1 + 10) / 3.0);
    } 
	
	else 
	{
        printf("Perintah tidak dikenali.\n");
    }

    return 0;
}
