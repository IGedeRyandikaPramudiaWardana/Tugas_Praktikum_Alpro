#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk header file BMP
#pragma pack(push, 1)
typedef struct {
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

void hideMessageInBMP(const char *inputFile, const char *outputFile, const char *message) {
    FILE *input = fopen(inputFile, "rb");
    if (input == NULL) {
        printf("Could not open input file.\n");
        return;
    }

    FILE *output = fopen(outputFile, "wb");
    if (output == NULL) {
        printf("Could not open output file.\n");
        fclose(input);
        return;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    // Baca header BMP dari file input
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, input);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, input);

    // Tulis header BMP ke file output
    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, output);

    // Salin bagian data gambar sebelum menyisipkan pesan
    int pixelArrayOffset = fileHeader.bfOffBits;
    unsigned char *pixelArray = (unsigned char *)malloc(pixelArrayOffset);
    fseek(input, 0, SEEK_SET);
    fread(pixelArray, pixelArrayOffset, 1, input);
    fwrite(pixelArray, pixelArrayOffset, 1, output);
    free(pixelArray);

    // Pindah ke data pixel pada file input dan output
    fseek(input, pixelArrayOffset, SEEK_SET);
    fseek(output, pixelArrayOffset, SEEK_SET);

    int messageLength = strlen(message);
    int bitIndex = 0;
    int byte;

    // Menyisipkan panjang pesan terlebih dahulu (asumsi panjang pesan <= 255)
    for (int i = 0; i < 8; i++) {
        byte = fgetc(input);
        byte = (byte & 0xFE) | ((messageLength >> i) & 1);
        fputc(byte, output);
    }

    // Menyisipkan pesan
    while (bitIndex < messageLength * 8) {
        byte = fgetc(input);
        if (feof(input)) break;

        // Ubah bit LSB dari byte dengan bit dari pesan
        byte = (byte & 0xFE) | ((message[bitIndex / 8] >> (bitIndex % 8)) & 1);
        fputc(byte, output);
        bitIndex++;
    }

    // Salin sisa data pixel
    while (!feof(input)) {
        byte = fgetc(input);
        if (!feof(input)) fputc(byte, output);
    }

    fclose(input);
    fclose(output);
    printf("Message hidden successfully in %s.\n", outputFile);
}

int main() {
    const char *inputFile = "Yuta.bmp";           // Nama file gambar input
    const char *outputFile = "Yuta_with_message.bmp"; // Nama file gambar output
    const char *message = "Nama kamu siapa?";                  // Pesan yang akan disisipkan

    hideMessageInBMP(inputFile, outputFile, message);

    return 0;
}
