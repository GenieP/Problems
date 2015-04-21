/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"
#include <stdio.h>
/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{
    int startpoint = 0;
    int endpoint = n-1;
        
    while(endpoint >= startpoint)
    {
        int midpoint = (startpoint + endpoint) / 2;
        if(values[midpoint] == value)
        {
            return true;
        }
        else if (values[midpoint] > value)
        {
            endpoint = midpoint - 1;
        }
        else 
        {
            startpoint = midpoint + 1;
        }
    }
    return false;   
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int min_loc = i;
        int minimum = values[i];
        for(int j = i+1; j < n; j++)
        {
            if(minimum > values[j])
            {
                minimum = values[j];
                min_loc = j;   
            }
        }
        values[min_loc] = values[i];
        values[i] = minimum;
        }
    return; 
}
