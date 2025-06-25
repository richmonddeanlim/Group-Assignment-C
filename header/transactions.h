const char *menutext = "\n--- User and Transaction Management System ---\n\n";

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void user();
void transactions();
void getValidInput();
void viewTransactions();
bool continueOrNo();
void viewArchive();


// Inventory
struct inventory_record {
    char date[20];
    char product_id[50];
    char action[50];
    int quantity;
    char status[50];
    char userID[10];
};