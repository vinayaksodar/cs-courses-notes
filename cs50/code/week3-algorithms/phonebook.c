#include <stdio.h>
#include <string.h>

typedef struct
{
    char *name;
    char *number;
} person;

int main(void)
{
    person people[2];

    people[0].name = "vms";
    people[0].number = "1";

    people[1].name = "gms";
    people[1].number = "2";

    char inputName[40];
    printf("Enter name to search: ");
    fgets(inputName, sizeof(inputName), stdin);
    inputName[strcspn(inputName, "\n")] = 0; // Remove newline

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, inputName) == 0)
        {
            printf("Match found");
            return 0;
        }
    }
    printf("Match not found");
}