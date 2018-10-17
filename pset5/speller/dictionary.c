// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// for each word found in the dictionary text file => store it in the dictionary data structure
// create representation for the dictionary (hash table)
// create nodes (linked lists)
typedef struct node
{
    char word [LENGTH + 1]; // LENGTH == 45 (see dictionary.h)
    struct node *next;
}
node;

node *hashtable[NUM_BUCKETS]; // NUM_BUCKETS == 143091 (see dictionary.h) => number of words in large dictionary file

// count words in dictionary
int word_count = 0;

// A case-insensitive implementation of the djb2 hash function.
// Adapted by Neel Mehta from
// http://stackoverflow.com/questions/2571683/djb2-hash-function.
unsigned int hash_word(const char* word)
{
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % NUM_BUCKETS; // Must return an index that's less than the number of buckets => use % to ensure this
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // char *dictionary = address of starting point of the dictionary file
    // FILE *file = address of the pointer of the file's "reading cursor"

    // populate hash table with words in dictionary file
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // store word in array
    char word[LENGTH+1];

    // scan dictionary word by word
    while (fscanf(file, "%s", word) != EOF) // takes dict. file, looks for a string, saves string in variable "word"
    {
        // 2. malloc a node for each word of file
        node *new_node = malloc(sizeof(node));
        // 3. for each created node check if malloc succeeded
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // copy word into node
        else
        {
            strcpy(new_node -> word, word);
        }
        word_count++;

        // hash the word and insert new node into linked list
        // new node should point to node that was previously first value in liked list
        int head = hash_word(word);
        new_node->next = hashtable[head];
        hashtable[head] = new_node;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
