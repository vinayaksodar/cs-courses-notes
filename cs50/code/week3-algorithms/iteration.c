#include <stdio.h>

void draw(int n);
int main(void)
{
    int n = 12;

    draw(n);
}

void draw(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}