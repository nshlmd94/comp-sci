// program to determine who has won based on who has gotten the highest number of votes

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// defining that the maximum number of voters are 9
#define MAX 9
#define CHAR_LENGTH 50

typedef struct
{
    char name[CHAR_LENGTH];
    int count;

} vote;

// prototypes
int voters(void);
bool voteCapture(int voterCount, int candidateCount, vote* voteResult);
void winner(vote* voteResult, int candidateCount);

// main functions to get candidate names as argument vectors, call voters, 
int main(int argc, char* argv[])
{
    int candidateCount = argc - 1;
    vote voteResult[candidateCount];

    // checks the validity of the user's command line arguments and if it satisfies the constraints
    if(candidateCount <= MAX && candidateCount >= 2)
    {
        for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
        {
            strcpy(voteResult[candidateIndex].name, argv[candidateIndex + 1]);
            voteResult[candidateIndex].count = 0;
        }
    }
    else
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    int voterCount = voters(); // call the voters function and assign to a variable 
    voteCapture(voterCount, candidateCount, voteResult); // call the voteCapture function
    winner(voteResult, candidateCount); // call the winner function

    return 0;
}

// program to prompt the user for the number of voters and return that
int voters(void)
{
    int voterCount;
    printf("Number of voters: ");
    scanf("%d", &voterCount);
    return voterCount;
}

bool voteCapture(int voterCount, int candidateCount, vote* voteResult)
{
    char candidateName[CHAR_LENGTH]; // user input of their voters, stays dynamic in the loop
    bool matchFound = false; // a placeholder bool to figure out if there is a match or not, if no match, will print invalid vote and return false

    // looping across the voters
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        printf("Vote %d: ", voterIndex+1);
        scanf("%s", candidateName);

        // matching against the candidates
        for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
        {
            // comparing the candidate with the user input
            if(strcmp(candidateName, voteResult[candidateIndex].name) == 0)
            {
                voteResult[candidateIndex].count++;
                matchFound = true; // updating the bool to indicate that there has been a match
            }
        }

        // an if-else inside the candidate loop would trigger on every single candidate comparison, and not just once per voter. So this is the best way to handle this
        if(matchFound == false)
        {
            printf("Invalid Vote.\n");
        }
    }
    return matchFound; // returning the bool
}
 
// function that determines the winner
void winner(vote* voteResult, int candidateCount)
{
    int max = voteResult[0].count;

    // figures out what the max votes a candidate got
    for(int index = 0; index < candidateCount; index++)
    {
        if(max < voteResult[index].count)
        {
            max = voteResult[index].count;
        }
    }

    // uses the above max to determine who all got those max votes and prints their names; best way to handle both a max and a tie
    for(int index = 0; index < candidateCount; index++)
    {
        if(max == voteResult[index].count)
        {
            printf("%s\n", voteResult[index].name);
        }
    }
}
