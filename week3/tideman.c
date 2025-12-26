// build a program to select a winner based on tideman form of voting that chooses based on preference of ranked pairs
// call all relevant libraries required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// define max limits to be used later
#define MAX_CANDIDATES 9
#define MAX_VOTERS 99
#define NAME_LENGTH 50

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX_CANDIDATES][MAX_CANDIDATES];

// locked[i][j] means i is locked in over j
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];

// define custom types
typedef char * string;

// Each pair has a winner, loser
typedef struct pair
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX_CANDIDATES];
pair pairs[MAX_CANDIDATES * (MAX_CANDIDATES - 1) / 2];

int pairCount;
int candidateCount;
int voterCount;

// Function prototypes
bool vote(int rank, string candidateName, int ranks[]);
void recordPreferences(int ranks[]);
void addPairs(void);
void sortPairs(void);
void lockPairs(void);
void printWinner(void);

int main(int argc, char* argv[])
{
    candidateCount = argc - 1; // calculate the count of candidates in the election

    // check if valid range of candidate names have been given as a command line input or not
    if(candidateCount < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
    
    if(candidateCount > MAX_CANDIDATES)
    {
        printf("Max candidates competitng can only be %d.\n", MAX_CANDIDATES);
        return 2;
    }
    
    // assign the candidate names to an array via a loop
    for(int index = 0; index < candidateCount; index++)
    {
        candidates[index] = argv[index+1];
    }    

    // initialize the locked and preferences to 0 for all
    for(int i = 0; i < candidateCount; i++)
    {
        for(int j = 0; j < candidateCount; j++)
        {
            locked[i][j] = 0;
            preferences[i][j] = 0;
        }
    }
    
    // ask for number of voters and keep nudging until it meets the range constraints
    do
    {
        printf("Enter the number of voters: \n");
        scanf("%d", &voterCount);
    } 
    while(voterCount < MAX_VOTERS && voterCount > 1);

    // capture the preferences
    int ranks[MAX_CANDIDATES];
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
        {
            bool voteSuccess = false;
            string name;
            while(!voteSuccess)
            {
                printf("Rank %d: ", rankIndex+1);
                scanf("%{49s", name);
                voteSuccess = vote(rankIndex, name, ranks);
            }
        }
        printf("\n");
        recordPreferences(ranks);
    }

    // TO DO: Add the other functions

}

// function to check if the rank's vote is valid and if valid, then store it in an array as preference
bool vote(int rank, string candidateName, int ranks[])
{
    bool voteStatus = false;
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(strcmp(candidates[candidateIndex], candidateName) == 0)
        {
            ranks[rank] = candidateIndex;
            voteStatus = true;
            break;
        }
    }
    if(voteStatus == false)
    {
        printf("Invalid Vote.\n");
    }
    return voteStatus;
}

// record the preference of a voter's for a candidate over the others
void recordPreferences(int ranks[])
{
    for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
    {
        for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
        {
            if(rankIndex < candidateIndex)
            {
                preferences[ranks[rankIndex]][ranks[candidateIndex]]++;
            }
        }
    }
}

void addPairs(void)
{

}

void sortPairs(void)
{

}

void lockPairs(void)
{

}

void printWinner(void)
{

}

