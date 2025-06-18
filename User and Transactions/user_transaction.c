#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "transactions.h"

const char *menutext = "\n--- User and Transaction Management System ---\n\n";
const char *customerFile = "customer_credentials.txt";

#define MAX_CUSTOMERS 100

// Define the customer struct

Customer customers[MAX_CUSTOMERS]; // Array to store customer data
int customerCount = 0; // Number of customers loaded

void loadCustomerCredentials() {
    FILE *file = fopen(customerFile, "r");
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
    printf("Im working");
    fclose(file);
}

int main() {
    int selection;
    loadCustomerCredentials(); // Load customer credentials at the start
    while (1) {
        bool validanswer = false;
        printf("%s",menutext);
        printf("Welcome to User and Transaction Management System!\n\n");
        printf("1. Modify users\n");
        printf("2. Modify transaction records\n\n");
        while (validanswer == false) {
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    user();
                    validanswer = true;    
                    break;
                case 2:
                    transactions();
                    validanswer = true;   
                    break;
                case 3:
                    validanswer = true;
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
    int selection;
    printf("%s",menutext);
    printf("1. Add new user\n");
    printf("2. Update user information\n");
    printf("3. Delete user account\n");
    printf("4. View user details\n");
    printf("5. Back to main menu\n\n");
    printf(">>>   ");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            addUser();
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
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
        
        if (strlen(buffer) == 0) {
            printf("\nInput cannot be empty! Please try again.\n");
            continue;
        }
        break;
    } while (1);
}

void addUser() {
    bool duplicateUsername = true;
    Customer Customer;
    while (getchar() != '\n');

    while (duplicateUsername = true) {
        getValidInput("Enter new username: ", Customer.username, sizeof(Customer.username));

        for (int i = 0; i < customerCount; i++) {
            if (strcmp(customers[i].username, Customer.username) == 0) {
                printf("Error: Username already exists.\n");
            }
        }
        duplicateUsername = false;
        break;
    }
    

    getValidInput("Enter new password: ", Customer.password, sizeof(Customer.password));

    // Add the new user to the customers array
    strcpy(customers[customerCount].username, Customer.username);
    strcpy(customers[customerCount].password, Customer.password);
    customerCount++;

    // Update the customer_credentials.txt file
    FILE *file;
    file = fopen("customer_credentials.txt", "a");
    if (file == NULL) {
        perror("Error: Could not open file for appending");
        return;
    }
    fprintf(file, "%s,%s\n", Customer.username, Customer.password); // Ensure newline is added
    fclose(file);

    printf("User '%s' added successfully and saved to file.\n", Customer.username);
}
