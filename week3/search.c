// program to run a search in the array of integers provided compared to the user input

#include <stdio.h>

int main(void)
{
    int user_input = 0;
    int array[] = {12, 53, 3, 234, 62, 56, 216, 353};
    printf("Enter a number:\n");
    scanf("%d", &user_input);

    for(int index = 0; index < (sizeof(array) / sizeof(array[0])); index++)
    {
        if(user_input == array[index])
        {
            printf("Found.\n");
            return 0;
        }
    }
    printf("Not found.\n");
    return 1;
}