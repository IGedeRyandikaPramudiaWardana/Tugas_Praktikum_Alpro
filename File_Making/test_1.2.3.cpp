#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi struct untuk menyimpan data mahasiswa
typedef struct {
    char nama[50];
    char namaLengkap[100];
    char NIM[20];
    char alamat[255];
} Mahasiswa;

// Prototipe fungsi
void tambahData(Mahasiswa **data, int *jumlahData);
void tampilkanData(Mahasiswa *data, int jumlahData);
int cariIndex(Mahasiswa *data, int jumlahData, char *NIM);
void editData(Mahasiswa *data, int index);
void hapusData(Mahasiswa **data, int *jumlahData, int index);

// Implementasi fungsi tambahData
void tambahData(Mahasiswa **data, int *jumlahData) {
    // Alokasi memori untuk data baru
    *data = realloc(*data, (*jumlahData + 1) * sizeof(Mahasiswa));
    if (*data == NULL) {
        printf("Alokasi memori gagal.\n");
        exit(1);
    }

    // Input data mahasiswa baru
    printf("Masukkan nama: ");
    gets((*data)[*jumlahData].nama);
    printf("Masukkan nama lengkap: ");
    gets((*data)[*jumlahData].namaLengkap);
    printf("Masukkan NIM: ");
    gets((*data)[*jumlahData].NIM);
    printf("Masukkan alamat: ");
    gets((*data)[*jumlahData].alamat);

    // Menambah jumlah data
    (*jumlahData)++;
}

// Implementasi fungsi tampilkanData
void tampilkanData(Mahasiswa *data, int jumlahData) {
    printf("\nData Mahasiswa:\n");
    for (int i = 0; i < jumlahData; i++) {
        printf("Nama: %s\n", data[i].nama);
        printf("Nama Lengkap: %s\n", data[i].namaLengkap);
        printf("NIM: %s\n", data[i].NIM);
        printf("Alamat: %s\n\n", data[i].alamat);
    }
}

// Implementasi fungsi cariIndex
int cariIndex(Mahasiswa *data, int jumlahData, char *NIM) {
    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(data[i].NIM, NIM) == 0) {
            return i;
        }
    }
    return -1; // Jika tidak ditemukan
}

// Implementasi fungsi editData
void editData(Mahasiswa *data, int index) {
    int pilihan;
    printf("Pilih data yang ingin diedit:\n");
    printf("1. Nama\n");
    printf("2. Nama Lengkap\n");
    printf("3. NIM\n");
    printf("4. Alamat\n");
    printf("Masukkan pilihan Anda: ");
    scanf("%d", &pilihan);
    getchar(); // Menghilangkan newline karakter

    switch (pilihan) {
        case 1:
            printf("Masukkan nama baru: ");
            gets(data[index].nama);
            break;
        case 2:
            printf("Masukkan nama lengkap baru: ");
            gets(data[index].namaLengkap);
            break;
        case 3:
            printf("Masukkan NIM baru: ");
            gets(data[index].NIM);
            break;
        case 4:
            printf("Masukkan alamat baru: ");
            gets(data[index].alamat);
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
}

// Implementasi fungsi hapusData
void hapusData(Mahasiswa **data, int *jumlahData, int index) {
    // Menggeser semua data setelah index ke kiri
    for (int i = index; i < *jumlahData - 1; i++) {
        (*data)[i] = (*data)[i + 1];
    }

    // Mengurangi jumlah data dan realokasi memori
    *jumlahData -= 1;
    *data = realloc(*data, (*jumlahData) * sizeof(Mahasiswa));
    if (*data == NULL && *jumlahData > 0) {
        printf("Alokasi memori gagal.\n");
        exit(1);
    }
}

// Fungsi utama
int main() {
    Mahasiswa *dataMahasiswa = NULL;
    int jumlahData = 0;
    int pilihan;
    char NIM[20];

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Data Mahasiswa\n");
        printf("2. Tampilkan Data Mahasiswa\n");
        printf("3. Edit Data Mahasiswa\n");
        printf("4. Hapus Data Mahasiswa\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar(); // Menghilangkan newline karakter

        switch (pilihan) {
            case 1:
                tambahData(&dataMahasiswa, &jumlahData);
                break;
            case 2:
                tampilkanData(dataMahasiswa, jumlahData);
                break;
            case 3:
                printf("Masukkan NIM Mahasiswa yang akan diedit: ");
                gets(NIM);
                int index = cariIndex(dataMahasiswa, jumlahData, NIM);
                if (index != -1) {
                    editData(dataMahasiswa, index);
                } else {
                    printf("Data tidak ditemukan.\n");
                }
                break;
            case 4:
                printf("Masukkan NIM Mahasiswa yang akan dihapus: ");
                gets(NIM);
                index = cariIndex(dataMahasiswa, jumlahData, NIM);
                if (index != -1) {
                    hapusData(&dataMahasiswa, &jumlahData, index);
                } else {
                    printf("Data tidak ditemukan.\n");
                }
                break;
            case 5:
                printf("Terima kasih telah menggunakan program ini.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 5);

    // Bebaskan memori
    free(dataMahasiswa);
    return 0;
}
