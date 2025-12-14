// program to determine the winner of an election following the runoff selection
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100
#define CHAR_LENGTH 50

typedef struct
{
    char name[CHAR_LENGTH];
    int votes;
    bool eliminate;

} candidate;

int voterPreference[MAX_VOTERS][MAX_CANDIDATES];

candidate candidates[MAX_CANDIDATES];

int voterCount;
int candidateCount;

// prototypes
int voters(void);

// main function
int main(int argc, int argv[])
{
    candidateCount = argc - 1;
    if(candidateCount < 2 && candidateCount > 9)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        strcpy(candidates[candidateIndex].name, argv[candidateIndex + 1]);
        candidates[candidateIndex].votes = 0;
    }
    
    voterCount = voters();
    char* candidateName[CHAR_LENGTH];
    
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
        {
            printf("Rank %d", rankIndex);
            scanf("%s", candidateName);
            if(vote(voterIndex, rankIndex, candidateName))
            {
                tabulate();
            }
        }
    }

    
}

int voters(void)
{
    do
    {
        printf("Number of voters: ");
        scanf("%d", &voterCount);
    } while (voterCount > MAX_VOTERS);
    return voterCount;
}

bool vote(int voter, int rank, char* candidateName)
{
    bool preferenceSuccess = false;
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(strcmp(candidateName, candidates[candidateIndex].name))
        {
            voterPreference[voter][rank] = candidateIndex;
            preferenceSuccess = true;
        }
    }

    if(preferenceSuccess == false)
    {
        printf("Invalid vote.\n");
    }

    return preferenceSuccess;
}

void tabulate(void)
{
    
}

/*
bool vote(int voter, int rank, char* name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
*/