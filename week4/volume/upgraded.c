#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    while(argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *oldInput = fopen(argv[1], "r");
    FILE *newOutput = fopen(argv[2], "a");

    float factor = strtof(argv[3], NULL);

    while(oldInput == NULL || newOutput == NULL)
    {
        printf("No such file found.\n");
        return 2;
    }

    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, oldInput);
    fwrite(header, HEADER_SIZE, 1, newOutput);

    int16_t *buffer = malloc(sizeof(int16_t));
    if(buffer == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(oldInput);
        fclose(newOutput);
        return 3;
    }

    while((fread(buffer, sizeof(int16_t), 1, oldInput)) > 0)
    {
        *buffer *= factor;
        fwrite(buffer, sizeof(int16_t), 1, newOutput);
    }

    fclose(oldInput);
    fclose(newOutput);
    free(buffer);

    return 0;
}