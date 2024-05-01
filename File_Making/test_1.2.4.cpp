#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	long int nim;
	char nama[50];
	int umur;
	char alamat[100];
} Mahasiswa;

void tambahData(char *filename)
{
	Mahasiswa mahasiswa;
	printf("Masukkan nim: ");
	scanf("%d", &mahasiswa.nim);
	getchar();
	
	printf("Masukkan nama mahasiswa: ");
	fgets(mahasiswa.nama, 50, stdin);
	mahasiswa.nama[strcspn(mahasiswa.nama, "\n")] = 0;
	
	printf("Masukkan umur: ");
	scanf("%d", &mahasiswa.umur);
	getchar();
	
	printf("Masukkan alamat: ");
	fgets(mahasiswa.alamat, 100, stdin);
	mahasiswa.alamat[strcspn(mahasiswa.alamat, "\n")] = 0;
	
	FILE *fp = fopen(filename, "a");
	if(fp == NULL)
	{
		printf("Gagal membuka file %s\n", filename);
		exit(-1);
	}
	
	fprintf(fp, "%d, %s, %d, %s\n", mahasiswa.nim, mahasiswa.nama, mahasiswa.umur, mahasiswa.alamat);
	fclose(fp);
}

void tampilkanData(char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
	{
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

	Mahasiswa mahasiswa;
    printf("Data yang tersimpan dalam file %s:\n", filename);
    printf("NIM, Nama, Umur, Alamat\n"); // Header tabel

    // Membaca dan menampilkan data
    while (fscanf(fp, "%49[^,],%d,%99[^\n]\n", &mahasiswa.nim, mahasiswa.nama, &mahasiswa.umur, mahasiswa.alamat) == 4) 
	{
        printf("%d, %s, %d, %s\n", mahasiswa.nim, mahasiswa.nama, mahasiswa.umur, mahasiswa.alamat);
    }

    fclose(fp);
}


int main() {
    char *filename = "output5.csv";
    int pilihan;
	do
	{
	    printf("Pilih operasi:\n");
	    printf("1. Tambah data baru\n");
//	    printf("2. Edit data\n");
	    printf("2. Tampilkan data\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &pilihan);
	    getchar();
	
	    switch (pilihan) {
	        case 1:
	            tambahData(filename);
	            break;
/*	        case 2:
	            editData(filename);
	            break;
*/	        case 2:
	            tampilkanData(filename);
	            break;
	        default:
	            printf("Pilihan tidak valid.\n");
	    }
	} 
	while (pilihan != 3);
	
    return 0;
}
