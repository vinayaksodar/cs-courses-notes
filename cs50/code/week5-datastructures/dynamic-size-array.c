// Implement a dynamic array

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = malloc(sizeof(int) * 3);
    if (arr == NULL)
    {
        return 1;
    }
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    // Resize list to be of size4

    int *tmp = realloc(arr, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(arr); // IMPORTANT: Don't forget to free arr here if realloc fails
        return 1;
    }
    // Don't free arr here before reassigning the arr pointer realloc does that for you also it may have allocated more memory in the same location so freeing will lead to errors.
    arr = tmp;

    // Add number to list

    arr[3] = 4;

    // Print list
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", arr[i]);
    }
    free(arr); // Don't forget to free arr here
}