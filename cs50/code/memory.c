#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = malloc(sizeof(int) * 3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    int size = 3; // Calculate array size

    printf("Integer Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}