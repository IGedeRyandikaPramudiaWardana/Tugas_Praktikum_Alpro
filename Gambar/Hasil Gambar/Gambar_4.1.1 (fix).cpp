#include "stdio.h"
#include "string.h"

// Function to convert a character to binary representation
void charToBinary(char c, char* binary) 
{
    for (int i = 7; i >= 0; --i) 
	{
        binary[i] = (c & 1) ? '1' : '0';
        c >>= 1;
    }
}

// Function to embed a bit into a byte
unsigned char embedBit(unsigned char byte, char bit) 
{
    byte = (byte & 0xFE) | (bit - '0');
    return byte;
}

// Function to extract a bit from a byte
char extractBit(unsigned char byte) 
{
    return (byte & 1) ? '1' : '0';
}

// Function to convert binary string to character
char binaryToChar(char* binary) 
{
    char c = 0;
    for (int i = 0; i < 8; ++i) 
	{
        c <<= 1;
        if (binary[i] == '1') 
		{
            c |= 1;
        }
    }
    return c;
}

void embedMessage() 
{
    FILE *flAsli, *flHasil;
    char buff[256];
    int buffInt;
    char message[256];
    char inputFile[256], outputFile[256];
    char inputFileName[260], outputFileName[260];

    printf("Masukkan Nama File Input BMP (tanpa menuliskan .bmp extension Pada Nama): ");
    fgets(inputFile, sizeof(inputFile), stdin);
    inputFile[strcspn(inputFile, "\n")] = '\0'; // Remove newline character
    snprintf(inputFileName, sizeof(inputFileName), "%s.bmp", inputFile);

    printf("Masukkan Nama File Output BMP (tanpa menuliskan .bmp extension Pada Nama): ");
    fgets(outputFile, sizeof(outputFile), stdin);
    outputFile[strcspn(outputFile, "\n")] = '\0'; // Remove newline character
    snprintf(outputFileName, sizeof(outputFileName), "%s.bmp", outputFile);

    printf("Masukkan Pesan yang Ingin Disisipkan: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    int messageLen = strlen(message);
    char messageBinary[messageLen * 8 + 1];
    messageBinary[0] = '\0';

    // Convert the message to a binary string
    for (int i = 0; i < messageLen; ++i) 
	{
        char binary[9] = {0};
        charToBinary(message[i], binary);
        strcat(messageBinary, binary);
    }

    int messageBinaryLen = strlen(messageBinary);
    int messageIndex = 0;

    flAsli = fopen(inputFileName, "rb");
    if (flAsli == NULL) 
	{
        printf("Error: gagal membuka sumber file.\n");
        return 1;
    }

    flHasil = fopen(outputFileName, "wb");
    
    if (flHasil == NULL) 
	{
        printf("Error: gagal membuka file yang dituju.\n");
        fclose(flAsli);
        return 1;
    }

    // Copy the BMP header unchanged
    fread(buff, 1, 54, flAsli);
    fwrite(buff, 1, 54, flHasil);

    // Embed the message into the image data
    while (fread(&buffInt, 4, 1, flAsli)) 
	{
        if (messageIndex < messageBinaryLen) 
		{
            unsigned char *bytePtr = (unsigned char *)&buffInt;
            for (int i = 0; i < 4 && messageIndex < messageBinaryLen; ++i) 
			{
                bytePtr[i] = embedBit(bytePtr[i], messageBinary[messageIndex]);
                messageIndex++;
            }
        }
        fwrite(&buffInt, 4, 1, flHasil);
    }

    fclose(flAsli);
    fclose(flHasil);

    printf("Pesan Berhasil disisipkan.\n");
}

void extractMessage() 
{
    FILE *flAsli;
    char buff[256];
    int buffInt;
    char messageBinary[256 * 8 + 1];
    int messageIndex = 0;
    int messageBinaryLen = sizeof(messageBinary) - 1; // Allocate space for null terminator
    char inputFile[256];
    char inputFileName[260];

    printf("Masukkan file BMP yang ingin di ekstrak (tanpa .bmp extension pada penulisan nama): ");
    fgets(inputFile, sizeof(inputFile), stdin);
    inputFile[strcspn(inputFile, "\n")] = '\0'; // Remove newline character
    snprintf(inputFileName, sizeof(inputFileName), "%s.bmp", inputFile);

    flAsli = fopen(inputFileName, "rb");
    if (flAsli == NULL)
	{
        printf("Error: gagal membuka file.\n");
        return;
    }

    // Skip the BMP header
    fread(buff, 1, 54, flAsli);

    // Extract the message from the image data
    while (fread(&buffInt, 4, 1, flAsli) && messageIndex < messageBinaryLen) 
	{
        unsigned char *bytePtr = (unsigned char *)&buffInt;
        for (int i = 0; i < 4 && messageIndex < messageBinaryLen; ++i) 
		{
            messageBinary[messageIndex] = extractBit(bytePtr[i]);
            messageIndex++;
        }
    }
    messageBinary[messageIndex] = '\0'; // Null terminate the binary message string

    // Convert binary string to text message
    int binaryLen = strlen(messageBinary);
    char extractedMessage[256];
    //char extractedMessage2[256];
    int extractedMessageIndex = 0;

    for (int i = 0; i < binaryLen; i += 8) 
	{
        char binaryChar[9] = {0};
        strncpy(binaryChar, &messageBinary[i], 8);
        extractedMessage[extractedMessageIndex] = binaryToChar(binaryChar);
        extractedMessageIndex++;
    }
    extractedMessage[extractedMessageIndex] = '\0'; // Null terminate the extracted message string
    //extractedMessage2[extractedMessageIndex] = '\0';

    fclose(flAsli);

    printf("Pesan yang diekstrak: %s\n", extractedMessage);
}

int main() 
{
    int pilihan;
	
	while (1)
	{	
	    printf("\n\nPilihan operasi yang ingin dilakukan:\n");
		printf("1. Menyisipkan Pesan Teks ke Dalam Gambar.\n");
	    printf("2. Ekstrak Pesan Teks Dari Gambar.\n");
	    printf("3. Keluar\n");
	    printf("Masukkan Pilihan Anda: ");
	    scanf("%d", &pilihan);
	    getchar(); // Consume the newline character left by scanf
	
	
	    if (pilihan == 1) 
		{
	        embedMessage();
	        //return main;
	    } 
		
		else if (pilihan == 2) 
		{
	        extractMessage();
	        //return main;
	    }
		
		else if(pilihan == 3)
		{
			printf("Anda telah keluar dari program.\n");
			return(0);
		}
		else 
		{
	        printf("Pilihan anda tidak valid.\n");
	    }
	}
    return 0;
}