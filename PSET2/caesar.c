// CS50x - Problem Set 2
// caesar.c

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char rotate(char givenletter, int key, char startletter);

// Program begins with user input of one command line argument
int main(int argc, string argv[])
{
// check and validate the input they have given - is a single positive integer
    if (argc < 2)
    {
        printf("You have not provided a number for your key!\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("I only require 1 integer for your key!\n");
        return 1;
    }

// convert string given by user to an integer for use in encryption and validate
    int key = atoi(argv[1]);
    if (key < 1)
    {
        printf("I require a positive integer for your key!\n");
        return 1;
    }
    
// Store input text from user for encryption
    string text = GetString();
    
// Work through the string, iterating over each character
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if ( c >= 'a' && c <= 'z')
        {
            c = rotate(c, key, 'a');
            printf("%c", c);
        }
    else if (c >= 'A' && c <= 'Z')
        {
            c = rotate(c, key, 'A');
            printf("%c", c);
        }
    else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

char rotate(char givenletter, int key, char startletter)
{
    int cipher = givenletter;
    cipher = cipher - startletter;
    cipher = cipher + key;
    cipher = cipher % 26;
    cipher = cipher + startletter;
    return(char) cipher;
}
