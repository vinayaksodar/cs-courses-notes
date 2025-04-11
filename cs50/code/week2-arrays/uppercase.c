#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(void)
{
    char name[3] = {'s', 'a', 'm'};
    printf("%c \n", name[3]);

    for (int i = 0; i < 3; i++)
    {
        // printf("%c", name[i] - ('a' - 'A'));
        printf("%c", toupper(name[i]));
    }
}