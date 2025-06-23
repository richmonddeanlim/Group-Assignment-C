#include "transactions.h"

FILE *productFile;
FILE *recordFile;
FILE *credentialFile;
char *recordFilepath = "inventory_record.txt";
char *credentialFilepath = "staff_credentials.txt";
char *productFilepath = "product.txt";

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
                    viewArchive();
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
    bool validAnswer;
    char selection;
    printf("Would you like to continue? (Y/N)\n");
    do {
        validAnswer = false;
        printf(">>>   ");
        scanf("%c",&selection);
        selection = tolower(selection);
        while (getchar() != '\n');
        switch (selection) {
            case 'y':
                return true;
                break;
            case 'n':
                return false;
                break;
            default:
                printf("\nInvalid answer. Please try again.\n");
        }
    } while (validAnswer == false);
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
    // Variable Declarations
    int filterType, actionChoice, statusChoice;
    bool repeat = true, validAnswer = false, validActionSelection = false, validStatusSelection = false, productIDFound = false;
    char inputUserID[50], inputAction[50], inputStatus[50], inputProductID[50], storedUserID[50], storedProductID[50];
    struct inventory_record inventoryRecord;
    
    while (getchar() != '\n');
    while (repeat == true) {        
        FILE *file = fopen(recordFilepath, "r");
        
        char credentialLine[256];
        char productLine[256];

        do {
            FILE *file2 = fopen(credentialFilepath, "r");
            validAnswer = false;
            getValidInput("Enter User ID to filter: ", inputUserID, sizeof(inputUserID));     // User enter UserID to check
            
            while (fgets(credentialLine, sizeof(credentialLine), file2)) {
                sscanf(credentialLine, "%49[^,]",storedUserID);
                storedUserID[strcspn(storedUserID, "\r\n")] = 0;
                if (strcmp(inputUserID, storedUserID) == 0) {
                    validAnswer = true;
                    printf("");
                    break;
                }
            }
            if (validAnswer == false) {
                printf("User ID: %s not found. Please try again.\n\n",inputUserID); 
            }
            fclose(file2);
        } while(validAnswer == false);


        do {
            printf("%s",menutext);
            printf("User selected: %s\n\n",inputUserID);
            printf("Would you like to filter transactions?\n");                            
            printf("1. ProductID\n");                                      // User is prompted to choose filters
            printf("2. Action\n");
            printf("3. Status\n");
            printf("4. No filters\n\n");
            validAnswer = false;
            printf(">>>   ");
            scanf("%d",&filterType);        // System receive the choice of filters
            while (getchar() != '\n');
            switch(filterType) {             
                case 1:
                    printf("%s",menutext);
                    do {
                        FILE *file3 = fopen(productFilepath,"r");
                        printf("Enter ProductID to filter:\n");
                        getValidInput(">>>   ", inputProductID, sizeof(inputProductID));
                        while (fgets(productLine, sizeof(productLine), file3)) {
                            sscanf(productLine, "%49[^,]",storedProductID);
                            storedProductID[strcspn(storedProductID, "\r\n")] = 0;
                            if (strcmp(inputProductID, storedProductID) == 0) {
                                productIDFound = true;
                                printf("");
                                break;
                            }
                        }
                        if (productIDFound == false) {
                            printf("Product ID: %s not found. Please try again.\n\n",inputProductID); 
                        }
                        fclose(file3);
                    } while (productIDFound == false);
                    validAnswer = true;
                    break;
                case 2:
                    printf("%s",menutext);
                    printf("Enter Action to filter\n\n");
                    printf("1. Restock\n");
                    printf("2. Out\n");
                    printf("3. Discontinue\n");
                    printf("4. Return\n\n");
                    do {
                        validActionSelection = false;
                        printf(">>>   ");
                        scanf("%d",&actionChoice);
                        switch(actionChoice) {
                            case 1:
                                strcpy(inputAction, "Restock");
                                printf("Im working");
                                validActionSelection = true;
                                break;
                            case 2:
                                strcpy(inputAction, "Out");
                                validActionSelection = true;
                                break;
                            case 3:
                                strcpy(inputAction, "Discontinue");
                                validActionSelection = true;
                                break;
                            case 4:
                                strcpy(inputAction, "Return");
                                validActionSelection = true;
                                break;
                            default:
                                validActionSelection = false;
                                printf("Invalid option entered. Please try again.\n\n");
                        }
                    } while (validActionSelection == false);
                    validAnswer = true;
                    break;
                case 3:
                    printf("%s",menutext);
                    printf("Enter Status to filter\n\n");
                    printf("1. Active\n");
                    printf("2. Discontinued\n");
                    printf("3. Back\n\n");
                    do {
                        validStatusSelection = false;
                        printf(">>>   ");
                        scanf("%d",&statusChoice);
                        switch(statusChoice) {
                            case 1:
                                strcpy(inputStatus, "Active");
                                validStatusSelection = true;
                                validAnswer = true;
                                break;
                            case 2:
                                strcpy(inputStatus,"Discontinued");
                                validStatusSelection = true;
                                validAnswer = true;
                                break;
                            case 3:
                                validStatusSelection = true;
                                validAnswer = false;
                                break;
                            default:
                                printf("Invalid option entered. Please try again.\n\n");
                        }
                    } while (validStatusSelection == false);
                    break;
                case 4:
                    validAnswer = true;
                    break;
                default:
                    printf("Invalid option entered. Please try again.\n");
                    validAnswer = false;
                }
            } while (validAnswer == false);

        char line[256];
        fgets(line, sizeof(line), file);        // Remove header row for inventory_record.txt

        printf("\n%s",menutext);
        printf("Showing transaction history for user: %s\n",inputUserID);
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "Date", "ProductID", "Action", "Quantity", "Status");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");


        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%19[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,]", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, &inventoryRecord.quantity, inventoryRecord.status, inventoryRecord.userID);
            
            inventoryRecord.userID[strcspn(inventoryRecord.userID, "\r\n")] = 0;
            if (filterType == 1) {
                if (strcmp(inputUserID, inventoryRecord.userID) == 0 && strstr(inventoryRecord.product_id, inputProductID) != NULL && strstr(inventoryRecord.date, "2025") != NULL) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
                }
            } else if (filterType == 2) {
                if (strcmp(inputUserID, inventoryRecord.userID) == 0 && strstr(inventoryRecord.action, inputAction) != NULL && strstr(inventoryRecord.date, "2025") != NULL) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
                }
            } else if (filterType == 3) {
                if (strcmp(inputUserID, inventoryRecord.userID) == 0 && strstr(inventoryRecord.status, inputStatus) != NULL && strstr(inventoryRecord.date, "2025") != NULL) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
                }
            } else {
                if (strcmp(inputUserID, inventoryRecord.userID) == 0 && strstr(inventoryRecord.date, "2025") != NULL) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
                }
            }
        }
        fclose(file);
        printf("\n");
        repeat = continueOrNo();
        printf("\n");
    }
}

