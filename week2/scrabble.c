// program to determine who has scored the highest in the game of scrabble

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototype
int score(char *word);

int main(void)
{
    // declaring strings
    char player1[50];
    char player2[50];

    // prompting the user for input
    printf("Player 1:\n");
    scanf("%s", player1);
    printf("Player 2:\n");
    scanf("%s", player2);

    // conditional on the score
    if(score(player1) > score(player2))
    {
        printf("Player 1 wins!\n");
    }
    else if(score(player1) < score(player2))
    {
        printf("Player 2 wins!\n");
    }
    else if(score(player1) == score(player2))
    {
        printf("It's a tie!\n");
    }
    return 0;
}

// calculate the score of the word put in based on the assigned capital alphabet
int score(char *word)
{
    int valueArray[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int i = 0;
    int score = 0;
    
    // looping until it hits the end and also validates if it is an alphabet, if not alphabet, ignore
    while(word[i] != '\0' && isalpha(word[i]))
    {   
        // convert the alphabet to uppercase to ensure there is no case sensitivity in calculation
        int alphabet = toupper(word[i]);

        // by subtracting the ascii value by 65, we ensure that we equate it to the position of the value assigned to that character in valueArray
        int position = (int)alphabet - 65;
        score = score + valueArray[position];

        // incrementing the i so we can move to the next character
        i++;
    }
    return score;
}