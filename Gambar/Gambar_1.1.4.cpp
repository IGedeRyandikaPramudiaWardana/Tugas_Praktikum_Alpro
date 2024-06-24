#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void hide_text(unsigned char *image, int imageSize, const char *text) {
    int text_len = strlen(text);
    int bit_index = 0;

    for (int i = 0; i < text_len; i++) {
        for (int j = 0; j < 8; j++) {  // Iterate over each bit in the character
            if (bit_index >= imageSize * 8) {
                printf("Image is too small to hide the entire text.\n");
                return;
            }

            // Clear the least significant bit (LSB) of the pixel byte and set it to the current bit of the character
            image[bit_index / 8] = (image[bit_index / 8] & 0xFE) | ((text[i] >> j) & 0x01);
            bit_index++;
        }
    }

    // Mark the end of the hidden text with a null character
    for (int j = 0; j < 8; j++) {
        if (bit_index >= imageSize * 8) {
            printf("Image is too small to hide the end of text marker.\n");
            return;
        }

        image[bit_index / 8] = (image[bit_index / 8] & 0xFE);  // Set LSB to 0
        bit_index++;
    }
}

int main() {
    FILE *flAsli, *flHasil;
    unsigned char header[54];
    unsigned char *image;
    int width, height, imageSize;

    flAsli = fopen("Yuta.bmp", "rb");
    if (flAsli == NULL) {
        perror("Error opening source file");
        return 1;
    }

    flHasil = fopen("YutaStego_1.jpeg", "wb");
    if (flHasil == NULL) {
        perror("Error opening destination file");
        fclose(flAsli);
        return 1;
    }

    // Read and write the BMP header
    fread(header, 1, 54, flAsli);
    fwrite(header, 1, 54, flHasil);

    // Get width and height from header
    width = *(int*)&header[18];
    height = *(int*)&header[22];
    imageSize = width * height * 3;

    // Allocate memory for the image data
    image = (unsigned char*)malloc(imageSize);

    // Read the image data
    fread(image, 1, imageSize, flAsli);

    // Hide the text "Chainsaw Man" in the image
    hide_text(image, imageSize, "Yuta dari Jujutsu Kaisen 0");

    // Write the modified image data to the new file
    fwrite(image, 1, imageSize, flHasil);

    // Free the allocated memory
    free(image);

    // Close the files
    fclose(flAsli);
    fclose(flHasil);

    return 0;
}
