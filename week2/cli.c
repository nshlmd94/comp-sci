// program to take name as user input via command line argument and print hello <name>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        for(int i = 1; i < argc; i++)
        {
            printf("hello, %s\n", argv[i]);
        }
    }
    else
    {
        printf("hello, world\n");
    }
}