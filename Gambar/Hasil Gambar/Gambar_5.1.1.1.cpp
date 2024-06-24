#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk menyisipkan pesan ke dalam file BMP
void embedMessage(const char *sourceFile, const char *outputFile, const char *message) {
    FILE *fin = fopen(sourceFile, "rb");
    FILE *fout = fopen(outputFile, "wb");

    if (fin == NULL || fout == NULL) {
        printf("File tidak dapat dibuka atau dibuat.\n");
        return;
    }

    // Salin header dari file BMP
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fin);
    fwrite(header, sizeof(unsigned char), 54, fout);

    // Ukuran pesan yang akan disisipkan
    int messageLen = strlen(message);
    int maxMessageLen = (header[18] - 1) * (header[22] - 1); // Karena setiap piksel menyimpan 1 byte pesan

    if (messageLen > maxMessageLen) {
        printf("Pesan terlalu panjang untuk disisipkan dalam gambar ini.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    // Proses menyisipkan pesan
    int i, j = 0;
    unsigned char data, bit;
    for (i = 0; i < messageLen; i++) {
        data = message[i];
        for (bit = 7; bit >= 0; bit--, j++) {
            unsigned char bitToEmbed = (data >> bit) & 1;
            header[j % 3] = (header[j % 3] & 0xFE) | bitToEmbed; // Mengganti LSB dengan bit pesan
            if (j % 3 == 2) {
                fwrite(header, sizeof(unsigned char), 3, fout); // Menulis kembali setiap 3 byte header yang sudah dimodifikasi
            }
        }
    }

    // Menyalin sisa data dari file asli
    unsigned char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(unsigned char), 1024, fin)) > 0) {
        fwrite(buffer, sizeof(unsigned char), bytesRead, fout);
    }

    printf("Pesan berhasil disisipkan ke dalam gambar %s.\n", outputFile);

    fclose(fin);
    fclose(fout);
}

// Fungsi untuk mengekstrak pesan dari file BMP yang sudah dimodifikasi
void extractMessage(const char *sourceFile) {
    FILE *fin = fopen(sourceFile, "rb");

    if (fin == NULL) {
        printf("File tidak dapat dibuka.\n");
        return;
    }

    // Melompati header BMP
    fseek(fin, 54, SEEK_SET);

    // Membaca pesan yang telah disisipkan
    unsigned char buffer = 0;
    int bitCount = 0;
    char extractedMessage[1000];
    int index = 0;

    while (fread(&buffer, sizeof(unsigned char), 1, fin) == 1 && index < 1000) {
        unsigned char lsb = buffer & 1;
        extractedMessage[index] = (extractedMessage[index] << 1) | lsb;
        bitCount++;

        // Setiap byte pesan memiliki 8 bit, jika sudah mencapai 8 bit, tambahkan ke pesan
        if (bitCount == 8) {
            if (extractedMessage[index] == '\0') {
                break; // Berhenti jika sudah menemukan null terminator
            }
            bitCount = 0;
            index++;
        }
    }

    if (index == 0) {
        printf("Tidak ada pesan yang ditemukan dalam gambar %s.\n", sourceFile);
    } else {
        printf("Pesan yang diekstraksi dari gambar %s adalah: %s\n", sourceFile, extractedMessage);
    }

    fclose(fin);
}

int main() {
    char sourceFile[100];
    char outputFile[100];
    char message[1000];

    printf("Masukkan nama file BMP yang akan dimodifikasi (contoh: Yuta.bmp): ");
    fgets(sourceFile, sizeof(sourceFile), stdin);
    sourceFile[strcspn(sourceFile, "\n")] = 0; // Menghapus newline dari fgets

    printf("Masukkan nama file output untuk gambar yang sudah dimodifikasi (contoh: output.bmp): ");
    fgets(outputFile, sizeof(outputFile), stdin);
    outputFile[strcspn(outputFile, "\n")] = 0; // Menghapus newline dari fgets

    printf("Masukkan pesan yang ingin disisipkan: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Menghapus newline dari fgets

    embedMessage(sourceFile, outputFile, message);

    // Ekstraksi pesan dari gambar yang sudah dimodifikasi
    extractMessage(outputFile);

    return 0;
}
