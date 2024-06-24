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

void extractMessageFromBMP(const char *inputFile) {
    FILE *input = fopen(inputFile, "rb");
    if (input == NULL) {
        printf("Could not open input file.\n");
        return;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    // Baca header BMP dari file input
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, input);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, input);

    // Pindah ke data pixel pada file input
    fseek(input, fileHeader.bfOffBits, SEEK_SET);

    int messageLength = 0;
    int bitIndex = 0;
    int byte = 0;

    // Membaca panjang pesan terlebih dahulu (asumsi panjang pesan <= 255)
    for (int i = 0; i < 8; i++) {
        byte = fgetc(input);
        messageLength |= ((byte & 1) << i);
    }

    char *message = (char *)malloc(messageLength + 1);
    if (message == NULL) {
        printf("Could not allocate memory for message.\n");
        fclose(input);
        return;
    }
    memset(message, 0, messageLength + 1);

    // Membaca pesan
    for (int i = 0; i < messageLength * 8; i++) {
        byte = fgetc(input);
        message[bitIndex / 8] |= ((byte & 1) << (bitIndex % 8));
        bitIndex++;
    }

    printf("Extracted message: %s\n", message);

    free(message);
    fclose(input);
}

int main() {
    const char *inputFile = "Yuta_with_message.bmp"; // Nama file gambar input

    extractMessageFromBMP(inputFile);

    return 0;
}
