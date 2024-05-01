#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// angka1 perintah angka2
	// perintah angka1 angka2
	
	int x = atoi(argv[1]);
	int y = atoi(argv[3]);
	
	
	if(strcmp(argv[2], "+") == 0)
	{
		printf("Hasil penjumlahan = %d\n", x + y);
	}
	
	else if(strcmp(argv[2], "-") == 0)
	{
		printf("Hasil Pengurangan = %d\n", x - y);
	}
	
	else if(strcmp(argv[2], "*") == 0)
	{
		printf("Hasil Perkalian = %d\n", x * y);
	}
	
	else if(strcmp(argv[2], "/") == 0)
	{
		printf("Hasil Pembagian = %d\n", x / y);
	}
	
	else if(strcmp(argv[2], "pangkat") == 0)
	{
		int hasil = pow(x, y);
		printf("Hasil pangkat = %d\n", hasil);
	}
	
	else if(strcmp(argv[2], "bagi") == 0)
	{
		printf("Hasil bagi sisa = %d sisa %d\n", x / y, x % y);
	}
	
	else if (strcmp(argv[2], "mod") == 0) 
	{
        printf("Hasil mod atau sisa adalah = %d\n", x % y);
    } 
	
	else
	{
		printf("Operasi tidak dikenali.\n");
	}
	
	return 0;
}