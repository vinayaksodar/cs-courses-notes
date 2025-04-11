#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("No command line arguments provided exiting... ");
        return 1; // failure
    }
    else
    {
        return 0; // success(representd by 0 as there is only one way of success but multiple ways of failure with multiple error codes)
    }
}

// see the status code by using echo $? after running the program