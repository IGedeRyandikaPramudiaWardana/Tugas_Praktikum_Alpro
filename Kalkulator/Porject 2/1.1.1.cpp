#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nim[20];
    char nama[100];
    int tahun_masuk;
    float ipk;
} Mahasiswa;

void tambahData(Mahasiswa **data, int *jumlah_data);
void hapusData(Mahasiswa **data, int *jumlah_data);
void ubahData(Mahasiswa *data, int jumlah_data);
void tampilkanData(Mahasiswa *data, int jumlah_data);
void simpanData(Mahasiswa *data, int jumlah_data);
void cariData(Mahasiswa *data, int jumlah_data);
void urutkanIPK(Mahasiswa *data, int jumlah_data);

int main() {
    Mahasiswa *dataMahasiswa = NULL;
    int jumlah_data = 0;
    int pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Data\n");
        printf("2. Hapus Data\n");
        printf("3. Ubah Data\n");
        printf("4. Tampilkan Data\n");
        printf("5. Simpan Data ke CSV\n");
        printf("6. Cari Data\n");
        printf("7. Urutkan Data Berdasarkan IPK\n");
        printf("8. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // Menghilangkan newline karakter

        switch (pilihan) {
            case 1:
                tambahData(&dataMahasiswa, &jumlah_data);
                break;
            case 2:
                hapusData(&dataMahasiswa, &jumlah_data);
                break;
            case 3:
                ubahData(dataMahasiswa, jumlah_data);
                break;
            case 4:
                tampilkanData(dataMahasiswa, jumlah_data);
                break;
            case 5:
                simpanData(dataMahasiswa, jumlah_data);
                break;
            case 6:
                cariData(dataMahasiswa, jumlah_data);
                break;
            case 7:
                urutkanIPK(dataMahasiswa, jumlah_data);
                break;
            case 8:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 8);

    // Bebaskan memori
    free(dataMahasiswa);

    return 0;
}

// Implementasi fungsi tambahData, hapusData, ubahData, tampilkanData, simpanData, cariData, dan urutkanIPK di sini

