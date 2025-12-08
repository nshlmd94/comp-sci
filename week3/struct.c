// program to get the number of the person if the person name matches the user input

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char* name;
    char* number;

} person;

int main(void)
{
    person people[4];

    people[0].name = "Anshul Modi"; // the string in "<>" is called String Literal
    people[0].number = "+91-9988776655";

    people[1].name = "Meet Semlani";
    people[1].number = "+91-9988336644";

    people[2].name = "Anil Modi";
    people[2].number = "+91-9988774422";
    
    people[3].name = "Sangeeta Modi";
    people[3].number = "+91-9988776633";

    char userInput[128];

    printf("Enter the name: ");
    if(fgets(userInput, sizeof(userInput), stdin) == NULL)
    {
        fprintf(stderr, "Error: Unable to read the name.\n");
        return 1;
    }

    size_t length = strlen(userInput);
    if(length > 0 && userInput[length-1] == '\n')
    {
        userInput[length-1] = '\0';
    }

    // sizeof counts number of bytes in an array, so to make it to the number of "items", diving it with the type size i.e., the size of one item
    for(size_t index = 0; index < (sizeof(people) / sizeof(people[0])); index++)
    {
        if(strcmp((people[index].name), userInput) == 0)
        {
            printf("User found. Contact them at %s.\n", people[index].number);
            return 0;
        }
    }
    printf("User not found.\n");
    return 1;
}

