#include <stdio.h>

int main() {
    FILE *fp;
    char *filename = "Test1.csv";

    // Membuka file untuk ditulis
    fp = fopen(filename, "w+");
    if (fp == NULL) {
        printf("Gagal membuka file %s\n", filename);
        return -1;
    }

    // Menulis data ke dalam file CSV
    fprintf(fp, "Nama,Umur,Alamat\n"); // Header CSV
    fprintf(fp, "Alice,30,Jakarta\n");
    fprintf(fp, "Bob,25,Bandung\n");
    fprintf(fp, "Charlie,35,Surabaya\n");

    // Menutup file
    fclose(fp);
    printf("File %s telah berhasil dibuat.\n", filename);

    return 0;
}
