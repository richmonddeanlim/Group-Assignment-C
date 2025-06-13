#include <stdio.h>
#include "../header/inventory_system.h"

// adding border
// tyhe default is 60, can be chnage based on usage
void border(int num) 
{
    for (int i = 0; i < num; i++) {
        printf("-");
    }
    printf("\n");
}

// adding white space
// c doens't have stringb formating like c++
void add_space(int num) {
    for (int i = 0; i < num; i++) {
        printf(" ");
    }
}
