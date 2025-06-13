#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 256
#define Max_users 100
#define default_border 60

// Staff and Product
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} Staff;

// Inventory
struct inventory_record {
    char date[20];
    char product_id[50];
    char action[50];
    int quantity;
    char status[50];
};

struct inventory_item {
    char product_id[50];
    char product_name[50];
    int quantity;
    char stock_status[50];
    char product_status[50];
};

// Global Variables

// Staff
extern Staff users[Max_users];
extern int userCount;
extern Staff currentUser;

// Inventory file paths
extern FILE *file_product;
extern FILE *file_record;
extern char product_location[];
extern char record_location[];


// --- Staff/User Functions ---
void loadUsers();
int login();
void changePassword();
void addUser();
void deleteUser();
void getValidInput(char* prompt, char* buffer, int maxLength);
void displayMainMenu();
void role1Menu(int isAdmin);
void role2Menu(int isAdmin);
void role3Menu(int isAdmin);
void role4Menu(int isAdmin);
void adminMenu();
void clearScreen();
void clearInputBuffer();

// --- Inventory Management ---
void add_record();
void update_stock();
void remove_discontinued();
void view_record();

// --- Validation Utilities ---
void option_validation(char *input_text, int *choice, int range);
void integer_valdiation(char *input_text, int *user_input);
void arr_len(char array[], int *array_len);
void str_lower(char *str);
void clean_string(char *str);

// --- Data Loaders ---
void data_product(char data[100][100][100], int *line_array);
void data_record(char data[100][100][100], int *line_array);

// --- Decoration Functions ---
void border(int num);
void add_space(int num);


#endif