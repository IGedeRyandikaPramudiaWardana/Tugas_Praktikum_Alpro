#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define WIDTH 8
#define HEIGHT 8

// Define a simple 8x8 bitmap font for "C"
const unsigned char font_C[HEIGHT] = {
    0b00111100,
    0b01100110,
    0b11000010,
    0b11000000,
    0b11000000,
    0b11000010,
    0b01100110,
    0b00111100
};

// Define a simple 8x8 bitmap font for "h"
const unsigned char font_h[HEIGHT] = {
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111100,
    0b11000110,
    0b11000110,
    0b11000110,
    0b11000110
};

// Define other characters similarly...
// For simplicity, let's assume we have all necessary characters defined in similar manner.

void draw_char(unsigned char *image, int img_width, int x, int y, const unsigned char *bitmap) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (bitmap[i] & (1 << (WIDTH - 1 - j))) {
                int pos = ((y + i) * img_width + (x + j)) * 3; // Assuming 24 bits per pixel (3 bytes)
                image[pos] = 0;    // Blue
                image[pos + 1] = 0;  // Green
                image[pos + 2] = 0;  // Red
            }
        }
    }
}

int main() {
    FILE *flAsli, *flHasil;
    unsigned char header[54];
    unsigned char *image;
    int width, height, imageSize;

    flAsli = fopen("Denji.bmp", "rb");
    if (flAsli == NULL) {
        perror("Error opening source file");
        return 1;
    }

    flHasil = fopen("DenjiNegatif.bmp", "wb");
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

    // Draw the text "Chainsaw Man"
    draw_char(image, width, 10, 10, font_C); // Draw 'C' at (10, 10)
    draw_char(image, width, 18, 10, font_h); // Draw 'h' at (18, 10)
    // Draw other characters similarly...

    // Write the modified image data to the new file
    fwrite(image, 1, imageSize, flHasil);

    // Free the allocated memory
    free(image);

    // Close the files
    fclose(flAsli);
    fclose(flHasil);

    return 0;
}
