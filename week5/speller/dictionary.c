// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int sizeCounter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table (= array of linked lists)
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Cursor points to first element in corresponding list
    node *cursor = table[hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int len = strlen(word);
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += (int) toupper(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Couldn't open dictionary.\n");
        return false;
    }

    // Read strings from file
    char buffer[LENGTH + 1];
    int idx = 0;
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        // Create a node to store word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Couldn't read word.\n");
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;

        // Hash word (determine which linked list to use)
        idx = hash(n->word);

        // Insert node into hash table
        n->next = table[idx];
        table[idx] = n;

        sizeCounter++;
        idx++;
    };
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeCounter;
}

// Recursively free singly-linked list
void freeList(node *list)
{
    if (list == NULL)
    {
        return;
    }
    freeList(list->next);
    free(list);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freeList(table[i]);
        }
    }
    return true;
}