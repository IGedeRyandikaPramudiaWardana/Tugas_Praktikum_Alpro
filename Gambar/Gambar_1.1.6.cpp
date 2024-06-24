#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void extract_text(unsigned char *image, int imageSize, char *extractedText, int maxTextSize) {
    int bit_index = 0;
    int char_index = 0;
    unsigned char current_char = 0;

    while (bit_index < imageSize * 8 && char_index < maxTextSize - 1) {
        current_char = 0;
        for (int j = 0; j < 8; j++) {
            if (bit_index >= imageSize * 8) {
                printf("Reached the end of the image.\n");
                extractedText[char_index] = '\0';
                return;
            }

            current_char |= ((image[bit_index / 8] & 0x01) << j);
            bit_index++;
        }

        printf("Extracted char: %c (0x%02X)\n", current_char, current_char);  // Debugging line

        if (current_char == '\0') {
            break;
        }

        extractedText[char_index++] = current_char;
    }

    extractedText[char_index] = '\0';
}

int main() {
    FILE *flAsli;
    unsigned char header[54];
    unsigned char *image;
    int width, height, imageSize;
    char extractedText[1000];  // Assuming the hidden text won't exceed 999 characters

    flAsli = fopen("YutaStego_1.jpeg", "rb");
    if (flAsli == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the BMP header
    fread(header, 1, 54, flAsli);

    // Get width and height from header
    width = *(int*)&header[18];
    height = *(int*)&header[22];
    imageSize = width * height * 3;

    // Allocate memory for the image data
    image = (unsigned char*)malloc(imageSize);

    // Read the image data
    fread(image, 1, imageSize, flAsli);

    // Extract the hidden text from the image
    extract_text(image, imageSize, extractedText, sizeof(extractedText));

    // Print the extracted text
    printf("Extracted Text: %s\n", extractedText);

    // Free the allocated memory
    free(image);

    // Close the file
    fclose(flAsli);

    return 0;
}
