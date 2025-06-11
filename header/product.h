#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100
#define MAX_NAME 50
#define PRODUCT_FILE "product.txt"

// Product structure definition using string ID
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

// Main menu
void showMenu();

// CRUD operations
void addProduct();
void viewProducts();
void updateProduct();
void deleteProduct();
void searchProductByName(); // Additional feature

// Helpers
int loadProducts(Product products[]);
void saveProducts(Product products[], int count);
int findProductIndex(Product products[], int count, const char* id);
void viewProductsWithLinkedList();

#endif
