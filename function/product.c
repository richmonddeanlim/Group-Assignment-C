#include <stdio.h>      // Standard I/O library
#include <stdlib.h>     // For malloc, free, etc.
#include <string.h>     // String manipulation functions
#include <ctype.h>      // Character handling functions
#include "../header/inventory_system.h"    // Header file with struct definitions and constants

// Get category name from ID by reading category.txt
const char* getCategoryName(int id) {
    static char line[150];
    static char name[50];
    FILE* fp = fopen("database/category.txt", "r");
    if (!fp) {
        return "Unknown Category";
    }

    while (fgets(line, sizeof(line), fp)) {
        int fileId;
        char nameBuffer[50];
        char descBuffer[100];

        // Parse line format: ID,Name,Description
        if (sscanf(line, "%d,%49[^,],%99[^\n]", &fileId, nameBuffer, descBuffer) == 3) {
            if (fileId == id) {
                strncpy(name, nameBuffer, sizeof(name));
                name[sizeof(name) - 1] = '\0';
                fclose(fp);
                return name;
            }
        }
    }

    fclose(fp);
    return "Unknown Category";
}

// Get supplier name from ID by reading supplier.txt
const char* getSupplierName(int id) {
    static char line[200];
    static char name[50];
    FILE* fp = fopen("database/supplier.txt", "r");
    if (!fp) {
        return "Unknown Supplier";
    }

    while (fgets(line, sizeof(line), fp)) {
        int fileId;
        char nameBuffer[50];
        char contact[30];
        char email[50];

        // Parse line format: ID,Name,Contact,Email
        if (sscanf(line, "%d,%49[^,],%29[^,],%49[^\n]", &fileId, nameBuffer, contact, email) == 4) {
            if (fileId == id) {
                strncpy(name, nameBuffer, sizeof(name));
                name[sizeof(name) - 1] = '\0';
                fclose(fp);
                return name;
            }
        }
    }

    fclose(fp);
    return "Unknown Supplier";
}

// Load products from file into array, return number loaded
int loadProducts(Product products[]) {
    FILE* fp = fopen(PRODUCT_FILE, "r");
    if (!fp) {
        perror("Failed to open file");
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%9[^,],%49[^,],%d,%d,%f\n",
        products[count].id,
        products[count].name,
        &products[count].category_id,
        &products[count].supplier_id,
        &products[count].price) == 5) {
        count++;
    }
    fclose(fp);
    return count;
}

// Save all products to file (overwrite)
void saveProducts(Product products[], int count) {
    FILE* fp = fopen(PRODUCT_FILE, "w");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%d,%d,%.2f\n",
            products[i].id,
            products[i].name,
            products[i].category_id,
            products[i].supplier_id,
            products[i].price);
    }
    fclose(fp);
}

// Search product array by ID, return index or -1 if not found
int findProductIndex(Product products[], int count, const char* id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(products[i].id, id) == 0)
            return i;
    }
    return -1;
}

