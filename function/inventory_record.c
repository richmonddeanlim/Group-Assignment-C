#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../header/decoration.h"
#include "decoration.c"

// data structure for the inventory_record
struct inventory_record
{
    char date[20];
    char product_id[100];
    int quantity;
    char status[50];
};

// option validation function
void option_validation(char *input_text,int *choice,int range)
{
    while(1)
    {
        printf("%s", input_text); 
        if(scanf("%d", choice))
        {
            for(int i = 0; i < range;i++)
            {
                if(*choice == i + 1)
                {
                    return;
                }
    
                else if(*choice != i && i == range - 1)
                {
                    printf("There is no such option\n");
                }
            } 
        }
    
        else
        {   char ch;
            printf("Pls input an integer\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

// int valdiation
void integer_valdiation(char *input_text,int *user_input )
{
    while(1)
    {
        printf("%s", input_text); 
        if(scanf("%d", user_input))
        {
            return;
        }
    
        else
        {   char ch;
            printf("Pls input an integer\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

// inventory record management menu
int menu()
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
    printf("5. Exit\n");
    border(default_border);
    
    // geting user choices
    int choice;
    option_validation("Enter your choice: ",&choice,5);
    printf("%d", choice);

    return choice; 
}

// function adding new record for inventory
void add_record()
{
    struct inventory_record record;
    while(1)
    {
        int arr_size = 0;

        // getting user input
        printf("Enter the date (dd-mm-yyyy): ");
        scanf("%s", &record.date);

        // date validation
        for(int i = 0; i < record.date[i] != '\0'; i++) // '\0' represent null value
        {
            arr_size += 1;
        }
        
        char ch;
        // further date validation
        if(arr_size == 10)
        {
            // ensure the date not above 31
            if( (int) (((record.date[0] - '0') * 10) + record.date[1] - '0') < 31) // subtract with '0' will return the int value (converting ascii to int)
            {
                // ensure the month not above 12
                if((int) (((record.date[3] - '0') * 10) + record.date[4] - '0') < 12)
                {
                    break;
                }

                else
                {
                    printf("The monnth is more than 31, pls stry again\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
                }
            }

            else
            {
                printf("The date is more than 31, pls stry again\n");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
            }

        }
        
        else if(arr_size < 10)
        {
            printf("Pls input the right format\n");
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
        }
        
        else
        {
            printf("Pls input the right format\n");
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
        }   
    }
}

int main()
{
    // menu();
    add_record();
    return 0;
}   