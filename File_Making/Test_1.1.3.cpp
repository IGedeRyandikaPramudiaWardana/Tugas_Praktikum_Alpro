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
    FILE *fp = fopen(filename, "a"); // Membuka file dalam mode append
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

    DataPengguna pengguna;
    printf("Masukkan nama, umur, dan alamat untuk data baru:\n");
    printf("Nama: ");
    scanf("%49s", pengguna.nama);
    printf("Umur: ");
    scanf("%d", &pengguna.umur);
    printf("Alamat: ");
    scanf(" %[^\n]s", pengguna.alamat);

    fprintf(fp, "%s,%d,%s\n", pengguna.nama, pengguna.umur, pengguna.alamat);
    fclose(fp);
}

// Fungsi untuk menghapus data
void hapusData(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

    DataPengguna pengguna, *dataSementara;
    int count = 0, idxHapus, i = 0;
    char line[200];

    // Menghitung jumlah baris/data
    while (fgets(line, sizeof(line), fp)) {
        count++;
    }
    rewind(fp); // Mengembalikan pointer ke awal file

    // Alokasi memori untuk menyimpan data sementara
    dataSementara = (DataPengguna *)malloc(count * sizeof(DataPengguna));

    // Membaca dan menyimpan data ke dalam array sementara
    while (fscanf(fp, "%49[^,],%d,%99[^\n]\n", pengguna.nama, &pengguna.umur, pengguna.alamat) == 3) {
        dataSementara[i++] = pengguna;
    }
    fclose(fp);

    // Meminta pengguna memilih data yang ingin dihapus
    printf("Masukkan indeks data yang ingin dihapus (1 sampai %d): ", count);
    scanf("%d", &idxHapus);
    idxHapus--; // Mengubah ke indeks array

    // Membuka file untuk ditulis ulang
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        exit(-1);
    }

    // Menulis header
    fprintf(fp, "Nama,Umur,Alamat\n");

    // Menulis kembali data kecuali data yang dihapus
    for (i = 0; i < count; i++) {
        if (i != idxHapus) {
            fprintf(fp, "%s,%d,%s\n", dataSementara[i].nama, dataSementara[i].umur, dataSementara[i].alamat);
        }
    }

    // Membersihkan memori dan menutup file
    free(dataSementara);
    fclose(fp);
}

int main() {
    char *filename = "output.csv";
    int pilihan;

    printf("Pilih operasi:\n");
    printf("1. Tambah data baru\n");
    printf("2. Hapus data\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            tambahData(filename);
            break;
        case 2:
            hapusData(filename);
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }

    return 0;
}
