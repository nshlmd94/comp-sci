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
    if(card == NULL)
    {
        printf("The file %s can't be opened.\n", infile);
        return 2;
    }

    int count = 0;
    
    BYTE buffer[BLOCK];

    while((fread(buffer, 1, BLOCK, card)) == BLOCK)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            count++;
        
            int fileNumber = 000 + count;

            char fileName[15]; // buffer to store the concatenated filename with filetype
            sprintf(fileName, "%d.jpg", fileNumber);

            // open a new JPEG file that we start writing to; use a counter to name the files correctly
            FILE *img = fopen(fileName, "w");

            fwrite(buffer, 1, BLOCK, img); 

            while(!= 0xff)
            {
                fread(buffer, 1, BLOCK, card);

                if((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef)))
                {
                    break;
                }

                fwrite(buffer, 1, BLOCK, img); 
            }

            fclose(img);
        }

        if(img != NULL)
        {
            fwrite(buffer, 1, BLOCK, img);
        }
    }
    fclose(card);
    return 0;
}