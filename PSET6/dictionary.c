/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"
 
 
// declare hashtable - array of node pointers
node* indexlist[HASHSIZE];
 
// declare linked list
struct node list;
node* new_node; char* d_word;
 
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
 
// declare word counter and hashvalue
unsigned int wordcount = 0; int hashvalue;
 
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if(!file)
    {
        printf("Could not open dictionary file\n");
        return 1;
    }
    for (int i = 0; i <= HASHSIZE; i++)
    {
        indexlist[i] = (node*)malloc(sizeof(node));
        indexlist[i]->next = NULL;
    }  
    
    // loop through dictionary words*/
    char* tmp = malloc(LENGTH + 1) ;
    while(fscanf(file, "%s", tmp) != EOF)
    { 
        // hash the word, returning the basket it fits into
        hashvalue = hash(tmp);
        wordcount++;  
        // allocate memory for word from dictionary file
        node* new_node = malloc(sizeof(node));
        strcpy(new_node->d_word, tmp);
        // put word into relevant list
        new_node->next = indexlist[hashvalue]->next;
        indexlist[hashvalue]->next = new_node;
   }
   fclose(file);
   free (tmp);
   return true;
}
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    // copy const to temp variable
    char* temp = malloc(strlen(word)+1);
    strcpy(temp, word);
    
    // convert to lower case
    for(int i = 0, a = strlen(temp); i <= a; i++)
    {
        temp[i] = tolower(temp[i]);
    }
    
    //hash text string
    hashvalue = hash(temp);
    
    //iterate through linked list, and compare
    node* iterator = indexlist[hashvalue]->next; 
    int compare;
    
    while(iterator != NULL)
    {   
        compare = strcmp(temp, iterator->d_word);
        if(compare == 0)
        {
            free(temp);
            return true;
        }
        iterator = iterator->next;
    }
    free(temp);
    return false;
} 
 
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}
 
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i <= HASHSIZE; i++)
    {   
        node* iterator = indexlist[i];
        while(iterator != NULL)
        { 
            node* temp = iterator;
            iterator = iterator->next;
            free (temp);
        }
    }
return true;
}
 
// hash function
int hash(char* d_word)
{
    unsigned int hashvalue = 0;
    for(int i = 0, n = strlen(d_word); i < n; i++)
    {
        hashvalue = (hashvalue << 2) ^ d_word[i];
    }
    return hashvalue % HASHSIZE;
}
