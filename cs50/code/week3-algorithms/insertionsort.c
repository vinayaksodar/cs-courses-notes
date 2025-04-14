#include <stdio.h>

void insertionsort(int arr[], int subarrlen, int length);
void swap(int arr[], int arr2[]);

int main(void)
{
    int arr[5] = {4, 7, 2, 5, 1};
    insertionsort(arr, 2, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
}

void insertionsort(int arr[], int subarrlen, int length)
{
    if (length < subarrlen)
    {
        return;
    }
    for (int i = subarrlen - 1; i > 0; i--)
    {
        if (arr[i - 1] > arr[i])
        {
            swap(&arr[i - 1], &arr[i]);
        }
        else
        {
            break;
        }
    }
    insertionsort(arr, subarrlen + 1, length);
}

void swap(int arr[], int arr2[])
{
    int tmp = *arr;
    *arr = *arr2;
    *arr2 = tmp;
}