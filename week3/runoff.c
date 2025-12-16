// program to determine the winner of an election following the runoff selection
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// defining max limits that will be used later
#define MAX_CANDIDATES 9
#define MAX_VOTERS 100
#define CHAR_LENGTH 50

// defining a data structure for candidate
typedef struct
{
    char name[CHAR_LENGTH];
    int votes;
    bool eliminate;

} candidate;

// global variables
int voterPreference[MAX_VOTERS][MAX_CANDIDATES];

candidate candidates[MAX_CANDIDATES];

int voterCount;
int candidateCount;

// prototypes
int voters(void);
bool vote(int voter, int rank, char* candidateName);
void tabulate(void);
bool printWinner(void);
int findMinimum(void);
bool isTie(int minVotes);
void eliminateLoser(int minVotes);

// main function
int main(int argc, char* argv[])
{
    candidateCount = argc - 1; // gets the candidate count
    // checks if the user met the constraints and used the right command line input
    if(candidateCount < 2 || candidateCount > 9)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // initializes the data for each candidate running in the election
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        strcpy(candidates[candidateIndex].name, argv[candidateIndex + 1]);
        candidates[candidateIndex].votes = 0;
        candidates[candidateIndex].eliminate = false;
    }
    
    // calling the voters function
    voterCount = voters();
    char candidateName[CHAR_LENGTH]; // defining the input store variable
    
    // prompting the user to share their candidate preferences
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
        {
            bool preferenceSuccess = false;

            while(!preferenceSuccess)
            {
                printf("Rank %d: ", rankIndex+1);
                scanf("%49s", candidateName); // bounding the input to the width limit of 49 characters
                preferenceSuccess = vote(voterIndex, rankIndex, candidateName); // calling the vote function and running this only if there is success
            }
        }
        printf("\n");
    }
    tabulate(); // calling the tabulate function

    /* DEBUGGING
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        printf("%s: %d\n", candidates[candidateIndex].name, candidates[candidateIndex].votes);
    }
    */

    int minVotes = findMinimum(); // calling the findMinimum function

    /* DEBUGGING
    printf("minVotes: %d\n", minVotes);
    */

    // this control flow loops until either a winner is declared or there is a tie among all the remaining candidates
    while(printWinner() == false)
    {
        minVotes = findMinimum();

        if(isTie(minVotes))
        {
            printf("It's a tie.\n");
            return 2;
        }

        /* DEBUGGING
        for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
        {
            printf("%s in while before elimination: %d\n", candidates[candidateIndex].name, candidates[candidateIndex].votes);
        }
        */

        eliminateLoser(minVotes);
        tabulate();

        /* DEBUGGING
        for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
        {
            printf("%s in while after elimination: %d\n", candidates[candidateIndex].name, candidates[candidateIndex].votes);
        }
        */
    }
    return 0; // exits the loop
}

// function to get the number of voters
int voters(void)
{
    do
    {
        printf("Number of voters: ");
        scanf("%d", &voterCount);
    } while (voterCount > MAX_VOTERS || voterCount < 1);
    return voterCount;
}

// function to get the voters to declare their preferences and in case the name didn't match the candidates list, it will declare it to be an invalid vote
bool vote(int voterIndex, int rankIndex, char* candidateName)
{
    bool preferenceSuccess = false;
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(strcmp(candidateName, candidates[candidateIndex].name) == 0)
        {
            voterPreference[voterIndex][rankIndex] = candidateIndex; // YOU HAD USED THIS HERE - YOU JUST HAD TO REPEAT IT
            preferenceSuccess = true;
            break;
        }
    }
    if(preferenceSuccess == false) // in case the person the voter included in their preference list is not a valid candidate
    {
        printf("Invalid vote.\n");
    }
    return preferenceSuccess;
}

// captures the votes across the candidates based on the preference of the voters
void tabulate(void)
{
    // resets the votes counter for each candidate (useful in case of elimination)
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        candidates[candidateIndex].votes = 0;
    }
    
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
        {
            int candidateIndex = voterPreference[voterIndex][rankIndex]; // I DIDN'T THINK OF THIS - WHY?!
            if(candidates[candidateIndex].eliminate == false)
            {
                candidates[candidateIndex].votes++;
                break; // breaks in case there is a match, else loops through the next rank
            }
        }
    }
}

// determines if there is a winner i.e., candidate winning by majority
bool printWinner(void)
{
    int majority = voterCount / 2;
    bool majorityStatus = false;
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(candidates[candidateIndex].votes > majority && candidates[candidateIndex].eliminate == false)
        {
            printf("%s\n", candidates[candidateIndex].name);
            majorityStatus = true; // breaks in case there is a match
            break;
        }
    }
    return majorityStatus;
}

// determines the least number of votes gotten by a candidate against the preference of the voter
int findMinimum(void)
{
    int minVotes = MAX_VOTERS; // starting at the max sentinel, assuming all votes go to the same candidate, so as to keep moving through the min loop
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(candidates[candidateIndex].votes < minVotes && candidates[candidateIndex].eliminate == false)
        {
            minVotes = candidates[candidateIndex].votes;
        }
    }
    return minVotes;
}

// determines if there is a tie amongst all the remaining candidates
bool isTie(int minVotes)
{
    bool tie = false;
    int count = 0;
    int notEliminated = 0;
    // checking if all the remaining candidates have the same number of votes, in which an elimination is no longer possible and it is a tie
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(candidates[candidateIndex].eliminate == false)
        {
            notEliminated++;
            if(candidates[candidateIndex].votes == minVotes)
            {
                count++;
            }
        }
    }

    if(count == notEliminated)
    {
        tie = true;
    }

    return tie;
}

// eliminates the candidate with the least number of votes
void eliminateLoser(int minVotes)
{
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(candidates[candidateIndex].votes == minVotes && candidates[candidateIndex].eliminate == false)
        {
            candidates[candidateIndex].eliminate = true;
            candidates[candidateIndex].votes = 0;
        }
    }
}