// Check if category ID exists in category.txt
int isValidCategoryID(int id) {
    FILE* fp = fopen("database/category.txt", "r");
    if (!fp) return 0;
    int fileId;
    char name[50], desc[100];
    while (fscanf(fp, "%d,%49[^,],%99[^\n]", &fileId, name, desc) == 3) {
        if (fileId == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Check if supplier ID exists in supplier.txt
int isValidSupplierID(int id) {
    FILE* fp = fopen("database/supplier.txt", "r");
    if (!fp) return 0;
    int fileId;
    char name[50], contact[30], email[50];
    while (fscanf(fp, "%d,%49[^,],%29[^,],%49[^\n]", &fileId, name, contact, email) == 4) {
        if (fileId == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addProduct() {
    Product products[MAX_PRODUCTS];
    int count = loadProducts(products);

    if (count >= MAX_PRODUCTS) {
        printf("Inventory full.\n");
        return;
    }

    Product p;

    printf("Enter Product ID (e.g., A001): ");
    fgets(p.id, sizeof(p.id), stdin);
    p.id[strcspn(p.id, "\n")] = '\0';

    // Validate ID format
    if (!isalpha(p.id[0]) || strlen(p.id) < 2) {
        printf("Invalid Product ID. Must start with a letter (e.g., A001).\n");
        return;
    }

    // Check for duplicate
    if (findProductIndex(products, count, p.id) != -1) {
        printf("Product ID already exists.\n");
        return;
    }

    printf("Enter Product Name: ");
    fgets(p.name, MAX_NAME, stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    // Validate name
    if (strlen(p.name) == 0 || isdigit(p.name[0])) {
        printf("Invalid Product Name. Please enter a valid name.\n");
        return;
    }

    
    printf("Enter Category ID (e.g.1-Mobile, 2-Computer, 3-Accessory): ");
    scanf("%d", &p.category_id);
    while (getchar() != '\n'); // clear buffer
    
    if (!isValidCategoryID(p.category_id)) {
        printf("Invalid Category ID. Please enter a valid ID listed in category.txt.\n");
        return;
    }
    
    printf("Enter Supplier ID (e.g. 1-TechSource, 2-GadgetMall, 3-PowerHouse): ");
    scanf("%d", &p.supplier_id);
    while (getchar() != '\n'); // clear buffer

    if (!isValidSupplierID(p.supplier_id)) {
        printf("Invalid Supplier ID. Please enter a valid ID listed in supplier.txt.\n");
        return;
    }

    printf("Enter Price: ");
    scanf("%f", &p.price);
    while (getchar() != '\n'); // Clear buffer

    if (p.price <= 0) {
        printf("Price must be greater than 0.\n");
        return;
    }

    products[count++] = p;
    saveProducts(products, count);
    printf(" Product added successfully.\n");
}


// View all products with readable category and supplier names
void viewProducts() {
    Product products[MAX_PRODUCTS];
    int count = loadProducts(products);

    if (count == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\n--------------------------------- Product List --------------------------------------------\n");
    printf("ID\tName\t\tCategory\t\tSupplier\t\tPrice\n");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-8s %-25s %-18s %-18s RM%8.2f\n",
            products[i].id,
            products[i].name,
            getCategoryName(products[i].category_id),
            getSupplierName(products[i].supplier_id),
            products[i].price);
        

    }

    viewProductsWithLinkedList();
}

void updateProduct() {
    Product products[MAX_PRODUCTS];
    int count = loadProducts(products);

    char id[10];
    printf("Enter Product ID to update: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findProductIndex(products, count, id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    printf("Enter new Product Name: ");
    fgets(products[index].name, MAX_NAME, stdin);
    products[index].name[strcspn(products[index].name, "\n")] = '\0';

    printf("Enter new Category ID: ");
    scanf("%d", &products[index].category_id);
    while (getchar() != '\n'); // Clear buffer

    printf("Enter new Supplier ID: ");
    scanf("%d", &products[index].supplier_id);
    while (getchar() != '\n'); // Clear buffer

    printf("Enter new Price: ");
    scanf("%f", &products[index].price);
    while (getchar() != '\n'); // Clear buffer

    // Basic input validation
    if (strlen(products[index].name) == 0 ||
        products[index].category_id <= 0 ||
        products[index].supplier_id <= 0 ||
        products[index].price <= 0) {
        printf("Invalid input. Update aborted.\n");
        return;
    }

    saveProducts(products, count);
    printf("Product updated.\n");
}


// Delete product by ID
void deleteProduct() {
    Product products[MAX_PRODUCTS];
    int count = loadProducts(products);

    char id[10];
    printf("Enter Product ID to delete: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findProductIndex(products, count, id);
    if (index == -1) {
        printf("Product not found.\n");
        return;
    }

    // Shift elements to remove product
    for (int i = index; i < count - 1; i++) {
        products[i] = products[i + 1];
    }
    count--;

    saveProducts(products, count);
    printf("Product deleted.\n");
}

// Use linked list to count total products (shared responsibility)
void viewProductsWithLinkedList() {
    FILE* fp = fopen(PRODUCT_FILE, "r");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    ProductNode* head = NULL;
    Product temp;

    // Read file and create linked list
    while (fscanf(fp, "%9[^,],%49[^,],%d,%d,%f\n",
        temp.id, temp.name, &temp.category_id,
        &temp.supplier_id, &temp.price) == 5) {
        ProductNode* newNode = (ProductNode*)malloc(sizeof(ProductNode));
        newNode->data = temp;
        newNode->next = head;
        head = newNode;
    }
    fclose(fp);

    // Count nodes
    int count = 0;
    ProductNode* current = head;
    while (current) {
        count++;
        current = current->next;
    }

    printf("Total products: %d\n", count);

    // Free memory
    while (head) {
        ProductNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// Search product by keyword in name
void searchProductByName() {
    char search[MAX_NAME];
    printf("Enter keyword to search: ");
    fgets(search, MAX_NAME, stdin);
    search[strcspn(search, "\n")] = '\0';

    // Convert search keyword to lowercase
    for (int i = 0; search[i]; i++) {
        search[i] = tolower(search[i]);
    }

    Product products[MAX_PRODUCTS];
    int count = loadProducts(products);
    int found = 0;

    printf("\n--------------------------------- Search Results ---------------------------------\n");
    printf("ID\tName\t\tCategory\t\tSupplier\t\tPrice\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        char lowerName[MAX_NAME];
        strcpy(lowerName, products[i].name);

        // Convert product name to lowercase
        for (int j = 0; lowerName[j]; j++) {
            lowerName[j] = tolower(lowerName[j]);
        }

        // Check for match
        if (strstr(lowerName, search)) {
            printf("%s\t%s\t\t%s\t\t%s\t\tRM%.2f\n",
                   products[i].id,
                   products[i].name,
                   getCategoryName(products[i].category_id),
                   getSupplierName(products[i].supplier_id),
                   products[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching products found for \"%s\".\n", search);
    }
}
