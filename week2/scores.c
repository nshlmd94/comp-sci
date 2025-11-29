// Averages three (hardcoded) numbers using an array and a loop

#include <stdio.h>

int main(void)
{
    // Get scores
    int scores[3];
    for (int i = 0; i < 3; i++)
    {
        printf("Enter.\n");
        scanf("%d", &scores[i]);
    }

    // Print average
    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
}