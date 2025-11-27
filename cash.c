// this is a greedy algorithm program to minimize the number of coins that a vendor gives out against the change owed to the customer

#include <stdio.h>

int getChange(void); // prototype

// main function for greedy algo
int main(void)
{   
    int coin = 0;
    int change = getChange();

    while (change > 0)
    {
        if (change >= 25)
        {
            change -= 25;
            coin++;
        }
        else if (change >= 10)
        {
            change -= 10;
            coin++;
        }
        else if (change >= 5)
        {
            change -= 5;
            coin++;
        }
        else if (change >= 1)
        {
            change -= 1;
            coin++;
        }
        else
        {
            change = change;
        }
        
    }
    printf("%d\n", coin);
    return 0;
}

// user input
int getChange(void)
{
    int change;
    do
    {
        printf("Enter the change value:\n");
        scanf("%d", &change);
    } 
    while (change <= 0);
    return change;
    
}