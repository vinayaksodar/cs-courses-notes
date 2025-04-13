#include <stdio.h>

// The parameter 'arr' here is NOT an array, it's a POINTER (char **)
void my_function(char *arr[])
{ // Equivalent to: void my_function(char **arr)

    printf("Inside function, address OF THE PARAMETER 'arr' (&arr): %p\n", (void *)&arr);

    // 'arr' itself holds the address of the first element of the original array
    printf("Inside function, value stored IN 'arr': %p\n", (void *)arr);

    // sizeof(arr) inside the function will give the size of a pointer, not the original array
    printf("Inside function, sizeof(arr) = %zu bytes (size of a pointer)\n", sizeof(arr));
}

int main(void)
{
    char *original_arr[] = {"hello", "world"};

    // +-------+-------+
    // arr:  | arr[0]| arr[1]|  (Array of 2 char* pointers)
    //       +-------+-------+
    //          |       |
    //          |       +-------------------> "world" (Stored elsewhere in memory)
    //          |
    //          +---------------------------> "hello" (Stored elsewhere in memory)

    // ALL IMPORTANT NOTE:  Here original arr is not a pointer it is an array of two pointers. There is no pointer to the array created, this is only created after pointer decay

    printf("In main, address OF THE ARRAY 'original_arr' (&original_arr): %p\n", (void *)&original_arr);
    printf("In main, value of 'original_arr' (decays to &original_arr[0]): %p\n", (void *)original_arr); // Here it decays to a ponter to the array when passed to printf
    printf("In main, sizeof(original_arr) = %zu bytes (size of the array)\n", sizeof(original_arr));

    printf("\nCalling function...\n");
    my_function(original_arr); // original_arr decays to char** when passed

    return 0;
}