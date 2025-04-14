#include <stdio.h>
#include <stdlib.h>

int *mergesort1(int arr[], int length);
void print_arr(int arr[], int length);

int main(void)
{
    int arr[5] = {4, 6, 2, 4, 8};
    int *mergedarr;
    mergedarr = mergesort1(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", mergedarr[i]);
    }
}

int *mergesort1(int arr[], int length)
{
    if (length == 1)
    {
        int *mergedarr = malloc(sizeof(int));
        mergedarr[0] = arr[0];

        return mergedarr;
    }
    int arr1len = length / 2;
    int arr2len = length - arr1len;
    int *arr1 = malloc(sizeof(int) * arr1len);
    int *arr2 = malloc(sizeof(int) * arr2len);
    for (int i = 0; i < arr1len; i++)
    {
        arr1[i] = arr[i];
    }
    for (int i = 0; i < arr2len; i++)
    {
        arr2[i] = arr[i + arr1len];
    }
    int *sorted1 = mergesort1(arr1, arr1len);
    int *sorted2 = mergesort1(arr2, arr2len);

    free(arr1);
    free(arr2);

    arr1 = sorted1;
    arr2 = sorted2;

    int *mergedarr = malloc(sizeof(int) * length);
    int p1 = 0;
    int p2 = 0;

    while (p1 < arr1len && p2 < arr2len)
    {
        if (arr1[p1] < arr2[p2])
        {
            mergedarr[p1 + p2] = arr1[p1];
            p1++;
        }
        else
        {
            mergedarr[p1 + p2] = arr2[p2];
            p2++;
        }
    }
    if (p1 == arr1len)
    {
        while (p2 < arr2len)
        {
            mergedarr[p1 + p2] = arr2[p2];
            p2++;
        }
    }
    else
    {
        while (p1 < arr1len)
        {
            mergedarr[p1 + p2] = arr1[p1];
            p1++;
        }
    }
    print_arr(mergedarr, length);

    free(arr1);
    free(arr2);

    return mergedarr;
}

void print_arr(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%i", arr[i]);
        if (i < length - 1)
        {
            printf(",");
        }
    }
    printf("\n");
}