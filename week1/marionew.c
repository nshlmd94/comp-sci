#include <stdio.h>

int getInteger(void);
void drawLines(int lines, int row);

int main(void)
{
    int lines = getInteger();

    for(int row = 0; row < lines; row++)
    {
        drawLines(lines, row);
    }
    return 0;
}

int getInteger(void)
{
    int value;
    do
    {
        printf("Enter a positive integer:\n");
        scanf("%d", &value);
    } 
    while (value <= 0);
    return value;
}

void drawLines(int lines, int row)
{
    for(int space = 1; space < lines - row; space++)
    {
        printf(" ");
    }

    for(int hash = row; hash >= 0; hash--)
    {
        printf("#");
    }

    printf("  ");

    for(int hash = row; hash >= 0; hash--)
    {
        printf("#");
    }

    printf("\n");
}