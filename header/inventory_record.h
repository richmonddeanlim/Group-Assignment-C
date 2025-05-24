#ifndef INVENTORY_RECORD_H
#define INVENTORY_RECORD_H


struct inventory_record
{
    char product_id[100];
    int quantity;
    char status[50];
};

#endif