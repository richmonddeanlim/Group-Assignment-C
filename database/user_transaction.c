#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "transactions.h"

FILE *recordFile;
char *recordFilepath = "inventory_record.txt";

int main() {
    int selection;
    while (true) {
        printf("%s",menutext);
        printf("Welcome to User and Transaction Management System!\n\n");
        printf("1. Modify users\n");
        printf("2. Modify transaction records\n");
        printf("3. Log out\n\n");
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
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    validAnswer = true;
                    break;
                case 2:
                    validAnswer = true;
                    break;
                case 3:
                    validAnswer = true;
                    break;
                case 4:
                    validAnswer = true;
                    break;
                case 5:
                    validAnswer = true;
                    return;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    while (getchar() != '\n');
                        break;
            }
        }   
    }
}

void transactions() {
    while (true) {
        bool validAnswer = false;
        int selection;
        printf("%s",menutext);
        printf("1. View transaction history\n");
        printf("2. Archived transactions\n");
        printf("3. Exit to main menu\n\n");
        while (validAnswer == false) {
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    viewTransactions();
                    validAnswer = true;
                    break; 
                case 2:
                    validAnswer = true;
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
    }   
}

bool continueOrNo() {
    char selection;
    printf("Would you like to continue? (Y/N)\n");
    printf(">>>   ");
    scanf("%c",&selection);
    selection = tolower(selection);
    switch (selection) {
        case 'y':
            return true;
            break;
        case 'n':
           return false;
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

void viewTransactions() {
    bool repeat = true;
    char inputUserID[50];
    struct inventory_record inventoryRecord;
    
    while (getchar() != '\n');

    while (repeat == true) {
        FILE *file = fopen(recordFilepath, "r");
        getValidInput("Enter User ID to filter: ", inputUserID, sizeof(inputUserID));

        char line[256];
        fgets(line, sizeof(line), file);

        printf("\n\nShowing transaction history for user: %s\n",inputUserID);
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "Date", "ProductID", "Action", "Quantity", "Status");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");

        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%19[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,]", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, &inventoryRecord.quantity, inventoryRecord.status, inventoryRecord.userID);
            
            inventoryRecord.userID[strcspn(inventoryRecord.userID, "\r\n")] = 0;
            if (strcmp(inputUserID, inventoryRecord.userID) == 0) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
            }
        }
        fclose(file);
        printf("\n");
        repeat = continueOrNo();
        while (getchar() != '\n');
        printf("\n");
    }
}