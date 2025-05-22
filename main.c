#include <stdio.h>

// decoration for display
void decoration()
{
    for(int i = 0; i < 60; i++)
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
// branch testing
int main()
{
    decoration();
    center(10);
    printf("Inventory Management System\n");
    decoration();

    return 0;
}