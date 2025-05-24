#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../header/inventory_system.h"

// File path constant
const char* credentials = "database/user_credentials.txt";

// Global variables
User users[MAX_USERS];
int userCount = 0;
User currentUser;

// Load users from file
void loadUsers() {
    FILE *file = fopen(credentials, "r");
    if (file == NULL) {
        printf("Error opening user credentials file!\n");
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
        printf("\nMaximum number of users reached!\n");
        system("pause");
        return;
    }

    User newUser;
    printf("\n=== Add New User ===\n");
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
    printf("Enter role (admin/role1/role2/role3/role4): ");
    scanf("%s", newUser.role);

    // Validate role
    if (strcmp(newUser.role, "admin") != 0 && 
        strcmp(newUser.role, "role1") != 0 && 
        strcmp(newUser.role, "role2") != 0 && 
        strcmp(newUser.role, "role3") != 0 && 
        strcmp(newUser.role, "role4") != 0) {
        printf("\nInvalid role! User not added.\n");
        system("pause");
        return;
    }

    // Add user to array
    users[userCount] = newUser;
    userCount++;

    // Save to file
    FILE *file = fopen(credentials, "a");
    if (file == NULL) {
        printf("\nError saving user to file!\n");
        system("pause");
        return;
    }
    fprintf(file, "%s,%s,%s\n", newUser.username, newUser.password, newUser.role);
    fclose(file);

    printf("\nUser added successfully!\n");
    system("pause");
}

// Delete user function
void deleteUser() {
    char username[50];
    printf("\n=== Delete User ===\n");
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
        printf("\nUser not found!\n");
        system("pause");
        return;
    }

    // Don't allow deleting the last admin
    if (strcmp(users[userIndex].role, "admin") == 0) {
        int adminCount = 0;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].role, "admin") == 0) {
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
        printf("\nError updating user file!\n");
        system("pause");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s,%s,%s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);

    printf("\nUser deleted successfully!\n");
    system("pause");
}

// Admin Menu
void adminMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n=== Administrator Menu ===\n");
        printf("1. Add New User\n");
        printf("2. Delete User\n");
        printf("3. Change User Password\n");
        printf("4. View All Users\n");
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
                printf("\n=== All Users ===\n");
                for (int i = 0; i < userCount; i++) {
                    printf("Username: %s, Role: %s\n", users[i].username, users[i].role);
                }
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
        printf("User not found!\n");
    }
    system("pause");
}
