#include <stdio.h>

int main()
{
    char *argv[] = {"./program", "hello", "world"};

    printf("Address of argv itself      : %p\n", (void *)argv);
    printf("Address of &argv[0]         : %p\n", (void *)&argv[0]);
    printf("Address of &argv[1]         : %p\n", (void *)&argv[1]);
    printf("Address of &argv[2]         : %p\n", (void *)&argv[2]);
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        printf("argv[%d] (string ptr)        : %p\n", i, (void *)argv[i]);
        printf("   &argv[%d] (ptr address)   : %p\n", i, (void *)&argv[i]);
        printf("   argv[%d] points to string : %s\n", i, argv[i]);
        printf("   First char of argv[%d]    : %c\n", i, *argv[i]);
        printf("\n");
    }

    printf("Address of argv : %p\n" * argv);

    return 0;
}
