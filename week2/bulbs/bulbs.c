// Program that prints string in "light bulbs" as binary
// Disclaimer: method is different from suggested in course
// Thought this was simpler than the "remainder method" suggested
// The math behind that is explained here: https://indepth.dev/posts/1019/the-simple-math-behind-decimal-binary-conversion-algorithms

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get input from user
    string msg = get_string("Message: ");
    int length = strlen(msg);

    // Iterate through each char in string
    for (int i = 0; i < length; i++)
    {
        int temp = msg[i];

        // Check for needed light bulbs and print accordingly
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int power = pow(2, j);
            if (temp >= power)
            {
                // Print light emoji
                printf("\U0001F7E1");
                temp -= power;
            }
            else
            {
                // Print dark emoji
                printf("\U000026AB");
            }
        }
        printf("\n");
    }
}