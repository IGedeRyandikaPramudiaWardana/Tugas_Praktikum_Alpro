#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char** argv)
{
	FILE *flAsli, *flHasil;
	char buff[256];
	int buffInt;
	char nmFileAsli[256];
	char nmFileHasil[256];
	unsigned char pesan[256];
	
	printf("Masukkan namafile format bmp (tanpa menuliskan .bmp): ");
	scanf("%s", &nmFileAsli);
	//strcat(nmFileAsli, ".bmp");
	while(getchar() != '\n');
	strcat(nmFileAsli, ".bmp");
	
	printf("Masukkan nama file Output bmp (tanpa menuliskan .bmp): ");
	scanf("%s", &nmFileHasil);
	while(getchar() != '\n');
	strcat(nmFileHasil, ".bmp");
	
	flAsli = fopen(nmFileAsli, "rb");
	if(flAsli == NULL)
	{
		printf("Error: File sumber tidak ditemukan.\n");
		fclose(flAsli);
		return 1;
	}
	
	
	flHasil = fopen(nmFileHasil, "wb");
	if(flHasil == NULL)
	{
		printf("Error: tidak ada file yang dituju.");
		fclose(flAsli);
		return 1;
	}
	
	fread(buff, 1, 54, flAsli);
	fwrite(buff, 1, 54, flHasil);
	
	
	
	return 0;
}