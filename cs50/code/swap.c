#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int a = 1;
    int b = 2;
    swap(&a, &b);

    printf("a:%i, b%i", a, b);
}