void viewArchive() {
    bool repeat = true;
    char inputUserID[50];
    struct inventory_record inventoryRecord;
    
    while (getchar() != '\n');

    while (repeat == true) {
        FILE *file = fopen(recordFilepath, "r");
        getValidInput("Enter User ID to filter: ", inputUserID, sizeof(inputUserID));

        char line[256];
        fgets(line, sizeof(line), file);

        printf("\n\nShowing archived transaction history for user: %s\n",inputUserID);
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "Date", "ProductID", "Action", "Quantity", "Status");
        printf("%-12s %-10s %-12s %-8s %-12s\n", "------------", "----------", "------------", "--------", "------------");

        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%19[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,]", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, &inventoryRecord.quantity, inventoryRecord.status, inventoryRecord.userID);
            
            inventoryRecord.userID[strcspn(inventoryRecord.userID, "\r\n")] = 0;
            if (strcmp(inputUserID, inventoryRecord.userID) == 0 && strstr(inventoryRecord.date, "2025") == NULL) {
                printf("%-12s %-10s %-12s %-8d %-12s\n", inventoryRecord.date, inventoryRecord.product_id, inventoryRecord.action, inventoryRecord.quantity, inventoryRecord.status);
            }
        }
        fclose(file);
        printf("\n");
        repeat = continueOrNo();
        printf("\n");
    } 
}