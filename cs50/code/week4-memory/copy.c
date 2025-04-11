#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char *s = "hi";

    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return 1;
    }
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    t[0] = toupper(t[0]);

    printf("%s\n", s);
    printf("%s\n", t);
    free(t);
}