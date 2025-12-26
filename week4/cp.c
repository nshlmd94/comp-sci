#include <stdio.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        printf("src: %s\n", &b);
        fwrite(&b, sizeof(b), 1, dst);
        printf("dst: %s\n", &b);
    }

    fclose(dst);
    fclose(src);
}