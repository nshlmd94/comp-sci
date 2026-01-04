#include <stdio.h>
#include <stdlib.h>

#define HEADER 4
#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int length = argc - 1;

    // remind the user of the usage of the CLI in case the command line argument length is less than 1
    if(length != 1)
    {
        printf("Usage: <program name> <forensic card name>\n");
        return 1;
    }

    char *infile = argv[1];

    // open the file that the user shared as a part of the command line input in the read mode and store it in the memory
    FILE *card = fopen(infile, "r");
    FILE *img = NULL;

    if(card == NULL)
    {
        printf("The file %s can't be opened.\n", infile);
        return 2;
    }

    int count = 0;

    BYTE buffer[BLOCK];

    while(fread(buffer, 1, BLOCK, card) == BLOCK) // if nearing end of file then fread will be less than BLOCK
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if(img != NULL)
            {
                fclose(img);
            }

            char imgName[15]; // buffer to store the concatenated filename with filetype
            sprintf(imgName, "%03i.jpg", count);
            count++;

            img = fopen(imgName, "w");
            fwrite(buffer, 1, BLOCK, img);
        }
        else if(img != NULL)
        {
            fwrite(buffer, 1, BLOCK, img);
        }
    }

    if(img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}

/*
What I learnt: "managing file state with NULL pointers"
1. I could set the img pointer to NULL in the beginning
2. I could then use it to compare with NULL to figure out if I have an open img or not - thereby closing it in case I do have one open and found a new jpeg else move to the other block and keep writing
3. Close the last image after the while loop hits the end of the raw file
*/