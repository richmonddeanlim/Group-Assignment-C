#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../header/decoration.h"
#include "decoration.c"

char product_location[] = "../database/product.txt";
char record_lcoation[] = "../database/inventory_record.txt";

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

// array length
void arr_len(char array[], int *array_len)
{
    // date validation
    for(int i = 0; array[i] != '\0'; i++) // '\0' represent null value
    {
        *array_len += 1;
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
int add_record()
{
    FILE *file_product;
    FILE *file_record;

    // File location
    struct inventory_record record;
    char ch;

    // getting date input
    while(1)
    {
        int array_len = 0;
        
        // getting user input
        printf("Enter the date (dd-mm-yyyy): ");
        scanf("%s", &record.date);
        
        // getting arr len
        arr_len(record.date, &array_len);
        
        // further date validation
        if(array_len == 10)
        {
            if(record.date[2] == '-' && record.date[5] == '-')
            {
                // ensure the date not above 31
                if( (int) (((record.date[0] - '0') * 10) + record.date[1] - '0') < 31) // subtract with '0' will return the int value (converting ascii to int)
                {
                    // ensure the month not above 12
                    if((int) (((record.date[3] - '0') * 10) + record.date[4] - '0') < 12)
                    {
                        while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
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

            else
            {
                printf("pls follow the data format put the '-' between the date\n");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            }
            
        }

        else if(array_len < 10)
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
    
    // getting product id input
    while(1)
    {
        int array_len = 0;
        
        //getting user input
        printf("Enter the product id (Axxx): ");
        scanf("%s", &record.product_id);
        
        // getting arr len for valdiation
        arr_len(record.product_id, &array_len);

        // open the product.txt
        file_product = fopen(product_location,"r");

        if( file_product == NULL)
        {
            printf("Error opening file.\n");
            return 1;
        }

        int line = 0;
        char raw_product [100] [100];

        // take all line to the array until not end of file and not error
        while(!feof(file_product) && !ferror(file_product))
        {
            // looping until the value null
            if(fgets(raw_product[line],100, file_product) != NULL)
            {
                // get the length of the line
                line += 1;
            }
        }

        // closing file
        fclose(file_product);

        char data[100][100][100];
        int len_data;

        // splitting , 
        for(int i = 0; i <2;i++)
        {
            // Returns first token 
            char *token = strtok(raw_product[i], ",");

            // Keep printing tokens while one of the
            // delimiters present in str[].
            while (token != NULL)
            {
                for(int j = 0; j < 5; j++)
                {
                    // copy the splitted string adn insert i into data
                    strncpy(data[i][j], token, 99);
                    data[i][j][99] = '\0'; 
                    token = strtok(NULL, ",");
                }
            }
    
        }

        char product_id[100][100];

        // insert the data into product id
        for(int i=0; i < line ;i++)
        {
            strncpy(product_id[i],data[i][0],99); 
        }

        for(int i = 0; i < line; i++)
        {
            printf("%s", product_id[i]);
        }


        if(array_len == 5)
        {
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            break;
        }

        {
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            printf("Pls enter the right format");
        }
    }

    // // getting the quantity
    // integer_valdiation("Enter the quantity: ", &record.quantity);

    // getting status
}

int main()
{
    // menu();
    add_record();
    return 0;
}   