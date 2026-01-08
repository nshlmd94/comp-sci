#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *listptr = malloc(sizeof(int) * 3);
    if(listptr == NULL)
    {
        return 1;
    }

    listptr[0] = 1;
    listptr[1] = 2;
    listptr[2] = 3;

    int *newptr = malloc(sizeof(int) * 4);
    if(newptr == NULL)
    {
        free(listptr); // Explain this
        return 2;
    }

    for(int i = 0; i < 3; i++)
    {
        newptr[i] = listptr[i];
    }

    newptr[3] = 4;

    free(listptr);

    listptr = newptr; // I don't understand this

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", listptr[i]); // Shouldn't this be newptr?
    }

    free(listptr);
    return 0;
}