#include <stdio.h>
#include <stdlib.h>

void extractMessageFromBMP(const char *inputFile) {
    FILE *input = fopen(inputFile, "rb");
    if (input == NULL) {
        printf("Could not open input file.\n");
        return;
    }

    // Header file BMP adalah 14 byte
    unsigned char fileHeader[14];
    // Header info BMP adalah 40 byte
    unsigned char infoHeader[40];

    // Baca header file BMP
    fread(fileHeader, 1, 14, input);
    fread(infoHeader, 1, 40, input);

    // Mendapatkan offset ke data pixel dari fileHeader[10-13]
    int offset = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);

    // Pindah ke data pixel pada file input
    fseek(input, offset, SEEK_SET);

    // Variabel untuk menyimpan panjang pesan dan byte sementara
    int messageLength = 0;
    int byte = 0;

    // Membaca panjang pesan (asumsi panjang pesan <= 255)
    for (int i = 0; i < 8; i++) {
        byte = fgetc(input);
        messageLength |= ((byte & 1) << i); // Mengambil LSB dari setiap byte untuk panjang pesan
    }

    // Alokasikan memori untuk pesan
    char *message = (char *)malloc(messageLength + 1);
    if (message == NULL) {
        printf("Could not allocate memory for message.\n");
        fclose(input);
        return;
    }

    // Inisialisasi memori pesan dengan nol
    for (int i = 0; i <= messageLength; i++) {
        message[i] = 0;
    }

    // Membaca pesan bit demi bit
    for (int i = 0; i < messageLength * 8; i++) {
        byte = fgetc(input);
        message[i / 8] |= ((byte & 1) << (i % 8)); // Menggabungkan bit menjadi byte
    }

    // Cetak pesan yang diekstraksi
    printf("Extracted message: %s\n", message);

    // Bebaskan memori dan tutup file
    free(message);
    fclose(input);
}

int main() {
    const char *inputFile = "Yuta_with_message.bmp"; // Nama file gambar input

    extractMessageFromBMP(inputFile);

    return 0;
}
