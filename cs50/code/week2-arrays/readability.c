#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

int get_index(string s);
int get_words(string s);
int get_letters(string s);
int get_sentences(string s);

int main(void)
{
    // get input form the user
    string s = get_string("Text: ");

    // compute the index
    int index = get_index(s);

    // print the result
    if (index >= 16)
    {
        printf("Grade16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

int get_index(string s)
{
    int words = get_words(s);
    int letters = get_letters(s);
    int sentences = get_sentences(s);

    int L = round((float)(letters * 100) / words);
    int S = round((float)(sentences * 100) / words);

    int index = (int)round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

int get_words(string s)
{
    int words = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            words += 1;
        }
    }
    return words;
}

int get_letters(string s)
{
    int letters = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int get_sentences(string s)
{
    int sentences = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentences += 1;
        }
    }
    return sentences;
}
