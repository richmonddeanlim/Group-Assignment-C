#include <stdio.h>
#include <stdbool.h>

const char *menutext = "\n--- User and Transaction Management System ---\n\n";

bool flag = true;

void user(int selection);
void transactions(int selection);

int main() {
    int selection;
    while (flag==true) {
        printf("%s",menutext);
        printf("Welcome to User and Transaction Management System!\n\n");
        printf("1. Modify users\n");
        printf("2. Modify transaction records\n\n");
        while (flag == true) {
            printf(">>>   ");
            scanf("%d",&selection);
            switch (selection) {
                case 1:
                    user(selection);
                    flag = false;
                    break;
                case 2:
                    transactions(selection);
                    flag = false;
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    while (getchar() != '\n');
                    continue;
                break;
            }
        }  
        flag = true;
    }    
}

void user(int selection) {
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

void transactions(int selection) {
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