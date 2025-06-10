#include "decoration.c"
#include "../header/inventory_record.h"

// Global Variable Definitions
FILE *file_product;
FILE *file_record;
char product_location[] = "../database/product.txt";
char record_location[] = "../database/inventory_record.txt";

// data structure for the inventory_record

// option validation function
void option_validation(char *input_text,int *choice,int range)
{
    while(1)
    {
        printf("%s", input_text); 
        if(scanf("%d", choice))
        {
            for(int i = 0; i < range;i++)
            {
                if(*choice == i + 1)
                {
                    return;
                }
    
                else if(*choice != i && i == range - 1)
                {
                    printf("There is no such option\n");
                }
            } 
        }
    
        else
        {   char ch;
            printf("Pls input an integer\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

// int valdiation
void integer_valdiation(char *input_text,int *user_input )
{
    char ch;
    while(1)
    {
        printf("%s", input_text); 
        if(scanf("%d", user_input))
        {
            while ((ch = getchar()) != '\n' && ch != EOF);
            return;
        }
        
        else
        {
            printf("Pls input an integer\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

// array length
void arr_len(char array[], int *array_len)
{
    // date validation
    for(int i = 0; array[i] != '\0'; i++) // '\0' represent null value
    {
        *array_len += 1;
    }
}

// lowering
void str_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// retrieving data inside teh product txt
void data_product(char data[100][100][100], int *line_array)
{
    FILE *file_product = fopen(product_location, "r");

    if(file_product == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char raw_product[100][100];
    int line = 0;

    while(fgets(raw_product[line], 100, file_product) != NULL) {
        line++;
    }

    fclose(file_product);

    for(int i = 0; i < line + 1; i++) {
        char *token = strtok(raw_product[i], ",");
        for(int j = 0; j < 5 && token != NULL; j++) {
            strncpy(data[i][j], token, 99);
            data[i][j][99] = '\0';
            token = strtok(NULL, ",");
        }
    }

    *line_array = line;
}

// retrieving data inside the data record
void data_record(char data[100][100][100], int *line_array)
{
    FILE *file_record = fopen(record_location, "r");

    if(file_record == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char raw_record[100][100];
    int line = 0;

    while(fgets(raw_record[line], 100, file_record) != NULL) {
        line++;
    }

    fclose(file_record);

    for(int i = 0; i < line + 1; i++) {
        char *token = strtok(raw_record[i], ",");
        for(int j = 0; j < 5 && token != NULL; j++) {
            strncpy(data[i][j], token, 99);
            data[i][j][99] = '\0';
            token = strtok(NULL, ",");
        }
    }

    *line_array = line;
}

// Function to clean string by removing whitespace and null characters
void clean_string(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r' && str[i] != '\t') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

// inventory record management menu
int menu()
{
   // giving menu interface for user
    border(default_border);
    add_space(15);
    printf("Iventory and Stock management\n");
    border(default_border);
    printf("1. Add stock inventory record\n");
    printf("2. Update stock level\n");
    printf("3. Remove Discontinued Stock\n");
    printf("4. View Current Inventory\n");
    printf("5. Exit\n");
    border(default_border);
    
    // geting user choices
    int choice;
    option_validation("Enter your choice: ",&choice,5);

    return choice; 
}

// function adding new record for inventory
void add_record()               
{
    // File location
    struct inventory_record record;
    char ch;
    char condition;
    char record_loop = 'y';
    int line = 0;

    // retrieving product data
    char product_data[100][100][100];
    data_product(product_data, &line);
    
    char product_id[100][100];
    // insert the data into product id
    for(int i=0; i < line ;i++)
    {
        strncpy(product_id[i],product_data[i][0],99); 
    }
            
    while(record_loop == 'y' || record_loop == 'Y')
    {

        // getting date input
        while(1)
        {
            int array_len = 0;
            
            // getting user input
            printf("Enter the date (dd-mm-yyyy): ");
            scanf("%s", &record.date);
            
            // getting arr len
            arr_len(record.date, &array_len);
            
            // further date validation
            if(array_len == 10)
            {
                if(record.date[2] == '-' && record.date[5] == '-')
                {
                    int day = (int) (((record.date[0] - '0') * 10) + record.date[1] - '0'); 
                    // ensure the date not above 31
                    if( day <= 31 && day > 0) // subtract with '0' will return the int value (converting ascii to int)
                    {
                        int month = (int) (((record.date[3] - '0') * 10) + record.date[4] - '0');
                        // ensure the month not above 12
                        if( month <= 12 && month > 0)
                        {
                            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
                            break;
                        }
                        
                        else
                        {
                            printf("The monnth is more than 12, pls stry again\n");
                            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
                        }
                    }
                    
                    else
                    {
                        printf("The date is more than 31, pls stry again\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input     
                    }
                
                }
                
                else
                {
                    printf("pls follow the data format put the '-' between the date\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                }
                
            }
            
            else if(array_len < 10)
            {
                printf("Pls input the right format\n");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            }
            
            else
            {
            printf("Pls input the right format\n");
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
        }   
        
    }
    
        // getting product id input
        while(1)
        {
            int array_len = 0;
            
            //getting user input
            printf("Enter the product id (Axxx): ");
            scanf("%s", &record.product_id);
            
            // getting arr len for valdiation
            arr_len(record.product_id, &array_len);
            
            if(array_len == 4)
            {
                
                // checking the product id inside the product.txt
                char *condition = "False";
                for(int i = 0; i < line; i++)
                {
                    // return the true when it same
                    if(strcmp(record.product_id, product_id[i]) == 0)
                    {
                        condition = "True";
                        while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                        break;
                    }
                    
                    // give error message when the product id not registered
                    else if(i == line - 1 && strcmp(record.product_id, product_id[i]) != 0)
                    {
                        condition = "False";
                        printf("The product haven't addded yet, the product id not in the product.txt\n");
                    }
                }
                
                // break if the condition is true
                if(condition == "True")
                {
                    break;
                }
            }
            
            else
            {
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                printf("Pls enter the right format\n");
            }
        }

        // getting the action from the user
        while(1)
        {
             printf("Enter the action (restock/out/return): ");
             scanf("%s", record.action);

             str_lower(record.action);

             if(strcmp(record.action, "restock") ==  0)
             {
                strcpy(record.action, "Restock");
                break;
             }

             else if(strcmp(record.action, "out") ==  0)
             {
                strcpy(record.action, "Out");
                break;
             }
             
             else if(strcmp(record.action, "return") ==  0)
             {
                strcpy(record.action, "Return");
                break;
             }

             else
             {
                printf("Pls enter the available action only\n");
                while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
             }
             
        }
        // getting the quantity
        integer_valdiation("Enter the quantity: ", &record.quantity);

        // openning the file
        file_record = fopen(record_location,"a");

        // check the file is there or not
        if(file_record == NULL)
        {
            printf("Error openning the file\n");
            return  ;
        }

        // write the record into the text file
        fprintf(file_record, "%s,%s,%s,%d,Active\n", record.date, record.product_id,record.action, record.quantity);

        // close the txt file
        fclose(file_record);

        // asking the user still want to continue or not
        printf("\nDo you still want to contiinue (y/n): ");
        scanf("%c", &record_loop);

    }
}

// view record
void view_record()
{
    // Display view options
    system("cls");
    border(default_border);
    add_space(15);
    printf("View Inventory Options\n");
    border(default_border);
    printf("1. View Active Stock\n");
    printf("2. View Discontinued Stock\n");
    printf("3. View All Stock\n");
    printf("4. Back to Main Menu\n");
    border(default_border);
    
    int view_choice;
    option_validation("Enter your choice: ", &view_choice, 4);
    
    if (view_choice == 4) {
        return;  // Return to main menu
    }

    char record_data[100][100][100];
    int len_record = 0;
    data_record(record_data, &len_record);  
    
    // First count unique products
    int unique_count = 0;
    char unique_product[100][100]; 
    
    // finding the unique value
    for(int j = 1; j < len_record; j++)  // Start from 1 to skip header
    {
        // Skip empty product IDs
        if(strlen(record_data[j][1]) == 0 || record_data[j][1][0] == '\0') 
        {
            continue;
        }

        int is_duplicate = 0;
        int is_discontinued = 0;

        // Check if this product ID is already in our unique list
        for(int k = 0; k < unique_count; k++)
        {
            if(strcmp(record_data[j][1], unique_product[k]) == 0)
            {
                is_duplicate = 1;
                break;
            }
        }

        // Check most recent record for discontinued status
        for(int k = len_record - 1; k >= 1; k--)
        {
            if(strcmp(record_data[k][1], record_data[j][1]) == 0)
            {
                // Clean the status string before comparing
                char clean_status[100];
                strcpy(clean_status, record_data[k][4]);
                clean_string(clean_status);
                
                // Now compare the cleaned string
                if(strcmp(clean_status, "Discontinued") == 0)
                {
                    is_discontinued = 1;
                }
                break;  // Found most recent record, stop checking
            }
        }
        
        // Add to unique list based on view choice
        if(!is_duplicate) {
            if (view_choice == 1 && !is_discontinued) {  // Active stock only
                strcpy(unique_product[unique_count], record_data[j][1]);
                unique_count++;
            }
            else if (view_choice == 2 && is_discontinued) {  // Discontinued stock only
                strcpy(unique_product[unique_count], record_data[j][1]);
                unique_count++;
            }
            else if (view_choice == 3) {  // All stock
                strcpy(unique_product[unique_count], record_data[j][1]);
                unique_count++;
            }
        }
    }
    
    struct inventory_item data[100]; 
    
    // loop through data and count the quantity
    for(int i = 0; i < unique_count; i++)  
    {
        int total = 0;  // Reset total for each product
        strcpy(data[i].product_id, unique_product[i]);
        
        for(int j = 1; j < len_record; j++)
        {
            // check on id the user input then count the quantity
            if(strcmp(record_data[j][1], unique_product[i]) == 0)
            {
                int quantity = atoi(record_data[j][3]);
                if(strcmp(record_data[j][2], "Restock") == 0 || strcmp(record_data[j][2], "Return") == 0)
                {
                    total += quantity;
                }
                else if(strcmp(record_data[j][2], "Out") == 0)
                {
                    total -= quantity;                
                }
            }
        }
        data[i].quantity = total;  // Store the total after calculation
    }

    int len_product = 0;
    char product_data[100][100][100];
    data_product(product_data, &len_product);

    // Search the product id and retrieve the name
    for(int i = 0; i < unique_count; i++)
    {
        for(int j = 0; j < len_product; j++)
        {
            if(strcmp(unique_product[i], product_data[j][0]) == 0)
            {
                strcpy(data[i].product_name, product_data[j][1]);
                break;
            }
        }
    }

    // determining the stock status
    for(int i = 0; i < unique_count; i++)
    {
        // Check if product is discontinued
        int is_discontinued = 0;
        for(int k = len_record - 1; k >= 1; k--)
        {
            if(strcmp(record_data[k][1], data[i].product_id) == 0)
            {
                char clean_status[100];
                strcpy(clean_status, record_data[k][4]);
                clean_string(clean_status);
                if(strcmp(clean_status, "Discontinued") == 0)
                {
                    is_discontinued = 1;
                    strcpy(data[i].stock_status, "Discontinued");
                }
                break;
            }
        }
        
        if (!is_discontinued) {
            if(data[i].quantity > 10)
            {
                strcpy(data[i].stock_status, "In Stock");
            }
            else if(data[i].quantity > 0 && data[i].quantity <= 10)
            {
                strcpy(data[i].stock_status, "Low Stock");
            }
            else
            {
                strcpy(data[i].stock_status, "Empty");
            }
        }
    }

    // Print title based on view choice
    add_space(26);
    switch(view_choice) {
        case 1:
            printf("ACTIVE INVENTORY\n");
            break;
        case 2:
            printf("DISCONTINUED INVENTORY\n");
            break;
        case 3:
            printf("ALL INVENTORY\n");
            break;
    }

    // Check if there are any stocks to display
    if (unique_count == 0) {
        printf("\nNo stock found for the selected view.\n");
        switch(view_choice) {
            case 1:
                printf("There are no active products in the inventory.\n");
                break;
            case 2:
                printf("There are no discontinued products in the inventory.\n");
                break;
            case 3:
                printf("There are no products in the inventory.\n");
                break;
        }
        border(default_border + 2);
        printf("\n");
        return;
    }

    // Print table header
    border(default_border + 2);
    printf("| Product ID | Product Name     | Current Stock | Status     |\n");
    border(default_border + 2);

    // Print table rows
    for(int i = 0; i < unique_count; i++)
    {
        printf("| %-10s | %-16s | %-13d | %-10s |\n", 
               data[i].product_id, 
               data[i].product_name, 
               data[i].quantity, 
               data[i].stock_status);
    }

    // Print table footer
    border(default_border + 2);
    printf("\n");
}

// update stock level
void update_stock()
{
    struct inventory_record record;
    char ch;
    int len_product = 0;
    char product_data[100][100][100];
    char product_id[100][100];
    char record_data[100][100][100];
    int len_record = 0;
    int choice;
    char current_status[50] = "Active";  // Default status
    
    // retrieve product_id from the product.txt
    data_product(product_data, &len_product);
    for(int i=0; i < len_product; i++)
    {
        strncpy(product_id[i], product_data[i][0], 99); 
    }

    // getting product id input
    while(1)
    {
        int array_len = 0;

        // Get current date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(record.date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        // Show options for stock update
        printf("\n");
        printf("Select stock update type:\n");
        border(default_border);
        printf("1. Add Stock (Restock)\n");
        printf("2. Add Stock (Return)\n");
        printf("3. Remove Stock (Out)\n");
        printf("4. Back to Menu\n");
        border(default_border);
        
        option_validation("Enter your choice: ", &choice, 4);

        if (choice == 4) {
            return;  // Return to main menu
        }

        //getting user input
        printf("Enter the product id (Axxx): ");
        scanf("%s", record.product_id);
        
        // getting arr len for validation
        arr_len(record.product_id, &array_len);
            
        if(array_len == 4)
        {
            // First check if product exists in product.txt
            int product_exists = 0;
            for(int i = 0; i < len_product; i++)
            {
                if(strcmp(record.product_id, product_id[i]) == 0)
                {
                    product_exists = 1;
                    break;
                }
            }
            
            if(!product_exists)
            {
                printf("Error: Product ID not found in product database.\n");
                continue;
            }

            // Then check if product has any records
            data_record(record_data, &len_record);
            int has_records = 0;
            
            // Check if product exists in records
            for(int i = 1; i < len_record; i++)  // Start from 1 to skip header
            {
                if(strcmp(record_data[i][1], record.product_id) == 0)
                {
                    has_records = 1;
                    break;
                }
            }

            // For new products (no records), only allow restock
            if(!has_records && choice != 1)
            {
                printf("Error: New products can only be restocked first.\n");
                continue;
            }

            // Check current status of the product
            if(has_records)
            {
                // Check most recent record for status
                for(int k = len_record - 1; k >= 1; k--)
                {
                    if(strcmp(record_data[k][1], record.product_id) == 0)
                    {
                        // Clean the status string before comparing
                        char clean_status[100];
                        strcpy(clean_status, record_data[k][4]);
                        clean_string(clean_status);
                        strcpy(current_status, clean_status);
                        
                        // Only prevent restocking of discontinued products
                        if(strcmp(clean_status, "Discontinued") == 0 && choice == 1)
                        {
                            printf("\nError: Cannot restock discontinued product.\n");
                            return;
                        }
                        break;  // Found most recent record, stop checking
                    }
                }
            }

            // If we get here, all validations passed
            while ((ch = getchar()) != '\n' && ch != EOF); // Clear input buffer
            break;
        }
        
        else
        {
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            printf("Please enter the right format (Axxx)\n");
        }
    }

    // Set action based on choice using if-else
    if(choice == 1)
    {
        strcpy(record.action, "Restock");
    }
    else if(choice == 2)
    {
        strcpy(record.action, "Return");
    }
    else if(choice == 3)
    {
        strcpy(record.action, "Out");
    }

    // Get quantity
    integer_valdiation("Enter the quantity: ", &record.quantity);

    // Open the record file in append mode
    file_record = fopen(record_location, "a");
    if(file_record == NULL)
    {
        printf("Error opening record file\n");
        return;
    }

    // Add new record with all information
    fprintf(file_record, "%s,%s,%s,%d,%s\n", 
            record.date, 
            record.product_id,
            record.action,
            record.quantity,
            current_status);  // Use the current status

    // Close the file
    fclose(file_record);

    system("cls");
    printf("\nStock update recorded successfully!\n");
    printf("----------------------------------------\n");
    printf("Date: %s\n", record.date);
    printf("Product ID: %s\n", record.product_id);
    printf("Action: %s\n", record.action);
    printf("Quantity: %d\n", record.quantity);
    printf("Status: %s\n", current_status);
    printf("----------------------------------------\n");
}

// remove or dfeltge the discontinued item
void remove_discontinued()
{
    struct inventory_record record;
    char ch;
    int len_product = 0;
    char product_data[100][100][100];
    char product_id[100][100];
    char record_data[100][100][100];
    int len_record = 0;
    
    // retrieve product_id from the product.txt
    data_product(product_data, &len_product);
    for(int i=0; i < len_product; i++)
    {
        strncpy(product_id[i], product_data[i][0], 99); 
    }

    // getting product id input
    while(1)
    {
        int array_len = 0;

        // Get current date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(record.date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        //getting user input
        printf("\nEnter the product id to discontinue (Axxx): ");
        scanf("%s", record.product_id);
        
        // getting arr len for validation
        arr_len(record.product_id, &array_len);
            
        if(array_len == 4)
        {
            // checking the product id inside the product.txt
            char *condition = "False";
            for(int i = 0; i < len_product; i++)
            {
                // return the true when it same
                if(strcmp(record.product_id, product_id[i]) == 0)
                {
                    condition = "True";
                    while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
                    break;
                }
                
                // give error message when the product id not registered
                else if(i == len_product - 1 && strcmp(record.product_id, product_id[i]) != 0)
                {
                    condition = "False";
                    printf("The product haven't added yet, the product id not in the product.txt\n");
                }
            }
            
            // break if the condition is true
            if(strcmp(condition, "True") == 0)
            {
                // Check if already discontinued
                data_record(record_data, &len_record);
                
                int is_discontinued = 0;
                // Check most recent record for discontinued status
                for(int k = len_record - 1; k >= 1; k--)
                {
                    if(strcmp(record_data[k][1], record.product_id) == 0)
                    {
                        // Clean the status string before comparing
                        char clean_status[100];
                        strcpy(clean_status, record_data[k][4]);
                        clean_string(clean_status);
                        
                        if(strcmp(clean_status, "Discontinued") == 0)
                        {
                            is_discontinued = 1;
                            printf("\nError: This product is already discontinued.\n");
                            return;
                        }
                        break;  // Found most recent record, stop checking
                    }
                }
                
                if(!is_discontinued)
                {
                    break;
                }
            }
        }
        
        else
        {
            while ((ch = getchar()) != '\n' && ch != EOF);// clearing previous input
            printf("Please enter the right format\n");
        }
    }

    // Open the record file in append mode
    file_record = fopen(record_location, "a");
    if(file_record == NULL)
    {
        printf("Error opening record file\n");
        return;
    }

    // Add new record with Discontinued status
    fprintf(file_record, "%s,%s,Discontinue,0,Discontinued\n", 
            record.date, 
            record.product_id);

    // Close the file
    fclose(file_record);

    printf("\nProduct successfully marked as discontinued!\n");
    printf("----------------------------------------\n");
    printf("Date: %s\n", record.date);
    printf("Product ID: %s\n", record.product_id);
    printf("Status: Discontinued\n");
    printf("----------------------------------------\n");
}


int main()
{
    int choice;
    while(1)
    {
        choice = menu();
        system("cls");
        
        switch(choice)
        {
            case 1:
                add_record();
                break;
                
            case 2:
                update_stock();
                break;
                
            case 3:
                remove_discontinued();
                break;
                
            case 4:
                view_record();
                break;
                
            case 5:
                return 0;
                
            default:
                break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}   
