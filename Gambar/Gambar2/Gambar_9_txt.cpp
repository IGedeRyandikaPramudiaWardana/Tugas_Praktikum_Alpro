#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char** argv) 
{
    FILE *flAsli, *flHasil, *flTxt;
    char nmFileAsli[256];
    char nmFileHasil[256];
    char nmFileTxt[256];
    char pesan[256];
    int choice;

    while (1) 
    {
        printf("Pilih mode:\n");
        printf("1. Sisipkan pesan\n");
        printf("2. Sisipkan file teks\n");
        printf("3. Ekstrak pesan\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); // Clear the buffer

        if (choice == 1) 
        {
            printf("Masukkan nama file format bmp (tanpa menuliskan .bmp): ");
            scanf("%s", nmFileAsli);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileAsli, ".bmp");
            
            flAsli = fopen(nmFileAsli, "rb");
            if (flAsli == NULL) 
            {
                printf("Error: File sumber tidak ditemukan.\n");
                return main(argc, argv);
            }

            printf("Masukkan nama file Output bmp (tanpa menuliskan .bmp): ");
            scanf("%s", nmFileHasil);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileHasil, ".bmp");

            printf("Masukkan pesan yang ingin disisipkan: ");
            fgets(pesan, sizeof(pesan), stdin);
            pesan[strcspn(pesan, "\n")] = '\0'; // Remove the newline character from the input

            flHasil = fopen(nmFileHasil, "wb");
            if (flHasil == NULL) 
            {
                printf("Error: tidak ada file yang dituju.\n");
                fclose(flAsli);
                continue;
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
            while (fread(&pixelByte, 1, 1, flAsli) == 1) 
            {
                if (messageCharIndex < messageLength) 
                {
                    bitToHide = (pesan[messageCharIndex] >> messageBitIndex) & 1;
                    pixelByte = (pixelByte & 0xFE) | bitToHide; // Set the LSB to bitToHide
                    
                    messageBitIndex++;
                    if (messageBitIndex == 8) 
                    {
                        messageBitIndex = 0;
                        messageCharIndex++;
                    }
                }
                
                fwrite(&pixelByte, 1, 1, flHasil); // Write the modified byte to the output file
            }

            fclose(flAsli);
            fclose(flHasil);

            printf("Pesan telah berhasil disisipkan ke dalam gambar BMP.\n\n");

        } 
        else if (choice == 2)
        {
            printf("Masukkan nama file format bmp (tanpa menuliskan .bmp): ");
            scanf("%s", nmFileAsli);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileAsli, ".bmp");
            
            flAsli = fopen(nmFileAsli, "rb");
            if (flAsli == NULL) 
            {
                printf("Error: File sumber tidak ditemukan.\n");
                return main(argc, argv);
            }

            printf("Masukkan nama file Output bmp (tanpa menuliskan .bmp): ");
            scanf("%s", nmFileHasil);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileHasil, ".bmp");

            printf("Masukkan nama file teks (tanpa menuliskan .txt): ");
            scanf("%s", nmFileTxt);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileTxt, ".txt");

            flTxt = fopen(nmFileTxt, "r");
            if (flTxt == NULL) 
            {
                printf("Error: File teks tidak ditemukan.\n");
                fclose(flAsli);
                continue;
            }

            // Read the text file into the message buffer
            size_t len = fread(pesan, 1, sizeof(pesan) - 1, flTxt);
            pesan[len] = '\0'; // Null-terminate the message

            fclose(flTxt);

            flHasil = fopen(nmFileHasil, "wb");
            if (flHasil == NULL) 
            {
                printf("Error: tidak ada file yang dituju.\n");
                fclose(flAsli);
                continue;
            }

            // Embedding the text file content into the BMP image
            char buff[54];
            fread(buff, 1, 54, flAsli); // Read the BMP header
            fwrite(buff, 1, 54, flHasil); // Write the BMP header to the output file

            int messageLength = strlen(pesan) + 1; // Include null terminator
            int messageBitIndex = 0;
            int messageCharIndex = 0;
            int bitToHide;
            
            unsigned char pixelByte;
            while (fread(&pixelByte, 1, 1, flAsli) == 1) 
            {
                if (messageCharIndex < messageLength) 
                {
                    bitToHide = (pesan[messageCharIndex] >> messageBitIndex) & 1;
                    pixelByte = (pixelByte & 0xFE) | bitToHide; // Set the LSB to bitToHide
                    
                    messageBitIndex++;
                    if (messageBitIndex == 8) 
                    {
                        messageBitIndex = 0;
                        messageCharIndex++;
                    }
                }
                
                fwrite(&pixelByte, 1, 1, flHasil); // Write the modified byte to the output file
            }

            fclose(flAsli);
            fclose(flHasil);

            printf("Pesan dari file teks telah berhasil disisipkan ke dalam gambar BMP.\n\n");
        } 
        else if (choice == 3) 
        {
            printf("Masukkan nama file format bmp yang telah disisipi pesan (tanpa menuliskan .bmp): ");
            scanf("%s", nmFileAsli);
            while(getchar() != '\n');  // Clear the buffer
            strcat(nmFileAsli, ".bmp");

            flAsli = fopen(nmFileAsli, "rb");
            if (flAsli == NULL) 
            {
                printf("Error: File sumber tidak ditemukan.\n\n");
                return 1;
            }

            // Extracting the message from the BMP image
            fseek(flAsli, 54, SEEK_SET); // Skip the BMP header

            int messageBitIndex = 0;
            int messageCharIndex = 0;
            unsigned char pixelByte;
            unsigned char currentChar = 0;

            while (fread(&pixelByte, 1, 1, flAsli) == 1 && messageCharIndex < sizeof(pesan) - 1) 
            {
                currentChar |= (pixelByte & 1) << messageBitIndex;
                messageBitIndex++;
                
                if (messageBitIndex == 8) 
                {
                    if (currentChar == '\0') 
                    {
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

            printf("Pesan yang diekstrak: %s\n\n", pesan);
        } 
        else if (choice == 4) 
        {
            printf("Anda telah keluar dari program.\n");
            return 1;
        } 
        else 
        {
            printf("Pilihan tidak valid.\n\n");
        }
    }

    return 0;
}
