// This program calculates grade of text
// Bug: used 100 instead of 100.0; L and S didn't register as floats

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 1;
    int sentences = 0;
    int length = strlen(text);

    // Count letters, words, and sentences
    for (int i = 0; i < length; i++)
    {
        char temp = text[i];
        if (isalpha(temp))
        {
            letters++;
        }
        if (isspace(temp))
        {
            words++;
        }
        if (temp == '.' || temp == '!' || temp == '?')
        {
            sentences++;
        }
    }

    // Average letters per 100 words in text
    float L = 100.0 * letters / words;

    // Average number of sentences per 100 words in text
    float S = 100.0 * sentences / words;

    // Implement Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print answers
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}