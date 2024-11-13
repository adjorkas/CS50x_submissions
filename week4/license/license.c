// The lesson here is that to reuse a buffer multiple times you need to malloc where you'll copy each value
// Since malloc allocates a new chunk of memory each time, so the pointers don't point all to the same buffer (last one)
// See line 41

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    // Exit it can't open file
    if (infile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Point plates[idx] to enough space in memory
        plates[idx] = malloc(sizeof(char) * 7);

        // Exit if memory can't be allocated
        if (plates[idx] == NULL)
        {
            return 2;
        }

        // Copy buffer contents to a string in each iteration
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }

    fclose(infile);
}