#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    char buffer;
    int counter = 0;
    int smallest = INT16_MAX;
    int largest = 0;
    int wordCount = 0;

    FILE *file = fopen("dictionaries/large", "r");
    if (file == NULL)
    {
        printf("File unsupported.\n");
        return 1;
    }

    while (fread(&buffer, sizeof(buffer), 1, file) != 0)
    {
        if (buffer != '\n')
        {
            counter++;
        }
        else
        {
            if (counter < smallest)
            {
                smallest = counter;
            }

            if (counter > largest)
            {
                largest = counter;
                
            }

            wordCount++;
            counter = 0;
        }
    }

    if (counter > 0)
    {
        if (counter < smallest)
        {
            smallest = counter;
        }

        if (counter > largest)
        {
            largest = counter;

        }
        
        wordCount++;
    }
    
    fclose(file);

    printf("Smallest: %d\n", smallest);
    printf("Largest: %d\n", largest);
    printf("Word Count: %d\n", wordCount);

    return 0;
}