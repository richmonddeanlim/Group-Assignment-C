//Run With gcc main.c function/user_credentials.c -o program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "header/inventory_system.h"
#include "function/decoration.c"

extern User users[MAX_USERS];
extern int userCount;
extern User currentUser;

int login() {
    char username[50];
    char password[50];
    int attempts = 3;

    while (attempts > 0) {
        printf("\n=== Login System ===\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, username) == 0 && 
                strcmp(users[i].password, password) == 0) {
                strcpy(currentUser.username, users[i].username);
                strcpy(currentUser.password, users[i].password);
                strcpy(currentUser.role, users[i].role);
                return 1;
            }
        }

        attempts--;
        printf("\nInvalid credentials! %d attempts remaining.\n", attempts);
    }

    return 0;
}



// Role 1 Menu - Core System and Product Management (This is just a placeholder)
void role1Menu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== Core System and Product Management ===\n");
        printf("1. Add New Product\n");
        printf("2. Update Product Information\n");
        printf("3. Delete Product\n");
        printf("4. View Product Details\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdd New Product functionality will be implemented here\n");
                system("pause");
                break;
            case 2:
                printf("\nUpdate Product Information functionality will be implemented here\n");
                system("pause");
                break;
            case 3:
                printf("\nDelete Product functionality will be implemented here\n");
                system("pause");
                break;
            case 4:
                printf("\nView Product Details functionality will be implemented here\n");
                system("pause");
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 2 Menu - Inventory and Stock Management (This is just a placeholder)
void role2Menu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== Inventory and Stock Management ===\n");
        printf("1. Add Stock Inventory\n");
        printf("2. Update Stock Levels\n");
        printf("3. Remove Stock Items\n");
        printf("4. View Inventory Levels\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdd Stock Inventory functionality will be implemented here\n");
                system("pause");
                break;
            case 2:
                printf("\nUpdate Stock Levels functionality will be implemented here\n");
                system("pause");
                break;
            case 3:
                printf("\nRemove Stock Items functionality will be implemented here\n");
                system("pause");
                break;
            case 4:
                printf("\nView Inventory Levels functionality will be implemented here\n");
                system("pause");
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 3 Menu - Category and Supplier Management (This is just a placeholder)
void role3Menu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== Category and Supplier Management ===\n");
        printf("1. Add Category/Supplier\n");
        printf("2. Update Category/Supplier\n");
        printf("3. Delete Category/Supplier\n");
        printf("4. View Categories/Suppliers\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdd Category/Supplier functionality will be implemented here\n");
                system("pause");
                break;
            case 2:
                printf("\nUpdate Category/Supplier functionality will be implemented here\n");
                system("pause");
                break;
            case 3:
                printf("\nDelete Category/Supplier functionality will be implemented here\n");
                system("pause");
                break;
            case 4:
                printf("\nView Categories/Suppliers functionality will be implemented here\n");
                system("pause");
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 4 Menu - User and Transaction Management (This is just a placeholder)
void role4Menu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== User and Transaction Management ===\n");
        printf("1. Add User/Transaction\n");
        printf("2. Update User/Transaction\n");
        printf("3. Delete User/Transaction\n");
        printf("4. View Users/Transactions\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdd User/Transaction functionality will be implemented here\n");
                system("pause");
                break;
            case 2:
                printf("\nUpdate User/Transaction functionality will be implemented here\n");
                system("pause");
                break;
            case 3:
                printf("\nDelete User/Transaction functionality will be implemented here\n");
                system("pause");
                break;
            case 4:
                printf("\nView Users/Transactions functionality will be implemented here\n");
                system("pause");
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}


// Main Menu
void displayMainMenu() {
    int choice;
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        printf("1. Core System and Product Management\n");
        printf("2. Inventory and Stock Management\n");
        printf("3. Category and Supplier Management\n");
        printf("4. User and Transaction Management\n");
        printf("5. Administrator Menu\n");
        printf("6. Logout\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (strcmp(currentUser.role, "role1") == 0 || strcmp(currentUser.role, "administrator") == 0)
                    role1Menu();
                else
                    printf("\nAccess denied! You don't have permission for this role.\n");
                break;
            case 2:
                if (strcmp(currentUser.role, "role2") == 0 || strcmp(currentUser.role, "administrator") == 0)
                    role2Menu();
                else
                    printf("\nAccess denied! You don't have permission for this role.\n");
                break;
            case 3:
                if (strcmp(currentUser.role, "role3") == 0 || strcmp(currentUser.role, "administrator") == 0)
                    role3Menu();
                else
                    printf("\nAccess denied! You don't have permission for this role.\n");
                break;
            case 4:
                if (strcmp(currentUser.role, "role4") == 0 || strcmp(currentUser.role, "administrator") == 0)
                    role4Menu();
                else
                    printf("\nAccess denied! You don't have permission for this role.\n");
                break;
            case 5:
                if (strcmp(currentUser.role, "administrator") == 0)
                    adminMenu();
                else
                    printf("\nAccess denied! Administrator privileges required.\n");
                break;
            case 6:
                return;
            case 7:
                printf("\nThank you for using the system. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
        system("pause");
    } while (1);
}

int main() {
    loadUsers();
    
    while (1) {
        if (login()) {
            displayMainMenu();
        } else {
            printf("\nToo many failed attempts. Program will exit.\n");
            break;
        }
    }

    return 0;
}