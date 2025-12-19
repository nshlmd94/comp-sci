// Capitalizes a string
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = "Hello";

    // Copy string's address
    char *t = s;

    // Print string address
    printf("s: %p\n", s);
    printf("t: %p\n", t);

    // Print the address of the pointer (variable) itself
    printf("s: %p\n", &s);
    printf("t: %p\n", &t);

}