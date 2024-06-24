#include "stdio.h"
#include "string.h"

// Function to convert a character to binary representation
void charToBinary(char c, char* binary) {
    for (int i = 7; i >= 0; --i) {
        binary[i] = (c & 1) ? '1' : '0';
        c >>= 1;
    }
}

// Function to embed a bit into a byte
unsigned char embedBit(unsigned char byte, char bit) {
    byte = (byte & 0xFE) | (bit - '0');
    return byte;
}

int main() {
    FILE *flAsli, *flHasil;
    char buff[256];
    int buffInt;
    char *message = "This is a hidden message.";
    int messageLen = strlen(message);
    char messageBinary[messageLen * 8 + 1];
    messageBinary[0] = '\0';
    
    // Convert the message to a binary string
    for (int i = 0; i < messageLen; ++i) {
        char binary[9] = {0};
        charToBinary(message[i], binary);
        strcat(messageBinary, binary);
    }

    int messageBinaryLen = strlen(messageBinary);
    int messageIndex = 0;

    flAsli = fopen("Yuta.bmp", "rb");
    flHasil = fopen("Yuta_stego_1.1.1.bmp", "wb");

    // Copy the BMP header unchanged
    fread(buff, 1, 54, flAsli);
    fwrite(buff, 1, 54, flHasil);

    // Embed the message into the image data
    while (fread(&buffInt, 4, 1, flAsli)) {
        if (messageIndex < messageBinaryLen) {
            unsigned char *bytePtr = (unsigned char *)&buffInt;
            for (int i = 0; i < 4 && messageIndex < messageBinaryLen; ++i) {
                bytePtr[i] = embedBit(bytePtr[i], messageBinary[messageIndex]);
                messageIndex++;
            }
        }
        fwrite(&buffInt, 4, 1, flHasil);
    }

    fclose(flAsli);
    fclose(flHasil);

    return 0;
}


