// program to count the length of the string the user inputs

#include <stdio.h>

// prototype
int stringLength(char *words);

// main function to run the program
int main(void)
{
    char input[20];

    printf("Enter the string:\n");
    scanf("%s", input);

    int length = stringLength(input);
    printf("%d\n", length);

    return 0;
}

// function to calculate the length of the string
int stringLength(char *words)
{
    int i = 0;
    while(words[i] != '\0')
    {
        i++;
    }
    return i;
}