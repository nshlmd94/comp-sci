#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;
    for(int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));

        if(n == NULL)
        {
            return 1;
        }

        int temp;
        printf("%d : ", i+1);
        scanf("%d", &temp);
        n->number = temp;
        n->next = NULL;

        n->next = list;
        list = n;
    }

    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    return 0;
}