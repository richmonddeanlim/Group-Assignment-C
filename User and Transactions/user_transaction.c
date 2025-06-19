#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "transactions.h"

Customer customers[MAX_CUSTOMERS]; // Array to store customer data
int customerCount = 0; // Number of customers loaded

void loadCustomerCredentials() {
    FILE *file = fopen(customerFile, "r");
    customerCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && customerCount < MAX_CUSTOMERS) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(customers[customerCount].username, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(customers[customerCount].password, token);
                customers[customerCount].password[strcspn(customers[customerCount].password, "\n")] = '\0';
                customerCount++;
            }
        }
    }
    fclose(file);
}

int main() {
    int selection;
    loadCustomerCredentials();
    while (true) {
        printf("%s",menutext);
        printf("Welcome to User and Transaction Management System!\n\n");
        printf("1. Modify users\n");
        printf("2. Modify transaction records\n\n");
        bool validAnswer = false;
        while (validAnswer == false) {
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    validAnswer = true; 
                    user();   
                    break;
                case 2:
                    validAnswer = true;  
                    transactions();
                    break;
                case 3:
                    validAnswer = true;
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    while (getchar() != '\n');
                    break;
            }
        }
        if (selection == 3) {
            break;
        }
    }
    printf("%s",menutext);
    printf("You have succesfully logged out.\n\n");    
}

void user() {
    while (true) {

        bool validAnswer = false;
        int selection;
        printf("%s",menutext);
        printf("1. Add new user\n");
        printf("2. Update user information\n");
        printf("3. Delete user account\n");
        printf("4. View user details\n");
        printf("5. Back to main menu\n\n");;
        while (validAnswer == false) {
            loadCustomerCredentials();
            printf("I loaded again");
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    addUser();
                    validAnswer = true;
                    break;
                case 2:
                    updateUser();
                    validAnswer = true;
                    break;
                case 3:
                    deleteUser();
                    validAnswer = true;
                    break;
                case 4:
                    viewUser();
                    validAnswer = true;
                    break;
                case 5:
                    main();
                    validAnswer = true;
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    while (getchar() != '\n');
                        break;
            }
        }   
    }
}

void transactions() {
    int selection;
    printf("%s",menutext);
    printf("1. Add new transaction record\n");
    printf("2. Update transaction status\n");
    printf("3. Delete transaction\n");
    printf("4. View transaction history\n\n");
    printf(">>>   ");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            break; 
        case 2:
            break; 
        case 3:
            break; 
        case 4:
            break;   
        case 5:
            break;
        }
}

void getValidInput(char* prompt, char* buffer, int maxLength) {
    do {
        printf("%s", prompt);
        fgets(buffer, maxLength, stdin);
        buffer[strcspn(buffer, "\n")] = 0; 
        
        if (strlen(buffer) == 0) {
            printf("\nInput cannot be empty! Please try again.\n");
            continue;
        }
        break;
    } while (1);
}

bool duplicateChecker(char* targetedtext) {
    FILE *file = fopen(customerFile, "r");
    Customer Customer;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].username, targetedtext) == 0) {
            printf("Username already exists. Please try again.\n\n");
            return true;
            break;
        }
    }
    return false;
}

void addUser() {
    bool duplicateUsername;
    Customer Customer;
    while (getchar() != '\n');
    printf("%s",menutext);

    do {
        duplicateUsername = false;
        getValidInput("Enter new username: ", Customer.username, sizeof(Customer.username));
        duplicateUsername = duplicateChecker(Customer.username);
    } while (duplicateUsername == true);

    getValidInput("Enter new password: ", Customer.password, sizeof(Customer.password));
    // Add the new user to the customers array
    strcpy(customers[customerCount].username, Customer.username);
    strcpy(customers[customerCount].password, Customer.password);
    customerCount++;

    FILE *file;
    file = fopen("customer_credentials.txt", "a");
    fprintf(file, "%s,%s\n", Customer.username, Customer.password); 
    fclose(file);

    printf("User '%s' added successfully and saved to file.\n", Customer.username);
}

