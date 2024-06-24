#include <stdio.h>
#include <stdlib.h>

void insertMessageIntoBMP(const char *inputFile, const char *outputFile, const char *message) {
    FILE *input = fopen(inputFile, "rb");
    FILE *output = fopen(outputFile, "wb");
    if (input == NULL || output == NULL) {
        printf("Could not open input or output file.\n");
        return;
    }

    // Header file BMP adalah 14 byte
    unsigned char fileHeader[14];
    // Header info BMP adalah 40 byte
    unsigned char infoHeader[40];

    // Baca header file BMP
    fread(fileHeader, 1, 14, input);
    fread(infoHeader, 1, 40, input);

    // Tulis header ke file output
    fwrite(fileHeader, 1, 14, output);
    fwrite(infoHeader, 1, 40, output);

    // Mendapatkan offset ke data pixel dari fileHeader[10-13]
    int offset = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);

    // Pindah ke data pixel pada file input dan output
    fseek(input, offset, SEEK_SET);
    fseek(output, offset, SEEK_SET);

    // Menyisipkan panjang pesan (asumsi panjang pesan <= 255)
    int messageLength = strlen(message);
    for (int i = 0; i < 8; i++) {
        int byte = fgetc(input);
        byte = (byte & 0xFE) | ((messageLength >> i) & 1); // Menyisipkan bit panjang pesan
        fputc(byte, output);
    }

    // Menyisipkan pesan
    for (int i = 0; i < messageLength * 8; i++) {
        int byte = fgetc(input);
        byte = (byte & 0xFE) | ((message[i / 8] >> (i % 8)) & 1); // Menyisipkan bit pesan
        fputc(byte, output);
    }

    // Menyalin sisa file
    while (!feof(input)) {
        int byte = fgetc(input);
        if (byte != EOF) {
            fputc(byte, output);
        }
    }

    fclose(input);
    fclose(output);
}

int main() {
    const char *inputFile = "Yuta.bmp"; // Nama file gambar input
    const char *outputFile = "Yuta_with_message.bmp"; // Nama file gambar output
    const char *message = "Hello, world!"; // Pesan yang akan disisipkan

    insertMessageIntoBMP(inputFile, outputFile, message);

    printf("Message inserted into BMP file.\n");

    return 0;
}
