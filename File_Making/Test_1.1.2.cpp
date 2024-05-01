#include <stdio.h>
#include <string.h>

// Mendefinisikan struct untuk menyimpan data pengguna
typedef struct {
    char nama[50];
    int umur;
    char alamat[100];
} DataPengguna;

int main() {
    FILE *fp;
    char *filename = "output.csv";
    DataPengguna pengguna;
    
    // Membuka file untuk ditulis
    fp = fopen(filename, "w+");
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        return -1;
    }

    // Menulis header ke dalam file CSV
    fprintf(fp, "Nama,Umur,Alamat\n");

    // Meminta input dari user
    printf("Masukkan nama, umur, dan alamat. Ketik 'selesai' untuk nama ketika ingin berhenti.\n");
    while(1) {
        printf("Nama: ");
        scanf("%49s", pengguna.nama); // Membaca maksimal 49 karakter untuk nama
        if(strcmp(pengguna.nama, "selesai") == 0) {
            break;
        }
        printf("Umur: ");
        scanf("%d", &pengguna.umur); // Membaca umur
        printf("Alamat: ");
        scanf(" %[^\n]s", pengguna.alamat); // Membaca alamat dengan spasi

        // Menulis data ke dalam file CSV
        fprintf(fp, "%s,%d,%s\n", pengguna.nama, pengguna.umur, pengguna.alamat);
    }

    // Menutup file
    fclose(fp);
    printf("File %s telah berhasil dibuat dengan data yang diinput.\n", filename);

    return 0;
}
