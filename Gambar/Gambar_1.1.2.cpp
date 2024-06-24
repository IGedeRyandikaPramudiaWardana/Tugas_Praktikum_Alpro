#include "stdio.h"

int main()
{
    FILE *flAsli, *flHasil;
    char buff[54];
    unsigned int buffInt;

    flAsli = fopen("Fuji.bmp", "rb");
    /*if (flAsli == NULL) {
        perror("Error opening source file");
        return 1;
    }*/

    flHasil = fopen("editedFuji.bmp", "wb");
    /*if (flHasil == NULL) {
        perror("Error opening destination file");
        fclose(flAsli);
        return 1;
    }
*/
    // Copy header
    fread(buff, 1, 54, flAsli);
    fwrite(buff, 1, 54, flHasil);

    // Process the rest of the file
    while (fread(&buffInt, 4, 1, flAsli) == 1) {
        buffInt = ~buffInt;
        fwrite(&buffInt, 4, 1, flHasil);
    }

    fclose(flAsli);
    fclose(flHasil);

    return 0;
}
