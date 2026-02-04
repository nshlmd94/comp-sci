// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// ???? Choose number of buckets in hash table
const unsigned int N = 10000;

int countSize = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }
    else
    {
        for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
        {
            if (strcasecmp(ptr->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    int hashValue;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        sum = sum + toupper(word[i]) - toupper(word[0]);
    }
    if (sum > 0)
    {
        hashValue = sum / len;
    }
    else
    {
        hashValue = -sum / len;
    }
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int index;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("File did not load.\n");
        return false;
    }

    char buffer[LENGTH + 1];
    int counter = 0;
    char c;

    while (fread(&c, sizeof(c), 1, file) != 0)
    {
        if (c != '\n')
        {
            buffer[counter] = c;
            counter++;
        }
        else
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            buffer[counter] = '\0';
            index = hash(buffer);

            if (table[index] == NULL)
            {
                strcpy(n->word, buffer);
                countSize++;
                n->next = NULL;
                table[index] = n;
            }
            else
            {
                for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
                {
                    if (ptr->next == NULL)
                    {
                        strcpy(n->word, buffer);
                        countSize++;
                        n->next = NULL;
                        ptr->next = n;
                        break;
                    }
                }
            }
            counter = 0;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return countSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int index = 0; index < N; index++)
    {
        if (table[index] != NULL)
        {
            node *ptr = table[index];
            while (ptr != NULL)
            {
                node *next = ptr->next;
                free(ptr);
                ptr = next;
            }
        }
    }

    return true;
}
