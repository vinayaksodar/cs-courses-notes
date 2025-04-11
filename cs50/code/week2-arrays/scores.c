// create an array with 3 values a helper average funnction and output the values

#include <stdio.h>
#include <stdlib.h>
float average(int arr[], int length);

int main()
{
    int arr[3] = {1, 2, 3};
    float avg = average(arr, 3);
    printf("%f \n", avg);
}

float average(int arr[], int length)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    return (float)sum / length;
}

// No way to pass the actual array onnly the poinnter to first element can be passed like above
// Read pointer decay in c

// float average(int &arr)
// {
//     int s = sizeof(*arr);
//     int arrLength;
//     if (s > 0)
//     {
//         int a = sizeof(arr[0]);
//         arrLength = s / a;
//     }
//     else
//     {
//         return 1;
//     }
//     int sum = 0;
//     for (int i = 0; i < arrLength; i++)
//     {
//         sum += arr[i];
//     }
//     return (float)sum / arrLength;
// }