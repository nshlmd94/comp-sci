// program to determine the reading grade level of the text provided by the user

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 1000

// prototypes
float readingLevel(const char *reading);

int main(void)
{
    char reading[MAX_LENGTH];

    printf("Enter the text:\n");

    // fgets will safely read a whole line, including spaces / whitespaces
    if(fgets(reading, sizeof(reading), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read the input.\n");
        return 1;
    }

    // stripping, in case there is a trailing new line
    size_t length = strlen(reading);
    if(length > 0 && reading[length-1] == '\n')
    {
        reading[length-1] = '\0';
    }

    int level = readingLevel(reading);

    if(level < 1)
    {
        printf("Below level 1.\n");
    }
    else if(level > 16)
    {
        printf("Level 16+.\n");
    }
    else
    {
        printf("Level %d.\n", level);
    }

    return 0;
}

// calculating reading level; choosing not to abstract it across multiple functions, since I can use the same loop
float readingLevel(const char *reading)
{
    int index = 0;
    float space = 0;
    float letter = 0;
    float period = 0;
    int length = strlen(reading);

    // looping until it hits the end of the input sting
    for(index = 0; index < length; index++)
    {
        // running a condition to count the value occurances and using them to calculate the level
        if(reading[index] == ' ')
        {
            // indicates the number of words e.g., a sentence with 4 words will have 3 spaces, so on and so forth
            space++;
        }
        else if(isalpha(reading[index]))
        {
            // indicates all alphabets present
            letter++;
        }
        else if(reading[index] == '.' || reading[index] == '!' || reading[index] == '?')
        {
            // indicates the number of sentences based on number of sentence terminations
            period++;
        }
    }
    
    // calculating the components of the equation
    float averageLetters = (letter / (space + 1)) * 100;
    float averageSentences = (period / (space + 1)) * 100;
    
    float level = 0.0588 * averageLetters - 0.296 * averageSentences - 15.8;

    return round(level);
}
