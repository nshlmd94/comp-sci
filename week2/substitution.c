// program to encrypt a plain text into cipher text using a substitution key

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 1048

// prototypes
bool keyArgumentChecker(const char *key);
bool keyLengthChecker(const char *key);
bool keyUniqueCheck(const char *key);
void encryptText(char *key, char *plainText, char *cipherText);

int main(int argc, char *argv[])
{
    // initializing the strings
    char plainText[MAX_LENGTH];
    char cipherText[MAX_LENGTH];

    // calling the helper functions to check if the user entered enough command line arguments and if the string is all alpha
    if(argc != 2 || !keyArgumentChecker(argv[1]))
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }

    // calling the helper functions to check if the user key is 26 in length and if it contains all unique alphabets only once
    if (!keyLengthChecker(argv[1]) || !keyUniqueCheck(argv[1]))
    {
        printf("Key must contain 26 unique characters.\n");
        return 1;
    }

    // using fgets to get the user input for plain text beyond just first whitespace
    printf("Plaintext: ");
    if(fgets(plainText, sizeof(plainText), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read the input.\n");
        return 1;
    }

    // removing the new line that fgets adds and replacing it with \0
    size_t length = strlen(plainText);
    if(length > 0 && plainText[length-1] == '\n')
    {
        plainText[length-1] = '\0';
    }

    // calling the encrypt text function to encrypt the user text into a cipher
    encryptText(argv[1], plainText, cipherText);

    // printing out the ciphertext
    printf("Ciphertext: %s\n", cipherText);
    return 0;
}

// helper function to check if the key is all alpha
bool keyArgumentChecker(const char *key)
{
    for(size_t index = 0; key[index] != '\0'; index++)
    {
        if(!isalpha((unsigned char)key[index]))
        {
            return false;
        }
    }
    return true;
}

// helper function to check the length of the key and if it is 26
bool keyLengthChecker(const char *key)
{
    size_t length = strlen(key);
    if(length != 26)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// helper function to check if the key includes all alphabets only once
bool keyUniqueCheck(const char *key)
{
    for(size_t i = 0; i < 26; i++)
    {
        for(size_t j = i+1; j <= 26; j++)
        {
            if(key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}

// function to encrypt the plaintext
void encryptText(char *key, char *plainText, char *cipherText)
{
    int position = 0;
    size_t length = strlen(plainText);

    for(size_t index = 0; index < length; index++)
    {
        if(isalpha(plainText[index]))
        {
            if(isupper(plainText[index]))
            {
                position = ((int)plainText[index]) - 65;
                cipherText[index] = toupper(key[position]);
            }
            if(islower(plainText[index]))
            {
                position = ((int)plainText[index]) - 97;
                cipherText[index] = tolower(key[position]);
            }
        }
        else
        {
            cipherText[index] = plainText[index];
        }
    }
    cipherText[length] = '\0';
}