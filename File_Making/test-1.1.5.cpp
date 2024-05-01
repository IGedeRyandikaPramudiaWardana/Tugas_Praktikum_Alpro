#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mendefinisikan struct untuk menyimpan data pengguna
typedef struct {
    char nama[50];
    int umur;
    char alamat[100];
} DataPengguna;

// Fungsi untuk menambahkan data baru
void tambahData(char *filename) {
    DataPengguna pengguna;
    printf("Masukkan nama: ");
    scanf("%49s", pengguna.nama); // Membaca nama
    printf("Masukkan umur: ");
    scanf("%d", &pengguna.umur); // Membaca umur
    printf("Masukkan alamat: ");
    scanf("%99s", pengguna.alamat); // Membaca alamat

    FILE *fp = fopen(filename, "a"); // Membuka file dalam mode append
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

    // Menulis data ke file
    fprintf(fp, "%s,%d,%s\n", pengguna.nama, pengguna.umur, pengguna.alamat);
    fclose(fp);
}

// Fungsi untuk mengedit data
void editData(char *filename) {
    // Kode untuk mengedit data belum diberikan
    printf("Fungsi editData belum diimplementasikan.\n");
}

// Fungsi untuk menampilkan data
void tampilkanData(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

    DataPengguna pengguna;
    char line[200];
    printf("Data yang tersimpan dalam file %s:\n", filename);
    printf("%-20s %-5s %-30s\n", "Nama", "Umur", "Alamat"); // Header tabel

    // Membaca dan menampilkan data
    while (fscanf(fp, "%49[^,],%d,%99[^\n]\n", pengguna.nama, &pengguna.umur, pengguna.alamat) == 3) {
        printf("%-20s %-5d %-30s\n", pengguna.nama, pengguna.umur, pengguna.alamat);
    }

    fclose(fp);
}

int main() {
    char *filename = "output2.csv";
    int pilihan;
	do
	{
	    printf("Pilih operasi:\n");
	    printf("1. Tambah data baru\n");
	    printf("2. Edit data\n");
	    printf("3. Tampilkan data\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &pilihan);
	
	    switch (pilihan) {
	        case 1:
	            tambahData(filename);
	            break;
	        case 2:
	            editData(filename);
	            break;
	        case 3:
	            tampilkanData(filename);
	            break;
	        default:
	            printf("Pilihan tidak valid.\n");
	    }
	} 
	while (pilihan != 4);
	
    return 0;
}
