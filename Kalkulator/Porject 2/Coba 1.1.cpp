#include <stdio.h>

int main() {
    // Membuat pointer ke file
    char nama[25];
    FILE *filePointer;

    // Membuka file untuk ditulis (mode "w")
    filePointer = fopen("coba 1.1.txt", "w");

    // Memeriksa apakah file berhasil dibuka
    if (filePointer == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    // Menulis data ke dalam file
    fgets(nama, sizeof(nama), filePointer);
    printf("%s", nama);
    fgets(nama, sizeof(nama), filePointer);
    printf("%s", nama);
   // fprintf(filePointer, "Hello, dunia!\n");
   // fprintf(filePointer, "Ini adalah contoh data yang disimpan.\n");

    // Menutup file setelah selesai
    fclose(filePointer);

    printf("Data berhasil disimpan ke dalam file 'data.txt'.\n");

    return 0;
}
