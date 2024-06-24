#include "stdio.h"

int main()
{
	FILE *flAsli, *flHasil;
	char buff[256];
	int buffInt;
	
	flAsli = fopen("Denji.bmp", "rb");
	flHasil = fopen("DenjiNegatif.bmp", "wb");
	
	fread(buff, 1, 54, flAsli);
	fwrite(buff, 1, 54, flHasil);
	
	while (fread(&buffInt, 4, 1, flAsli))
	{
		buffInt = ~buffInt;
		fwrite(&buffInt, 4, 1, flHasil);
	}
	
	fclose(flAsli);
	fclose(flHasil);
	
	return(0);
}