void deleteUser() {
    FILE *file = fopen(customerFile, "r");
    FILE *tempFile = fopen("temporary.txt", "w");
    Customer Customer;
    while (getchar()!= '\n');
    bool successfullDelete = false;
    printf("%s",menutext);

    while (!successfullDelete) {
        getValidInput("Enter username to be deleted: ", Customer.username, sizeof(Customer.username));
        for (int i = 0; i < customerCount; i++) {
            if (strcmp(customers[i].username, Customer.username) == 0) {
                successfullDelete = true;
                break;
            }
        }

        if (!successfullDelete) {
            printf("Error: Username '%s' not found. Please try again.\n\n", Customer.username);
        }
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char username[50];
        sscanf(line, "%49[^,]", username); // extract usernames from the line

        if (strcmp(username, Customer.username) != 0) {
            fputs(line, tempFile); // write all lines except the one to delete
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(customerFile);               // replace old file with new file
    rename("temporary.txt", "customer_credentials.txt");
    printf("User '%s' has been deleted from the database successfully.\n", Customer.username);
}

void updateUser() {
    char oldUsername[50], newUsername[50], oldPassword[50], newPassword[50];
    bool duplicateUsername, userFound;
    int selection;
    FILE *file = fopen(customerFile, "r");
    FILE *tempFile = fopen("temporary.txt", "w");
    Customer Customer;
    printf("%s",menutext);
    while (getchar() != '\n');
    do {
        getValidInput("Enter username to be updated: ", oldUsername, sizeof(oldUsername));
        for (int i = 0; i < customerCount; i++) {
            if (strcmp(customers[i].username, oldUsername) == 0) {
                userFound = true;
                break;
            }
        }
        if (!userFound) {
            printf("Error: Username '%s' not found. Please try again.\n\n", oldUsername);
        }
    } while (!userFound);
    printf("%s",menutext);
    printf("Selected Username: %s\n\n", oldUsername);
    printf("1. Username\n");
    printf("2. Password\n");
    printf("\nPlease choose which data to be updated.");
    printf("\n>>>   ");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            printf("%s",menutext);
            while (getchar() != '\n');
            do {                // Enter new username section
                duplicateUsername = false;
                getValidInput("Enter new username: ", newUsername, sizeof(newUsername));
                for (int i = 0; i < customerCount; i++) {
                    if (strcmp(customers[i].username, newUsername) == 0) {
                        printf("\nUsername already exists. Please try again.\n");
                        duplicateUsername = true;
                        break;
                    }
                }
            } while (duplicateUsername == true);

            char line[256];
            while (fgets(line, sizeof(line), file)) {
                char username[50], password[50];
                sscanf(line, "%49[^,],%49s", username, password); // Extract username and password from the line

                if (strcmp(username, oldUsername) == 0) {
                    fprintf(tempFile, "%s,%s\n", newUsername, password); // Replace username
                } else {
                    fputs(line, tempFile); // Write other lines unchanged
                }
            }
            printf("\nUsername updated successfully.\n");
            break;
        case 2:
            while (getchar() != '\n');
            duplicateUsername = false;      // Enter new password section

            printf("%s",menutext);
            getValidInput("Enter new password: ", newPassword, sizeof(newPassword));
                
            while (fgets(line, sizeof(line), file)) {
                char username[50], password[50];
                sscanf(line, "%49[^,],%49s", username, password); 

                if (strcmp(username, oldUsername) == 0) {
                    fprintf(tempFile, "%s,%s\n", username, newPassword); // Replace password
                } else {
                    fputs(line, tempFile); // Write other lines unchanged
                }
            }
            printf("\nPassword updated successfully.\n");
            break;
        }
        fclose(file);
        fclose(tempFile);
        remove(customerFile);
        rename("temporary.txt","customer_credentials.txt");
    }

void viewUser() {
    Customer Customer;
    FILE *file = fopen(customerFile, "r");
    
    printf("\n%s",menutext);
    printf("%-20s %-20s\n", "Username", "Password");
    printf("%-20s %-20s\n", "-------------------", "-------------------");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char username[50], password[50];
        sscanf(line, "%49[^,],%49s", Customer.username, Customer.password); 
        printf("%-20s %-20s\n", Customer.username, Customer.password);
    }
    fclose(file);
}

