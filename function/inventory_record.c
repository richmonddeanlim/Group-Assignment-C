#include <stdio.h>
#include "../header/decoration.h"
#include "decoration.c"

int main()
{
    // giving menu interface for user
    border(default_border);
    add_space(15);
    printf("Iventory and Stock management\n");
    border(default_border);
    printf("1. Add stock inventory record\n");
    printf("2. Update stock level\n");
    printf("3. Delete Discontinued Stock\n");
    printf("4. View Current Invetory\n");
    border(default_border);
    
    return 0;
}   