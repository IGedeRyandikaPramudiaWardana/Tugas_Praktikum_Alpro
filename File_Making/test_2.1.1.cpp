#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Mahasiswa
{
	public:
		char nama[100];
		char NIM[15];
		char umur[4];
		char fakultas[100];
		char jurusan[100];
		char prodi[50];
		char TempatTinggal[200];
		char AsalKota[100];
};

void tambahData(char *filename)
{
	Mahasiswa mahasiswa;
	
	printf("Nama mahasiswa: ");
	gets(mahasiswa.nama);
	
	printf("NIM: ");
	gets(mahasiswa.NIM);
	
	printf("Umur: ");
	gets(mahasiswa.umur);
	
	printf("Fakultas: ");
	gets(mahasiswa.fakultas);
	
	printf("Jurusan: ");
	gets(mahasiswa.jurusan);
	
	printf("Program Studi: ");
	gets(mahasiswa.prodi);
	
	printf("Tempat tinggal: ");
	gets(mahasiswa.TempatTinggal);
	
	printf("Asal Kota: ");
	gets(mahasiswa.AsalKota);
	
	printf("\n\n");
	
	FILE *fp = fopen(filename, "a");
	if(fp == NULL)
	{
		printf("Gagal membuka file %s\n", filename);
		exit(-1);
	}
	
	fprintf(fp, "%s, %s, %s, %s, %s, %s, %s, %s\n", 
	mahasiswa.nama, mahasiswa.NIM, mahasiswa.umur, mahasiswa.fakultas, mahasiswa.jurusan, mahasiswa.prodi, 
	mahasiswa.TempatTinggal, mahasiswa.AsalKota);
	fclose(fp);
}


void tampilkanData(char *filename)
{
	printf("# Data Mahasiswa # \n");
	printf("================== \n");
	
	FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
	{
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

	Mahasiswa mahasiswa;
    //printf("Data yang tersimpan dalam file %s:\n", filename);
    printf("Nama, NIM, Umur, Fakultas, Jurusan, Prodi, Tempat Tinggal, Asal Kota\n"); // Header tabel

    // Membaca dan menampilkan data
    while (fscanf(fp, "%99[^,], %14[^,], %3[^,], %99[^,], %99[^,], %49[^,], %199[^,], %99[^,]\n", mahasiswa.nama, mahasiswa.NIM, mahasiswa.umur, mahasiswa.fakultas, mahasiswa.jurusan, mahasiswa.prodi, mahasiswa.TempatTinggal, mahasiswa.AsalKota) == 8) 
	{
        printf("%s, %s, %s, %s, %s, %s, %s, %s, \n", mahasiswa.nama, mahasiswa.NIM, mahasiswa.umur, mahasiswa.fakultas, mahasiswa.jurusan, mahasiswa.prodi, mahasiswa.TempatTinggal, mahasiswa.AsalKota);
    }
    
    printf("\n\n");

    fclose(fp);
}


int main()
{
	char *filename = "output8.csv";
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