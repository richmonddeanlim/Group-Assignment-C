#include "../header/inventory_system.h"

// File path constant
const char* credentials = "database/staff_credentials.txt";

// Global variables
Staff users[MAX_USERS];
int userCount = 0;
Staff currentUser;

// Load users from file
void loadUsers() {
    FILE *file = fopen(credentials, "r");
    if (file == NULL) {
        printf("Error opening staff credentials file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    userCount = 0;

    while (fgets(line, sizeof(line), file) && userCount < MAX_USERS) {
        char *token = strtok(line, ",");
        strcpy(users[userCount].username, token);
        
        token = strtok(NULL, ",");
        strcpy(users[userCount].password, token);
        
        token = strtok(NULL, "\n");
        strcpy(users[userCount].role, token);
        
        userCount++;
    }

    fclose(file);
}

// Clear screen function
void clearScreen() {
    system("cls");
}

// Add new user function
void addUser() {
    if (userCount >= MAX_USERS) {
        printf("\nMaximum number of staff members reached!\n");
        system("pause");
        return;
    }

    Staff newUser;
    printf("\n=== Add New Staff Member ===\n");
    printf("Enter username: ");
    scanf("%s", newUser.username);
    
    // Check if username already exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("\nUsername already exists!\n");
            system("pause");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);
    
    // Display role selection menu
    printf("\n=== Role Selection ===\n");
    printf("1. Administrator\n");
    printf("2. Product Manager\n");
    printf("3. Inventory Manager\n");
    printf("4. Supplier Manager\n");
    printf("5. Transaction Manager\n");
    printf("\nEnter role number (1-5) or type the role name: ");
    
    char roleInput[50];
    scanf("%s", roleInput);
    
    // Convert number input to role name if needed
    if (strlen(roleInput) == 1 && roleInput[0] >= '1' && roleInput[0] <= '5') {
        switch (roleInput[0]) {
            case '1':
                strcpy(newUser.role, "administrator");
                break;
            case '2':
                strcpy(newUser.role, "product_manager");
                break;
            case '3':
                strcpy(newUser.role, "inventory_manager");
                break;
            case '4':
                strcpy(newUser.role, "supplier_manager");
                break;
            case '5':
                strcpy(newUser.role, "transaction_manager");
                break;
        }
    } else {
        strcpy(newUser.role, roleInput);
    }

    // Validate role
    if (strcmp(newUser.role, "administrator") != 0 && 
        strcmp(newUser.role, "product_manager") != 0 && 
        strcmp(newUser.role, "inventory_manager") != 0 && 
        strcmp(newUser.role, "supplier_manager") != 0 && 
        strcmp(newUser.role, "transaction_manager") != 0) {
        printf("\nInvalid role! Staff member not added.\n");
        system("pause");
        return;
    }

    // Add user to array
    users[userCount] = newUser;
    userCount++;

    // Save to file
    FILE *file = fopen(credentials, "a");
    if (file == NULL) {
        printf("\nError saving staff member to file!\n");
        system("pause");
        return;
    }
    fprintf(file, "%s,%s,%s\n", newUser.username, newUser.password, newUser.role);
    fclose(file);

    printf("\nStaff member added successfully!\n");
    system("pause");
}

// Delete user function
void deleteUser() {
    char username[50];
    printf("\n=== Delete Staff Member ===\n");
    printf("Enter username to delete: ");
    scanf("%s", username);

    // Find user
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("\nStaff member not found!\n");
        system("pause");
        return;
    }

    // Don't allow deleting the last admin
    if (strcmp(users[userIndex].role, "administrator") == 0) {
        int adminCount = 0;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].role, "administrator") == 0) {
                adminCount++;
            }
        }
        if (adminCount <= 1) {
            printf("\nCannot delete the last administrator!\n");
            system("pause");
            return;
        }
    }

    // Remove user from array
    for (int i = userIndex; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    // Update file
    FILE *file = fopen(credentials, "w");
    if (file == NULL) {
        printf("\nError updating staff file!\n");
        system("pause");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);

    printf("\nStaff member deleted successfully!\n");
    system("pause");
}

// Admin Menu
void adminMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== Administrator Menu ===\n");
        printf("1. Add New Staff Member\n");
        printf("2. Delete Staff Member\n");
        printf("3. Change Staff Password\n");
        printf("4. View All Staff Members\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                deleteUser();
                break;
            case 3:
                changePassword();
                break;
            case 4:
                printf("\n=== All Staff Members ===\n");
                printf("+------------------+---------------------+\n");
                printf("| %-16s | %-19s |\n", "Username", "Role");
                printf("+------------------+---------------------+\n");
                for (int i = 0; i < userCount; i++) {
                    printf("| %-16s | %-19s |\n", users[i].username, users[i].role);
                }
                printf("+------------------+---------------------+\n");
                printf("\nTotal Staff Members: %d\n", userCount);
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

// Change Password Function
void changePassword() {
    char username[50];
    char newPassword[50];
    int found = 0;

    printf("\nEnter username to change password: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Enter new password: ");
            scanf("%s", newPassword);
            strcpy(users[i].password, newPassword);
            found = 1;

            // Update the file
            FILE *file = fopen(credentials, "w");
            if (file != NULL) {
                for (int j = 0; j < userCount; j++) {
                    fprintf(file, "%s,%s,%s\n", users[j].username, users[j].password, users[j].role);
                }
                fclose(file);
                printf("Password updated successfully!\n");
            } else {
                printf("Error updating password in file!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Staff member not found!\n");
    }
    system("pause");
}
