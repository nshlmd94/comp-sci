#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// defining a data structure (a linked list) indicating a person with their allele and relationship
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

// defining global variables that are going to be constants throughout execution
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// function prototypes
person *createFamily(int generations);
void printFamily(person *p, int generation);
void freeFamily(person *p);
char randomAllele();

// executing the main function
int main(void)
{
    srandom(time(0)); // WHAT IS THIS FOR???
    
    person *p = createFamily(GENERATIONS); // creating a new family with three generations, returning a pointer to the most recent generation of the family

    printFamily(p, 0); // print family with blood types

    freeFamily(p); // free family members

    return 0;
}

person *createFamily(int generations)
{
    person *newPerson = malloc(sizeof(person));

    if(newPerson != NULL)
    {
        newPerson->parents[0] = NULL;
        newPerson->parents[1] = NULL;
        newPerson->alleles[0] = 0;
        newPerson->alleles[1] = 0;
    }

    if(generations > 1)
    {
        // creating parents; this is basically recursion and we are now going to create an execution stack, so even if I started at 3 the allele assignment will first move deep to the base case and then come up
        // the recursion here changes the primary argument passed in the createFamily function
        person *parent0 = createFamily(generations - 1);
        person *parent1 = createFamily(generations - 1);

        // assigning pointers to parents from child i.e., newPerson
        newPerson->parents[0] = parent0;
        newPerson->parents[1] = parent1;

        // alleles inherited from parents
        newPerson->alleles[0] = parent0->alleles[random() % 2]; // oh shit, this is soo soo cool; we are essentially choosing one of the random alleles between 0 and 1 as the index from the 0th parent and assigning it to the 0th allele of child
        newPerson->alleles[1] = parent1->alleles[random() % 2]; // we are doing the same as above but for the 1th parent and assigning to the 1th element of the child
    }
    else
    {
        // grandparents or rather the oldest generation assignment
        newPerson->parents[0] = NULL;
        newPerson->parents[1] = NULL;
        
        newPerson->alleles[0] = randomAllele();
        newPerson->alleles[1] = randomAllele();
    }

    // returning the child
    return newPerson;
}

void printFamily(person *p, int generation)
{
    // handling the base case of NULL as pointer i.e., hits the oldest generation, then exit
    if(p == NULL)
    {
        return;
    }

    // space indentation while printing - default is 4 and for printing we pass 0 for the child and then 2 is for grandparents
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    if(generation == 0)
    {
        printf("Child (Generation %d): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if(generation == 1)
    {
        printf("Parent (Generation %d): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        // can be ignored - this is only if there are about more than 3 generations
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparents (Generation %d): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    
    // recursively print - this modifies the p as we recurse through each generation
    printFamily(p->parents[0], generation+1);
    printFamily(p->parents[1], generation+1);
}

void freeFamily(person *p)
{
    // handling the base case of NULL as pointer i.e., hits the oldest generation, then exit
    if(p == NULL)
    {
        return;
    }

    // recursively handle the freeing by building out an execution stack
    freeFamily(p->parents[0]);
    freeFamily(p->parents[1]);

    // free the execution stack
    free(p);
}

char randomAllele()
{
    int r = random() % 3;

    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }

}

