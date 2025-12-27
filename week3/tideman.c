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
bool checkCycle(int winner, int loser);

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
            locked[i][j] = 0; // setting the locked graph to zero
            preferences[i][j] = 0;
        }
    }
    
    // ask for number of voters and keep nudging until it meets the range constraints
    do
    {
        printf("Enter the number of voters: ");
        scanf("%d", &voterCount);
        printf("\n");
    } 
    while(voterCount > MAX_VOTERS && voterCount < 1);

    // capture the preferences
    int ranks[MAX_CANDIDATES];
    for(int voterIndex = 0; voterIndex < voterCount; voterIndex++)
    {
        for(int rankIndex = 0; rankIndex < candidateCount; rankIndex++)
        {
            bool voteSuccess = false;
            char name[NAME_LENGTH];
            while(!voteSuccess)
            {
                printf("Rank %d: ", rankIndex+1);
                scanf("%49s", name);
                voteSuccess = vote(rankIndex, name, ranks);
            }
        }
        printf("\n");
        recordPreferences(ranks); // creates a 2D array (matrix) of the voter preferences
    }

    // calling all relevant helper functions
    addPairs();
    sortPairs();
    lockPairs();

    printWinner();

    return 0;
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
    pairCount = 0; // initializing it to 0, so it can used to index the pairs data structure
    for(int i = 0; i < candidateCount; i++)
    {
        for(int j = 0; j < candidateCount; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                pairs[pairCount].winner = i;
                pairs[pairCount].loser = j;
                pairCount++;
            }
        }
    }
}

// implementation of 'selection sort' to sort the pairs in descending order
void sortPairs(void)
{
    int strength[pairCount];
    
    for(int index = 0; index < pairCount; index++)
    {
        strength[index] = preferences[pairs[index].winner][pairs[index].loser];
    }

    for(int loopIndex = 0; loopIndex < pairCount-1; loopIndex++)
    {
        int maxValue = strength[loopIndex];
        int tempIndex = loopIndex;
        for(int elementIndex = loopIndex+1; elementIndex < pairCount; elementIndex++)
        {
            if(maxValue < strength[elementIndex])
            {
                maxValue = strength[elementIndex];
                tempIndex = elementIndex;
            }
        }

        pair tempValue = pairs[tempIndex];
        int tempStrength = strength[tempIndex];

        pairs[tempIndex] = pairs[loopIndex];
        strength[tempIndex] = strength[loopIndex];

        pairs[loopIndex] = tempValue;
        strength[loopIndex] = tempStrength;
    }
}

// locking in the pairs while checking there is no cycle created
void lockPairs(void)
{
    for(int pairIndex = 0; pairIndex < pairCount; pairIndex++)
    {
        int winner = pairs[pairIndex].winner;
        int loser = pairs[pairIndex].loser;

        if(checkCycle(winner, loser) == false)
        {
            locked[winner][loser] = true;
        }
    }
}

// printing the winner of the election by checking which candidate is the source i.e., doesn't have any arrows pointing to it (no presence in j)
void printWinner(void)
{
    int isNotSource[candidateCount];

    // initialization of the array to 0
    for(int i = 0; i < candidateCount; i++)
    {
        isNotSource[i] = 0;
    }

    // counting which candidates have a presence in j i.e., have arrows pointing towards them
    for(int i = 0; i < candidateCount; i++)
    {
        for(int j = 0; j < candidateCount; j++)
        {
            if(locked[i][j] == 1)
            {
                isNotSource[j]++;
            }
        }
    }

    // if the isNotSource is 0, then the candidates has no arrows pointing towards it, hence they are declared the winner
    for(int index = 0; index < candidateCount; index++)
    {
        if(isNotSource[index] == 0)
        {
            printf("The winner is: %s\n", candidates[index]);
        }
    }
}

// helper function to the lockPairs; takes in locked graph and and checks it for cycle via a base case and recursion
bool checkCycle(int winner, int loser)
{
    bool cycleStatus = false; // sets the cycle status to false

    // base case: checks if the loser points towards the winner -> if it does, then returns true, because it creates a cycle
    if(locked[loser][winner] == true)
    {
        cycleStatus = true;
        return cycleStatus;
    }

    // if the base condition is false, then it check if the loser points towards another candidate, if it does, then it calls the checkCycle recursively to see if it points to the winner
    for(int candidateIndex = 0; candidateIndex < candidateCount; candidateIndex++)
    {
        if(locked[loser][candidateIndex] == true)
        {
            cycleStatus = checkCycle(winner, candidateIndex);
            // if true is returned i.e., a cycle is found, then exit early
            if(cycleStatus == true)
            {
                return cycleStatus;
            }
        }
    }

    return cycleStatus; // returns the status of the cycle
}
