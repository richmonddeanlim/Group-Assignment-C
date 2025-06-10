#ifndef INVENTORY_RECORD_H
#define INVENTORY_RECORD_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global Variables
extern FILE *file_product;
extern FILE *file_record;
extern char product_location[];
extern char record_location[];

// Data Structures
struct inventory_record
{
    char date[20];
    char product_id[50];
    char action[50];
    int quantity;
    char status[50];
};

struct inventory_item
{
    char product_id[50];
    char product_name[50];
    int quantity;
    char stock_status[50];
};

// Function Declarations

// Menu and Main Functions
int menu();
void add_record();
void update_stock();
void view_record();
void remove_discontinued();

// Validation Functions
void option_validation(char *input_text, int *choice, int range);
void integer_valdiation(char *input_text, int *user_input);
void arr_len(char array[], int *array_len);
void str_lower(char *str);
void clean_string(char *str);

// Data Management Functions
void data_product(char data[100][100][100], int *line_array);
void data_record(char data[100][100][100], int *line_array);

#endif