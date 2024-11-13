// Encrypt plaintext using alphabetical key input as command line argument
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LETTERS_IN_ALPHABET 26

string cipher(string s, char arg[]);

int main(int argc, string argv[])
{
    // Exit if more than 1 argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key; where key = 26 unrepeated letters.\n");
        return 1;
    }

    // Exit if key is not 26 characters
    int keyLen = strlen(argv[1]);
    if (keyLen != LETTERS_IN_ALPHABET)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char key[LETTERS_IN_ALPHABET];
    for (int i = 0; i < keyLen; i++) // Go through every character in key
    {
        // Exit if key contains repeated characters
        char c1 = argv[1][i];
        for (int j = i + 1; j < keyLen; j++)
        {
            char c2 = argv[1][j];
            if (c1 == c2)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

        // Exit if key contains non-alphabetical characters
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return 1;
        }

        // Store key
        key[i] = argv[1][i];
    }

    // Prompt for input plaintext
    string plaintext = get_string("plaintext: ");

    // Print ciphertext and exit correctly
    string ciphertext = cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

// Encipher any string with key
string cipher(string s, char arg[])
{
    // For the length of the plaintext
    for (int i = 0, strLen = strlen(s); i < strLen; i++)
    {
        if (islower(s[i]))
        {
            s[i] = tolower(arg[s[i] - 'a']);
        }

        if (isupper(s[i]))
        {
            s[i] = toupper(arg[s[i] - 'A']);
        }
    }
    return s;
}