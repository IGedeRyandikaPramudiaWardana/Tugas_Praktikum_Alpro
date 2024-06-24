#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sisipkanTeksKeGambar(const char *inputGambar, const char *outputGambar, const char *teks) 
{
    FILE *flAsli, *flHasil;
    char header[54];
    char pixel[3];
    int lebar, tinggi, pad, panjangTeks, indeksTeks = 0, indeksBit = 0;

    flAsli = fopen(inputGambar, "rb");
    flHasil = fopen(outputGambar, "wb");

    fread(header, 1, 54, flAsli);
    fwrite(header, 1, 54, flHasil);

    lebar = *(int*)&header[18];
    tinggi = *(int*)&header[22];

    pad = (4 - (lebar * 3) % 4) % 4;

    panjangTeks = strlen(teks);

    int i, j, k;
    for (i = 0; i < tinggi; i++) 
    {
        for (j = 0; j < lebar; j++) 
        {
            fread(pixel, 1, 3, flAsli);
            for (k = 0; k < 3; k++) 
            {
                if (indeksTeks < panjangTeks) 
                {
                    pixel[k] = (pixel[k] & 0xFE) | ((teks[indeksTeks] >> indeksBit) & 0x01);
                    indeksBit++;
                    if (indeksBit == 8) 
                    {
                        indeksBit = 0;
                        indeksTeks++;
                    }
                }
            }
            fwrite(pixel, 1, 3, flHasil);
        }
        if (pad > 0) 
        {
            char padding[3];
            fread(padding, 1, pad, flAsli);
            fwrite(padding, 1, pad, flHasil);
        }
    }

    fclose(flAsli);
    fclose(flHasil);

    printf("Teks berhasil disembunyikan di dalam gambar\n");
}

void ekstrakTeksDariGambar(const char *inputGambar, const char *outputTeks) 
{
    FILE *flHasil = fopen(inputGambar, "rb");
    
    char header[54];
    fread(header, 1, 54, flHasil);

    int lebar = *(int*)&header[18];
    int tinggi = *(int*)&header[22];

    int pad = (4 - (lebar * 3) % 4) % 4;

    char pixel[3];
    char extractedTeks[256] = {0};
    int indeksTeks = 0;
    int indeksBit = 0;

    int i, j, k;
    for (i = 0; i < tinggi && indeksTeks < sizeof(extractedTeks) - 1; i++) 
    {
        for (j = 0; j < lebar && indeksTeks < sizeof(extractedTeks) - 1; j++) 
        {
            fread(pixel, 1, 3, flHasil);
            for (k = 0; k < 3 && indeksTeks < sizeof(extractedTeks) - 1; k++) 
            {
                extractedTeks[indeksTeks] |= (pixel[k] & 0x01) << indeksBit;
                indeksBit++;
                if (indeksBit == 8) 
                {
                    indeksBit = 0;
                    indeksTeks++;
                    if (indeksTeks < sizeof(extractedTeks) - 1) {
                        extractedTeks[indeksTeks] = 0;
                    }
                }
            }
        }
        if (pad > 0) 
        {
            char padding[3];
            fread(padding, 1, pad, flHasil);
        }
    }

    fclose(flHasil);

    FILE *flEkstrak = fopen(outputTeks, "w");
    
    fwrite(extractedTeks, 1, strlen(extractedTeks), flEkstrak);
    fclose(flEkstrak);

    printf("Teks yang di dalam gambar: %s\n", extractedTeks);
}

int main() 
{
    char inputGambar[256];
    char outputGambar[256];
    char inputTeks[256];
    char outputTeks[256];

    
		int pilihan;
		do{
			printf("Pilih operasi yang ingin dilakukan:\n");
		    printf("1. Sembunyikan teks ke dalam gambar\n");
		    printf("2. lihat teks di gambar\n");
		    printf("3. Keluar\n");
		    printf("Masukkan pilihan: ");
		    scanf("%d", &pilihan);
		
		    switch(pilihan) {
		        case 1:
		        {
		            printf("Masukkan nama file gambar input: ");
		            scanf("%s", inputGambar);
		
		            printf("Masukkan nama file gambar output: ");
		            scanf("%s", outputGambar);
		
		            printf("Masukkan nama file teks input: ");
		            scanf("%s", inputTeks);
		
		            FILE *flTeks = fopen(inputTeks, "r");
		            if (!flTeks) {
		                perror("Gagal membuka file teks input");
		                return 1;
		            }
		
		            char teks[256] = {0};
		            fread(teks, 1, sizeof(teks) - 1, flTeks);
		            fclose(flTeks);
		
		            sisipkanTeksKeGambar(inputGambar, outputGambar, teks);
		            break;
		        }
		        case 2:
		        {
		            printf("Masukkan nama file gambar output: ");
		            scanf("%s", inputGambar);
		
		            printf("Masukkan nama file teks output: ");
		            scanf("%s", outputTeks);
		
		            ekstrakTeksDariGambar(inputGambar, outputTeks);
		            break;
		        }
		        case 3:
		        	printf("Keluar\n");
		        	break;
		        default:
		            printf("Pilihan tidak valid");
		            return 1;
		    }
		}while (pilihan != 3);
    	
	
	return 0;
}


