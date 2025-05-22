#include <stdio.h>
#include <stdbool.h>

const char *menutext = "\n--- User and Transaction Management System ---\n\n";

void user();
void transactions();

int main() {
    int selection;
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
        printf("%s",menutext);
        printf("You have succesfully logged out.\n\n");
        break;
    }
    
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