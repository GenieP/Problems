#include <stdio.h>
#include <cs50.h>

int main(void)
{   //Get user to supply an integer     
    printf("Please give me a number for the height of the half-pyramid \n");
    int n;
    
    //Verify it is in the required range, otherwise ask for another
    do
    {
        n = GetInt();
        if (n < 0)
        {
        printf("You chose a negative number, please choose a positive one\n");
        }
        else if (n > 23)
        {
        printf("You chose too high a number! Please choose another\n");
        }
    }
    while ((n < 0)|| (n>23));
    
    //Print out the half-pyramid
    for(int count=0; count<n; count++)
    {
        
        for(int pos_s=1; pos_s<n-count; pos_s++ )
        {
            printf(" ");
        }
        
        for (int pos_h=0; pos_h<count+2; pos_h++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
