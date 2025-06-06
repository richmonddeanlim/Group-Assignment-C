#ifndef INVENTORY_RECORD_H
#define INVENTORY_RECORD_H

// Function declarations
int menu();
void add_record();
void update_stock();
void view_record();

// Data structures
struct inventory_record
{
    char date[20];
    char product_id[50];
    char action[50];
    int quantity;
};

struct inventory_item
{
    char product_id[50];
    char product_name[50];
    int quantity;
    char stock_status[50];
};

#endif