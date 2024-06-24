#include "stdio.h"

int main()
{
	FILE *flAsli, *flHasil;
	char buff[256];
	char buffWarna[3];
	//int buffInt;
	int temp;
	int lebar;
	int tinggi;
	int pad;
	
	flAsli = fopen("Yuta.bmp", "rb");
	flHasil = fopen("YutaNegatif.bmp", "wb");
	
	fread(buff, 1, 54, flAsli);
	fwrite(buff, 1, 54, flHasil);
	
	fseek(flAsli, 18, SEEK_SET);
	fread(&lebar, 4, 1, flAsli);
	fread(&tinggi, 4, 1, flAsli);
	pad = 3 - ((lebar * 3) %4) %4;
	
	for(int i=0; i<tinggi; i++)
	{
		for(int j=0; j<lebar; j++)
		{
			if(fread(buffWarna, 1, 3, flAsli))
			{
				temp = buffWarna[0];
				buffWarna[0] = buffWarna[1];
				buffWarna[1] = buffWarna[2];
				buffWarna[2] = temp;
				fwrite(buffWarna, 1, 3, flHasil);
			}
			if (pad>0)
			{
				fread(buffWarna, 1, pad, flAsli);
				fwrite(buffWarna, 1, pad, flHasil);
			}
		}
	}
	
	fclose(flAsli);
	fclose(flHasil);
	
	return(0);
}