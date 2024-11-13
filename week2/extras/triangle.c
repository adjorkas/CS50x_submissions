// Check if triangle is valid based on size of its sides and inform the user
// Done as practice for CS50 2023 - "Functions"

#include <cs50.h>
#include <stdio.h>

// Sides in a triangle are always 3
const int triSides = 3;

bool valid_triangle(float array[]);

int main(void)
{
    float sides[triSides];

    // Ask user for input
    for(int i = 0; i < triSides; i++)
    {
        sides[i] = get_float("Side #%i: ", i + 1);
    }

    // Check validity
    bool valid = valid_triangle(sides);

    // Print valid or invalid
    if(valid == true)
    printf("The triangle is valid!\n");
    else
    printf("The triangle is not valid!\n");
}

// Check for triangle validity based on size of sides
// Note: I did this differently before seeing course answer but-
// -implemented answer since seemed more efficient ("short-circuits")
// and learnt something bc of this comparison

bool valid_triangle(float array[])
{
    // Check for positive sides
    if((array[0]) <= 0 || array[1] <= 0 || array[2] <= 0)
    return false;

    // Check for sum of two sides larger than the third
    if((array[0] + array[1] <= array[2]
    || array[1] + array[2] <= array[0]
    || array[2] + array[0] <= array[1]))
    return false;

    // If tests are passed, we're good!
    return true;
}