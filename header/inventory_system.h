#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
#define Max_users 100
#define default_border 60

#define MAX_PRODUCTS 100
#define MAX_NAME 50
#define PRODUCT_FILE "database/product.txt"
#define max_categories 100
#define max_suppliers 100


// Staff and Product
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} Staff;

typedef struct {
    char id[10];                // e.g., A001
    char name[MAX_NAME];       // Product name
    int category_id;           // Integer ID linked to categories
    int supplier_id;           // Integer ID linked to suppliers
    float price;               // Product price
} Product;

// Linked list node structure for shared responsibility
typedef struct ProductNode {
    Product data;
    struct ProductNode* next;
} ProductNode;

// Inventory
struct inventory_record {
    char date[20];
    char product_id[50];
    char action[50];
    int quantity;
    char status[50];
    char userID[10];
};

struct inventory_item {
    char product_id[50];
    char product_name[50];
    int quantity;
    char stock_status[50];
    char product_status[50];
};

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
void role4_Menu(int isAdmin);
void main_menu(); 
void adminMenu();
void clearScreen();
void clearInputBuffer();

// --- Product Management ---
void addProduct();
void viewProducts();
void updateProduct();
void deleteProduct();
void searchProductByName();
int loadProducts(Product products[]);
void saveProducts(Product products[], int count);
int findProductIndex(Product products[], int count, const char* id);
void viewProductsWithLinkedList();

// --- Inventory Management ---
void add_record();
void update_stock();
void remove_discontinued();
void view_record();

// --- User and Transaction Management ---
void user();
void transactions();
void viewTransactions();
bool continueOrNo();
void viewArchive();

// --- Category and Supplier Management ---

// Category structure
struct category {
    int id;
    char name[100];
    char description[200];
};

// Supplier structure
struct supplier {
    int id;
    char name[100];
    char contact[50];
    char email[100];
};

extern struct category categories[max_categories];
extern int category_count;

extern struct supplier suppliers[max_suppliers];
extern int supplier_count;

// --- Category Functions ---
void load_category();
void save_category();
int next_categoryID();
void add_category();
void view_category();
void update_category();
void delete_category();
void category_menu();

// --- Supplier Functions ---
void load_supplier();
void save_supplier();
int next_supplierID();
void add_supplier();
void view_supplier();
void update_supplier();
void delete_supplier();
void supplier_menu();


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