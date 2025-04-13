#include <stdio.h>

int main(void)
{
    int a = 5;

    int *b = &a;

    printf("%p\n", &b);    // This will print out the address at which the pointer itself resides.
    printf("%p\n", b);     // This will print out the pointer value i.e the address it points to.
    printf("%p\n", *(&b)); // This will print out the value at the address of the pointer which will be the address it points to.(Same address as above)
    printf("%p\n", &(*b)); // This will print out the address of the value the pointer points at.(Same address as above)
}