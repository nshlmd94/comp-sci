// program to turn a plaintext into a cipher text with the help of a key on alphabets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 1028

// prototypes
bool isDigitOnly(char *key);
void plainToCipher(char *plaintext, int key, char *ciphertext);

int main(int argc, char *argv[])
{
    char plaintext[MAX_LENGTH];
    char ciphertext[MAX_LENGTH];  

    // exit the program if the user doesn't pass one command line argument that can used as a key
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    bool keyInput = isDigitOnly(argv[1]);
    if(keyInput != 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // prompt the user for the plaintext input
    printf("Plaintext: ");
    if(fgets(plaintext, sizeof(plaintext), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read the input.\n");
        return 1;        
    }

    // convert the key that was passed as a char * i.e., string to an int with atoi, as a part of stdlib.h
    int key = atoi(argv[1]);

    plainToCipher(plaintext, key, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

bool isDigitOnly(char *keyInput)
{
    int keyDigit = atoi(keyInput);
    if(isdigit(keyDigit))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// creating a void function and not returning anything because returning a string without a heap can only be possible with this output buffer of char *ciphertext which is actually initialized in main
void plainToCipher(char *plaintext, int key, char *ciphertext)
{
    // removed the \n (newline) that is added from fgets 
    size_t length = strlen(plaintext);
    if(length > 0 && plaintext[length-1] == '\n')
    {
        plaintext[length-1] = '\0';
    }

    // logic to rotate and wrap the key around only alphabets and then modify it to get the ciphertext
    for(size_t index = 0; index < length; index++)
    {
        int asciiValuePlain = (int)plaintext[index];
        int asciiValueCipher = 0;

        if(isalpha(plaintext[index]))
        {
            if(isupper(plaintext[index]))
            {
                asciiValueCipher = ((asciiValuePlain - 65) + key) % 26;
                ciphertext[index] = (char)(asciiValueCipher + 65);
            }
            else
            {
                asciiValueCipher = ((asciiValuePlain - 97) + key) % 26;
                ciphertext[index] = (char)(asciiValueCipher + 97);
            }
        }
        else
        {
            asciiValueCipher = asciiValuePlain;
            ciphertext[index] = (char)asciiValueCipher;
        }
    }
    // a string in C is never a string until \0 is added at the end of the string
    ciphertext[length] = '\0';
}

