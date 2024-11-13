// Encipher text by key input as command line argument

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int ALPHABET_LETTERS = 26;

string encipher(int k, string s);

int main(int argc, string argv[])
{
    // Exit if more than 1 argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Exit if non-numerical input
    for (int i = 0, keyLen = strlen(argv[1]); i < keyLen; i++)
    {
        bool isNum = isdigit(argv[1][i]);
        if (!isNum)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Key to int
    int key = atoi(argv[1]);

    // Get user input and print ciphertext
    string plaintext = get_string("plaintext: ");
    string ciphertext = encipher(key, plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

// Encipher any string by key
string encipher(int k, string s)
{
    string cipher = s;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (isalpha(cipher[i]))
        {
            // Determine start of alphabetical index
            char a = (isupper(cipher[i])) ? 'A' : 'a';
            // Convert ASCII to alphabetical index
            cipher[i] -= a;
            // Shift alphabetical index using formula
            cipher[i] = (cipher[i] + k) % ALPHABET_LETTERS;
            // Convert result back to ASCII
            cipher[i] += a;
        }
    }
    return cipher;
}