#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{   //Get user to supply an amount of change due     
    printf("Hello, how much change is owing? \n");
    float change;
     
    //Check input is valid, otherwise ask again
    do
    {   
        change = GetFloat();
        if (change < 0.00) 
        {
        printf("You selected a negative amount, please enter a positive amount\n");
        }
        else if (change == 0.00)
        {
        printf("You selected no change! Please enter another amount\n");
        }
    }
    while (change <= 0.00);
    
    //Convert the figure given to cents
    double change_int = round(change*100);
    
    //Calculate number of coins
    int coins = 0;
    do 
    {   
        if (change_int >=25)  
        {
        change_int = change_int-25;
        coins++;
        }
        else if (change_int >=10)
        {
        change_int = change_int-10;
        coins++;
        }
        else if (change_int >=5)
        {
        change_int = change_int-5;
        coins++;
        }
        else if (change_int <5)
        {
        change_int = change_int-1;
        coins++;
        }
    }
    while (change_int>0);
    
    //Display number of coins used
    printf("%i\n", coins);
}
