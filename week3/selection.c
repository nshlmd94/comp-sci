// program to run selection sort on an array of numbers

#include <stdio.h>

int main(void)
{
    int array[] = {20, 63, 42, 100, 34, 64, 36, 2, 3, 9};

    for(int index = 0; index < (sizeof(array)/sizeof(array[0]))-1; index++)
    {
        int min_index = index;
        for(int loop = index + 1; loop < (sizeof(array)/sizeof(array[0])); loop++)
        if(array[loop] < array[min_index])
        {
            min_index = loop;
        }
    }

   
}