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
        int temp;
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return 1;
        }
        printf("Enter number: ");
        scanf("%d", &temp);
        n -> number = temp;
        n -> next = NULL;

        if(list == NULL)
        {
            list = n;
        }
        else
        {
            for(node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }

    }

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    node *ptr = list;

    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return 0;
    
}