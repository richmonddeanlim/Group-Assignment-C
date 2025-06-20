#include <stdio.h>
#include "product.h"

//gcc main.c product.c -o inventory
//./inventory
// Main menu for product management
void showMenu() {
    int choice;
    do {
        printf("\n=== Product Management Menu ===\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product by Name\n");
        printf("6. Exit\n");
        printf("Choose: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: searchProductByName(); break;
            case 6: printf("Exiting system.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

// Entry point
int main() {
    showMenu();
    return 0;
}
