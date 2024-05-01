#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Penggunaan: %s <angka1> <operasi> <angka2> \n", argv[0]);
        return 1;
    }

    int angka1 = atoi(argv[1]);
    int angka2 = atoi(argv[3]);
    if (strcmp(argv[2], "tambah") == 0) {
        printf("Hasil penjumlahan: %d\n", angka1 + angka2);
    } else if (strcmp(argv[2], "kurang") == 0) {
        printf("Hasil pengurangan: %d\n", angka1 - angka2);
    } else {
        printf("Operasi tidak dikenali.\n");
    }

    return 0;
}
