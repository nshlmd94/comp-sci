#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

int main(void)
{
    // Create one person
    person *child = malloc(sizeof(person));
    child->alleles[0] = 'A';
    child->alleles[1] = 'B';
    
    printf("Child's alleles: %c %c\n", child->alleles[0], child->alleles[1]);
    
    // Create a parent
    person *mom = malloc(sizeof(person));
    mom->alleles[0] = 'O';
    mom->alleles[1] = 'A';

    // Create a parent
    person *dad = malloc(sizeof(person));
    dad->alleles[0] = 'B';
    dad->alleles[1] = 'A';

    // Create grandparents
    person *grandmother = malloc(sizeof(person));
    grandmother->alleles[0] = 'O';
    grandmother->alleles[1] = 'O';
    
    // Connect them
    child->parents[0] = mom;
    child->parents[1] = dad;
    child->parents[0]->parents[0] = grandmother;
    
    // Access mom's alleles through child
    printf("Mom's alleles (via child): %c %c\n Dad's alleles (via child): %c %c\n", 
           child->parents[0]->alleles[0],
           child->parents[0]->alleles[1],
           child->parents[1]->alleles[0],
           child->parents[1]->alleles[1]);
    
    free(child);
    free(mom);
    free(dad);
    return 0;
}