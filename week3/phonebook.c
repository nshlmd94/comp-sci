// program to get the phone number when a user gives a name that is present in the list

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char userName[128];
    printf("Enter the person's name: ");
    if(fgets(userName, sizeof(userName), stdin) == NULL)
    {
        fprintf(stderr, "Error: Unable to read the name.\n");
    }

    int length = strlen(userName);
    if(length > 0 && userName[length-1] == '\n')
    {
        userName[length-1] = '\0';
    }

    char* name[] = {"Anshul Modi", "Meet Semlani", "Anil Modi", "Sangeeta Modi"};
    char* number[] = {"+91-9988776655", "+91-9988336644", "+91-9988774422", "+91-9988776633"};

    for(size_t index = 0; index < (sizeof(name) / sizeof(name[0])); index++)
    {
        if(strcmp(userName, name[index]) == 0)
        {
            printf("User found. Here's their number: %s\n", number[index]);
            return 0;
        }
    }
    printf("User not found.\n");
    return 1;
}