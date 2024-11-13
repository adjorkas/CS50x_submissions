// Recovers 50 deleted images from memory card

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Exit if program is not executed with one command-line arg
    if (argc != 2)
    {
        printf("Proper usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Couldn't open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *picture = NULL;
    int counter = 0;
    ckhar *filename; // No need for array[50];

    // Read 512 bytes into a buffer until end of card
    while (fread(&buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // If start of new jpeg make file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first picture, close previous
            if (counter > 0)
            {
                fclose(picture);
            }

            // Set filename
            filename = malloc(sizeof(char) * 8);
            if (filename == NULL)
            {
                return 1;
            }
            sprintf(filename, "%03i.jpg", counter);

            // Open newfile
            picture = fopen(filename, "w");
            free(filename);
            fwrite(buffer, 1, BLOCK_SIZE, picture);

            counter++;
        }
        // Else if already found a jpg continue writing
        else if (picture != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, picture);
        }
    }
    // Close any remaining files
    fclose(picture);
    fclose(card);
}