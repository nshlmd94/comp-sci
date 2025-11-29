// program to say hello to the user by prompting the user for their name

#include <stdio.h>

int main(void)
{
    char name[100];
    printf("Hi, what's your name?:\n");
    scanf("%s", name);
    printf("Hello, %s\n", name);
}