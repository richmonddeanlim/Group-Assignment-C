#include <stdio.h>
#define default_border 60

// decoration for display
// the default is 60, so if want to adjust can just add the number of '-' that want to be printed"
void border(int num)
{
    for(int i = 0; i < num; i++)
    {
        printf("-");
    }

    printf("\n");
}

// centering an text
void add_space(int num)
{
    int len_of_string;

    for(int i = 0; i < num; i++)
    {
        printf(" ");
    }
}