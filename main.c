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

int main()
{
    decoration();
    printf("Inventory Management System\n");
    decoration();

    return 0;
}