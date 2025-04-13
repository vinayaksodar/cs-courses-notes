// Implements linear search for strings

#include <stdio.h>
#include <string.h>

int main(void)
{
    // An array of strings
    char **strings = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    // Search for string
    char *s = "boot";
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}