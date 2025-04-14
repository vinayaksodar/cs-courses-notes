#include <stdio.h>

void selectionsort(int arr[], int length);
void swap(int arr[], int length, int maxindex);

int main(void)
{
    int arr[5] = {4, 7, 2, 5, 7};
    selectionsort(arr, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
}

void selectionsort(int arr[], int length)
{
    if (length == 0)
    {
        return;
    }
    int maxindex = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > arr[maxindex])
        {
            maxindex = i;
        }
    }
    swap(arr, length, maxindex);
    selectionsort(arr, length - 1);
}

void swap(int arr[], int length, int maxindex)
{
    int tmp = arr[length - 1];
    arr[length - 1] = arr[maxindex];
    arr[maxindex] = tmp;
}