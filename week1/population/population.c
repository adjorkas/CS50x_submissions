// Lab1: population growth.
// Determine how long it takes for a population to reach a particular size.

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start, end;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Calculate number of years until we reach threshold
    int years = 0;
    int n = start;

    while (n < end)
    {
        n += (n / 3) - (n / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}
