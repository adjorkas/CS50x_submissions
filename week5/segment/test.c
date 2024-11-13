// Understanding making singly linked lists of char * values
#include <stdlib.h>

typedef struct node
{
    char *value;
    struct node *next;
}
node;

int main(void)
{
    // Declare list
    node *list = NULL;

    // Dynamically allocate space for a new node
    node *n = malloc(sizeof(node));

    // Check to make sure we didn't run out of memory
    if (n == NULL)
        return 1;

    // Initialize node's value field
    n -> value = malloc(sizeof(char) * 3);
    n -> value = "Hi";

    // Initialize the node's next field
    n -> next = NULL;

    // Return a pointer to the newly created node
    list = n;

    return 0;
}