#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*
	how to run:
	1. stegano_program nama_File_BMP sisipkan nama_File_TXT
	2. stegano_program nama_File_BMP ekstrak

*/

void sisipkanPesan(const char* nmFileAsli, const char* nmFilePesan, const char* nmFileHasil) {
    FILE *flAsli, *flHasil, *flPesan;
    char pesan[1024];  // Increase buffer size to handle larger messages

    flAsli = fopen(nmFileAsli, "rb");
    if (flAsli == NULL) {
        printf("Error: File sumber tidak ditemukan.\n");
        return;
    }

    flPesan = fopen(nmFilePesan, "r");
    if (flPesan == NULL) {
        printf("Error: File pesan tidak ditemukan.\n");
        fclose(flAsli);
        return;
    }

    // Read the message from the text file
    fgets(pesan, sizeof(pesan), flPesan);
    pesan[strcspn(pesan, "\n")] = '\0'; // Remove the newline character from the input
    fclose(flPesan);

    flHasil = fopen(nmFileHasil, "wb");
    if (flHasil == NULL) {
        printf("Error: tidak ada file yang dituju.\n");
        fclose(flAsli);
        return;
    }

    // Embedding the message into the BMP image
    char buff[54];
    fread(buff, 1, 54, flAsli); // Read the BMP header
    fwrite(buff, 1, 54, flHasil); // Write the BMP header to the output file

    int messageLength = strlen(pesan) + 1; // Include null terminator
    int messageBitIndex = 0;
    int messageCharIndex = 0;
    int bitToHide;

    unsigned char pixelByte;
    while (fread(&pixelByte, 1, 1, flAsli) == 1) {
        if (messageCharIndex < messageLength) {
            bitToHide = (pesan[messageCharIndex] >> messageBitIndex) & 1;
            pixelByte = (pixelByte & 0xFE) | bitToHide; // Set the LSB to bitToHide
            
            messageBitIndex++;
            if (messageBitIndex == 8) {
                messageBitIndex = 0;
                messageCharIndex++;
            }
        }
        
        fwrite(&pixelByte, 1, 1, flHasil); // Write the modified byte to the output file
    }

    fclose(flAsli);
    fclose(flHasil);

    printf("Pesan telah berhasil disisipkan ke dalam gambar BMP.\n");
}

void ekstrakPesan(const char* nmFileAsli) {
    FILE *flAsli;
    char pesan[1024];  // Increase buffer size to handle larger messages

    flAsli = fopen(nmFileAsli, "rb");
    if (flAsli == NULL) {
        printf("Error: File sumber tidak ditemukan.\n");
        return;
    }

    // Extracting the message from the BMP image
    fseek(flAsli, 54, SEEK_SET); // Skip the BMP header

    int messageBitIndex = 0;
    int messageCharIndex = 0;
    unsigned char pixelByte;
    unsigned char currentChar = 0;

    while (fread(&pixelByte, 1, 1, flAsli) == 1 && messageCharIndex < sizeof(pesan) - 1) {
        currentChar |= (pixelByte & 1) << messageBitIndex;
        messageBitIndex++;
        
        if (messageBitIndex == 8) {
            if (currentChar == '\0') {
                break; // Stop reading if null terminator is found
            }
            pesan[messageCharIndex] = currentChar;
            messageCharIndex++;
            messageBitIndex = 0;
            currentChar = 0;
        }
    }
    pesan[messageCharIndex] = '\0'; // Null-terminate the extracted message

    fclose(flAsli);

    printf("Pesan yang diekstrak: %s\n", pesan);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage:\n");
        printf("%s nama_File_BMP sisipkan nama_File_TXT\n", argv[0]);
        printf("%s nama_File_BMP ekstrak\n", argv[0]);
        return 1;
    }

    char nmFileAsli[256];
    char nmFilePesan[256];
    char nmFileHasil[256];

    strcpy(nmFileAsli, argv[1]);
    strcat(nmFileAsli, ".bmp");

    if (strcmp(argv[2], "sisipkan") == 0) {
        if (argc < 4) {
            printf("Error: Nama file teks yang berisi pesan harus disertakan.\n");
            return 1;
        }

        strcpy(nmFilePesan, argv[3]);
        strcat(nmFilePesan, ".txt");

        printf("Masukkan nama file Output bmp (tanpa menuliskan .bmp): ");
        scanf("%s", nmFileHasil);
        while(getchar() != '\n');  // Clear the buffer
        strcat(nmFileHasil, ".bmp");

        sisipkanPesan(nmFileAsli, nmFilePesan, nmFileHasil);

    } else if (strcmp(argv[2], "ekstrak") == 0) {
        ekstrakPesan(nmFileAsli);

    } else {
        printf("Error: Argumen kedua harus 'sisipkan' atau 'ekstrak'.\n");
        return 1;
    }

    return 0;
}
