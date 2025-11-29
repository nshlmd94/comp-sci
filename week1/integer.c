// write a program to test if the integer given as an input is positive or not and keep prompting the user until they enter a positive integer

#include <stdio.h>

// prototypes of the function to let the program know its signature
int getInteger(void);
void paradise(int a);

// executing main while calling the functions
int main(void)
{
    int n = getInteger();
    paradise(n);
}

// this function checks if i is a positive integer and if it is, then returns it
int getInteger(void)
{
    int i = 0;
    while (i <= 0)
    {
        printf("Enter a positive integer: ");
        scanf("%d", &i);
    }
    return i;
}

// this function prints Paradise times the value of b
void paradise(int a)
{
    for(int b = 0; b < a; b++)
    {
        printf("Paradise\n");
    }
}