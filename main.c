// First do cd Group-Assignment-C-main in the terminal
// Run With gcc main.c function/*.c -o program
// Run With ./program

#include "header/inventory_system.h"

int login() {
    char username[50];
    char password[50];
    int attempts = 3;

    while (attempts > 0) {
        clearScreen();
        printf("\n=== Login System ===\n");
        
        // Get username and password using getValidInput
        getValidInput("Username: ", username, sizeof(username));
        getValidInput("Password: ", password, sizeof(password));

        // Check credentials
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
        system("pause");
    }

    return 0;
}



// Role 1 Menu - Core System and Product Management (This is just a placeholder)
void role1Menu(int isAdmin) {
    int choice;
    char choiceStr[10];
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        border(default_border);
        printf("\n=== Product Management Menu ===\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Search Product by Name\n");
        if (isAdmin) {
            printf("6. Return to Main Menu\n");
        } else {
            printf("6. Logout\n");
            printf("7. Exit\n");
        }
        
        getValidInput("Enter your choice: ", choiceStr, sizeof(choiceStr));
        choice = atoi(choiceStr);

        switch (choice) {
            case 1:
                addProduct();
                system("pause");
                break;
            case 2:
                viewProducts();
                system("pause");
                break;
            case 3:
                updateProduct();
                system("pause");
                break;
            case 4:
                deleteProduct();
                system("pause");
                break;
            case 5:
                searchProductByName();
                system("pause");
                break;
            case 6:
                return;
            case 7:
                if (!isAdmin) {
                    printf("\nThank you for using the system. Goodbye!\n");
                    exit(0);
                }
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 2 Menu - Inventory and Stock Management (This is just a placeholder)
void role2Menu(int isAdmin) {
    int choice;
    char choiceStr[10];
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        border(default_border);
        printf("\n=== Inventory and Stock Management ===\n");
        printf("1. Add stock inventory record\n");
        printf("2. Update stock level\n");
        printf("3. Remove Discontinued Stock\n");
        printf("4. View Current Inventory\n");
        if (isAdmin) {
            printf("5. Return to Main Menu\n");
        } else {
            printf("5. Logout\n");
            printf("6. Exit\n");
        }
        
        getValidInput("Enter your choice: ", choiceStr, sizeof(choiceStr));
        choice = atoi(choiceStr);

        clearScreen();
        switch (choice) {
            char ch;
            case 1:
                add_record();
                system("pause");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                break;
            case 2:
                update_stock();
                system("pause");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                break;
            case 3:
                remove_discontinued();
                system("pause");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                break;
            case 4:
                view_record();
                system("pause");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                break;
            case 5:
                return;
            case 6:
                if (!isAdmin) {
                    printf("\nThank you for using the system. Goodbye!\n");
                    exit(0);
                }
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 3 Menu - Category and Supplier Management (This is just a placeholder)
void role3Menu(int isAdmin) {
    int choice;
    char choiceStr[10];
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        border(default_border);
        printf("\n=== Category and Supplier Management ===\n");
        printf("1. Add Category/Supplier\n");
        printf("2. Update Category/Supplier\n");
        printf("3. Delete Category/Supplier\n");
        printf("4. View Categories/Suppliers\n");
        if (isAdmin) {
            printf("5. Return to Main Menu\n");
        } else {
            printf("5. Logout\n");
            printf("6. Exit\n");
        }
        
        getValidInput("Enter your choice: ", choiceStr, sizeof(choiceStr));
        choice = atoi(choiceStr);

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
            case 6:
                if (!isAdmin) {
                    printf("\nThank you for using the system. Goodbye!\n");
                    exit(0);
                }
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Role 4 Menu - User and Transaction Management (This is just a placeholder)
void role4Menu(int isAdmin) {
    int choice;
    char choiceStr[10];
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        border(default_border);
        printf("\n=== User and Transaction Management ===\n");
        printf("1. Add User/Transaction\n");
        printf("2. Update User/Transaction\n");
        printf("3. Delete User/Transaction\n");
        printf("4. View Users/Transactions\n");
        if (isAdmin) {
            printf("5. Return to Main Menu\n");
        } else {
            printf("5. Logout\n");
            printf("6. Exit\n");
        }
        
        getValidInput("Enter your choice: ", choiceStr, sizeof(choiceStr));
        choice = atoi(choiceStr);

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
            case 6:
                if (!isAdmin) {
                    printf("\nThank you for using the system. Goodbye!\n");
                    exit(0);
                }
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                system("pause");
        }
    } while (1);
}

// Main Menu
void displayMainMenu() {
    int choice;
    char choiceStr[10];
    do {
        clearScreen();
        border(default_border);
        add_space(15);
        printf("Inventory Management System\n");
        border(default_border);
        printf("Current User: %s (Role: %s)\n", currentUser.username, currentUser.role);
        
        if (strcmp(currentUser.role, "administrator") == 0) {
            // Administrator sees all options
            printf("1. Core System and Product Management\n");
            printf("2. Inventory and Stock Management\n");
            printf("3. Category and Supplier Management\n");
            printf("4. User and Transaction Management\n");
            printf("5. Administrator Menu\n");
            printf("6. Logout\n");
            printf("7. Exit\n");
            
            getValidInput("Enter your choice: ", choiceStr, sizeof(choiceStr));
            choice = atoi(choiceStr);

            switch (choice) {
                case 1:
                    role1Menu(1);  // Pass 1 for admin
                    break;
                case 2:
                    role2Menu(1);  // Pass 1 for admin
                    break;
                case 3:
                    role3Menu(1);  // Pass 1 for admin
                    break;
                case 4:
                    test_mains();  // Pass 1 for admin
                    break;
                case 5:
                    adminMenu();
                    break;
                case 6:
                    return;
                case 7:
                    printf("\nThank you for using the system. Goodbye!\n");
                    exit(0);
                default:
                    printf("\nInvalid choice! Please try again.\n");
            }
        } else {
            // For other roles, show their specific menu
            if (strcmp(currentUser.role, "product_manager") == 0) {
                role1Menu(0);  // Pass 0 for non-admin
                return;
            } else if (strcmp(currentUser.role, "inventory_manager") == 0) {
                role2Menu(0);  // Pass 0 for non-admin
                return;
            } else if (strcmp(currentUser.role, "supplier_manager") == 0) {
                role3Menu(0);  // Pass 0 for non-admin
                return;
            } else if (strcmp(currentUser.role, "transaction_manager") == 0) {
                test_mains();  // Pass 0 for non-admin
                return;
            }
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