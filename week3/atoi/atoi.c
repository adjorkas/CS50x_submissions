#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int len = strlen(input);
    int n = 0;

    // Base case
    if (len == 1)
    {
        return n = input[len - 1] - '0';
    }
    // Recursive case
    else
    {
        n = input[len - 1] - '0'; // Convert to int last string digit
        input[len - 1] = '\0'; // Shorten string by 1 position
        return n + 10 * convert(input); // Recursion itself: sum int to what comes "before" it
    }
}