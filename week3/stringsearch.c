// program to search for your name in an array of names

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER 248

int main(void)
{
    char user_input[BUFFER];
    printf("Enter a one word string: ");
    scanf("%s", user_input);

    char* array[] = {"Anshul", "Meet", "Pranjali", "Niharika", "Rohini", "Anil", "Sangeeta"};
    for(size_t index = 0; index < (sizeof(array) / sizeof(array[0])); index++)
    {
        if(strcmp(array[index], user_input) == 0)
        {
            printf("You are on the list.\n");
            return 0;
        }
    }
    printf("Oops, can't find ya.\n");
    return 1;
}