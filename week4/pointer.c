#include <stdio.h>

int main(void)
{
    // POINTER
    char* name1 = "Turing"; // stores the string literal
    printf("%s\n", name1); // prints the entire string

    printf("%c\n", *name1);  // prints the character at this pointer address
    printf("%c\n\n", *(name1+1));  // prints the character at this pointer address

    printf("%s\n", name1+0); // prints the string stored starting at this address (e.g., Turing)
    printf("%s\n", name1+1);  // prints the string stored starting at this address (e.g., uring)
    printf("%s\n\n", name1+2);

    // ARRAY
    char name[] = "Turing"; // stores the address and is therefore a pointer
    printf("%s\n", name);   // prints the entire string
    printf("%c\n", name[0]);
    printf("%c\n", name[1]);
    printf("%c\n", name[2]);
    printf("%c\n", name[3]);
    printf("%c\n", name[4]);
    printf("%c\n", name[5]);
    printf("%c\n", name[6]);
    printf("%p\n", &name);
    printf("%p\n", &name[0]);
    printf("%p\n", &name[1]);
    printf("%p\n", &name[2]);
    printf("%p\n", &name[3]);
    printf("%p\n", &name[4]);
    printf("%p\n", &name[5]);
    printf("%p\n", &name[6]);
    printf("%p\n", &name[7]); // &name[7] works because computing an address is allowed even one past the array, but accessing data there (name[7]) is undefined behavior.
}