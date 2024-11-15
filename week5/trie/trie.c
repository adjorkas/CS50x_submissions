// Saves popular dog names in a trie
// https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ALPHABET 26
#define MAXCHAR 20

typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}
node;

// Function prototypes
bool check(char *word);
bool unload(void);
void unloader(node *current);

// Root of trie
node *root;

// Buffer to read dog names into
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./trie infile\n");
        return 1;
    }

    // File with names
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Allocate root of trie
    root = malloc(sizeof(node));

    if (root == NULL)
    {
        return 1;
    }

    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }

    // Add words (names in given file) to the trie
    while (fscanf(infile, "%s", name) == 1) // Scan single word until there are no more
    {
        node *cursor = root; // Pointer to the node we're currently at - first root, later next nodes

        for (int i = 0, n = strlen(name); i < n; i++) // For every word in name
        {
            int index = tolower(name[i]) - 'a'; // Name letter to numerical index (e.g: c is 2)
            if (cursor->children[index] == NULL) // If we didn't create a node pointing from this index in cursor before
            {

                // Make node
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new; // we make previous node point at new one we just created
            }

            // Go to node which we may have just been made
            cursor = cursor->children[index]; // First time: we're not longer at root, but the next node
        }

        // if we are at the end of the word, mark it as being a word
        cursor->is_word = true;
    }

    // HERE WE ARE DONE WITH CREATING THE TRIE
    // NOW IT'S TIME TO GET USER INPUT

    if (check(get_string("Check word: "))) // This is what we have to do for this lab
    {
        printf("Found!\n");
    }
    else
    {
        printf("Not Found.\n");
    }

    if (!unload())
    {
        printf("Problem freeing memory!\n");
        return 1;
    }

    fclose(infile);
}

// TODO: Complete the check function, return true if found, false if not found
bool check(char *word)
{
    node *cursor = root;
    // Iterate through each letter in input word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        int index = tolower(word[i]) - 'a';

        // Check if pointer isn't NULL - first root then all children...
        if (cursor->children[index] == NULL)
        {
            return false;
        }
        cursor = cursor->children[index];
    }
    if (cursor->is_word == true)
    {
        return true;
    }
    return false;
}

// Unload trie from memory
bool unload(void)
{

    // The recursive function handles all of the freeing
    unloader(root);

    return true;
}

void unloader(node *current)
{

    // Iterate over all the children to see if they point to anything and go
    // there if they do point
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // After we check all the children point to null we can get rid of the node
    // and return to the previous iteration of this function.
    free(current);
}
