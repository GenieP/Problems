// CS50x - Problem Set 2
// vigenere.c

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Declaration of function
char rotate(char givenletter, char keyletter, char startletter);

// Program begins with user input of one command line argument
int main(int argc, string argv[])
{

    
// Check and validate the input they have given - is a single keyword
    if (argc < 2)
    {
        printf("You have not provided a keyword!\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("I only require a single keyword!\n");
        return 1;
    }
    
// Check that the input is alphabetical only 
    string keyword = argv[1];
    int keylength = strlen(keyword);   
    for (int i = 0, j = 0, n = keylength;  i < n; i++, j++)
    { 
        char keyletter = keyword[j];

        if (isalpha(keyletter)) 
        {  
            continue;
        }
        else
        {   
            printf("Your keyword can only be letters of the alphabet!\n");
            return 1;
        }
    }
        
// Prompt user for text and store input for encryption
    string text = GetString();
    
// Work through the string, iterating over each character
    for (int i = 0, j = 0, n = strlen(text); i < n; i++, j++)
    {
        char c = text[i];
        char keyletter = keyword[j % keylength];
        if ( c >= 'a' && c <= 'z')
        {
            keyletter = tolower(keyletter);
            c = rotate(c, keyletter, 'a');
            printf("%c", c);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            keyletter = toupper(keyletter);
            c = rotate(c, keyletter, 'A');
            printf("%c", c);
        }
        else
        {
            printf("%c", c);
            j--;
        }
    }
    printf("\n");
} 
    
char rotate(char givenletter, char keyletter, char startletter)
{
    
    int cipher = givenletter;
    cipher = cipher - startletter;
    cipher = cipher + (keyletter - startletter);
    cipher = cipher % 26;
    cipher = cipher + startletter;
    return(char) cipher;
}
