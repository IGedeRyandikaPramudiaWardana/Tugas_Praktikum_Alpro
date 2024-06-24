#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hideMessageInBMP(FILE *flHasil, const char *message) {
    int messageLength = strlen(message);
    int bitIndex = 0;
    int byte;

    // Menyisipkan panjang pesan terlebih dahulu (asumsi panjang pesan <= 255)
    for (int i = 0; i < 8; i++) {
        fread(&byte, 1, 1, flHasil);
        fseek(flHasil, -1, SEEK_CUR);
        byte = (byte & 0xFE) | ((messageLength >> i) & 1);
        fwrite(&byte, 1, 1, flHasil);
    }

    // Menyisipkan pesan
    while (bitIndex < messageLength * 8) {
        fread(&byte, 1, 1, flHasil);
        fseek(flHasil, -1, SEEK_CUR);
        byte = (byte & 0xFE) | ((message[bitIndex / 8] >> (bitIndex % 8)) & 1);
        fwrite(&byte, 1, 1, flHasil);
        bitIndex++;
    }
}

void extractMessageFromBMP(const char *inputFile) {
    FILE *input = fopen(inputFile, "rb");
    if (input == NULL) {
        printf("Could not open input file.\n");
        return;
    }

    unsigned char header[54];
    fread(header, 1, 54, input); // Read the header

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

void processImage(const char *inputFile, const char *outputFile, const char *mode, const char *message) {
    FILE *flAsli, *flHasil;
    unsigned char header[54];
    unsigned char pixel[3];
    
    flAsli = fopen(inputFile, "rb");
    flHasil = fopen(outputFile, "wb");

    if (!flAsli || !flHasil) {
        printf("Could not open files.\n");
        return;
    }

    // Read and write the header
    fread(header, 1, 54, flAsli);
    fwrite(header, 1, 54, flHasil);

    // Process the image based on the mode
    while (fread(pixel, 1, 3, flAsli) == 3) {
        if (strcmp(mode, "negative") == 0) {
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
        } else if (strcmp(mode, "grayscale") == 0) {
            unsigned char gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[0] = pixel[1] = pixel[2] = gray;
        } else if (strcmp(mode, "red") == 0) {
            pixel[1] = pixel[2] = 0;
        } else if (strcmp(mode, "green") == 0) {
            pixel[0] = pixel[2] = 0;
        } else if (strcmp(mode, "blue") == 0) {
            pixel[0] = pixel[1] = 0;
        }

        fwrite(pixel, 1, 3, flHasil);
    }

    // Hide message in the output file if provided
    if (message != NULL) {
        fseek(flHasil, 54, SEEK_SET); // Move to the start of the pixel data
        hideMessageInBMP(flHasil, message);
    }

    fclose(flAsli);
    fclose(flHasil);
    printf("Image processed successfully in %s mode.\n", mode);
    if (message != NULL) {
        printf("Message hidden successfully in %s.\n", outputFile);
    }
}

int main() {
    char inputFile[256];
    char outputFile[256];
    char mode[20];
    char message[256];
    char choice;

    printf("Enter the name of the input file (e.g., Denji.bmp): ");
    scanf("%s", inputFile);

    printf("Enter the name of the output file (e.g., Denji_processed.bmp): ");
    scanf("%s", outputFile);

    printf("Choose an image processing mode:\n");
    printf("1. Negative\n");
    printf("2. Grayscale\n");
    printf("3. Red dominant\n");
    printf("4. Green dominant\n");
    printf("5. Blue dominant\n");
    printf("6. Hide a message\n");
    printf("7. Extract a message\n");
    printf("Enter your choice (1-7): ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            strcpy(mode, "negative");
            break;
        case '2':
            strcpy(mode, "grayscale");
            break;
        case '3':
            strcpy(mode, "red");
            break;
        case '4':
            strcpy(mode, "green");
            break;
        case '5':
            strcpy(mode, "blue");
            break;
        case '6':
            strcpy(mode, "hide");
            break;
        case '7':
            strcpy(mode, "extract");
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    if (strcmp(mode, "extract") == 0) {
        extractMessageFromBMP(inputFile);
    } else {
        printf("Do you want to hide a message in the image? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            printf("Enter the message to hide: ");
            scanf(" %[^\n]%*c", message); // Read the entire line including spaces
            processImage(inputFile, outputFile, mode, message);
        } else {
            processImage(inputFile, outputFile, mode, NULL);
        }

        if (strcmp(mode, "hide") == 0) {
            printf("Do you want to extract a message from the processed image? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                extractMessageFromBMP(outputFile);
            }
        }
    }

    return 0;
}
