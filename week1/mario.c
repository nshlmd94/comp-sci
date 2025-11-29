// writing a program to build a mario block

#include <stdio.h>

int getInteger(void);

int main(void)
{
    int lines = getInteger();
    for(int row = 0; row < lines; row++)
    {
        for(int space = 1; space < lines - row; space++)
        {
            printf(" ");
        }

        for(int hash = row; hash >= 0 ; hash--)
        {
            printf("#");
        }

        printf("\n");
    }

}

int getInteger(void)
{
    int a;
    do
    {
        printf("Enter a positive integer:\n");
        scanf("%d", &a);
    } 
    while (a <= 0);

    return a;
}