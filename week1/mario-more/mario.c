// Recreates adjacent pyramids of blocks from Super Mario Bros. (harder version)

#include <cs50.h>
#include <stdio.h>

#define MIN_HEIGHT 1
#define MAX_HEIGHT 8

void bricks(int a);

int main(void)
{
    // Prompt user for pyramid height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < MIN_HEIGHT || n > MAX_HEIGHT);

    // Print adjacent pyramids
    // Repeat for each 'i' line number
    for (int i = 1; i <= n; i++)
    {
        // Print spaces to right-align first pyramid's bricks
        for (int x = 0; x < n - i; x++)
        {
            printf(" ");
        }

        // Print first pyramid's bricks
        bricks(i);

        // Print two spaces
        printf("  ");

        // Print second pyramid's bricks
        bricks(i);

        // New line
        printf("\n");
    }
}











// Prints '#' a times
void bricks(int a)
{
    for (int j = 0; j < a; j++)
    {
        printf("#");
    }
}