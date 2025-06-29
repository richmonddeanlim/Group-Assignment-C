#include "../header/inventory_system.h"


struct category categories[max_categories];  // Array to store category structs
int category_count = 0;            

struct supplier suppliers[max_suppliers];   // Array to store supplier structs
int supplier_count = 0;            


// Reads category information
void load_category() {
    FILE *file = fopen("database/category.txt", "r"); 
    if (file == NULL) {
        printf("database/ file not found. Starting with empty category list.\n");
        category_count = 0;
        return;
    }

    category_count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%199[^\n]", 
            &categories[category_count].id, 
            categories[category_count].name, 
            categories[category_count].description) == 3) {
            category_count++;
        }
    }
    fclose(file); 
}

// Save category information
void save_category() {
    FILE *file = fopen("database/category.txt", "w");  // Open category file for writing
    
    // Write each category to the file, one by one
    for (int i = 0; i < category_count; i++) {
        fprintf(file, "%d,%s,%s\n", categories[i].id, categories[i].name, categories[i].description);
    }
    fclose(file);                            // Close category file
}

// Find the next available category ID
int next_categoryID() {
    int nextID = 1;                     // Start checking from ID 1
    
    while (1) {                        // Find available ID
        int found = 0;                 // Check if current ID is already used
        
        // Check if this ID already exists
        for (int i = 0; i < category_count; i++) {
            if (categories[i].id == nextID) {
                found = 1;            // ID already in use
                break;
            }
        }
        
        if (!found) {                 // ID not found in existing categories, ID available
            return nextID;
        }
        
        nextID++;                     // Next ID
    }
}

// Add a new category
void add_category() {
    // Check if reached the maximum capacity
    if (category_count >= max_suppliers) {
        printf("Maximum number of categories reached! Cannot add more.\n");
        return;
    }
    
    int newID = next_categoryID();                  // Get the next available category ID
    printf("Adding new category with ID: %d\n", newID);  // Imform assigned ID
    
    categories[category_count].id = newID;          // Give this category the new ID number
    
    printf("Enter category name: ");                // Ask the user for the category name
    scanf(" %[^\n]", categories[category_count].name); 
    
    printf("Enter category description: ");         // Ask for a description
    scanf(" %[^\n]", categories[category_count].description); 
    
    category_count++;                               
    save_category();                                 // Save 
    printf("Category added successfully with ID %d!\n", newID);                   
}

// View all category
void view_category() {
    printf("Categories:\n");                       
    
    // Check if there are any categories
    if (category_count == 0) {
        printf("No records found. The category file is empty.\n");
        return;
    }
    
    // Display all categories
    for (int i = 0; i < category_count; i++) {
        printf("%d. %s - %s\n", categories[i].id, categories[i].name, categories[i].description);
    }
}

// Update a category
void update_category() {
    int id, i;                                    
    
    printf("Enter category ID to update: ");             // Ask which category to change
    scanf("%d", &id);                            
    
    // Look for the category with this ID
    for (i = 0; i < category_count; i++) {
        if (categories[i].id == id) {                    // Found
            printf("Enter new name: ");                  // Ask for new information
            scanf(" %[^\n]", categories[i].name);
            printf("Enter new description: ");
            scanf(" %[^\n]", categories[i].description);
            save_category();                             // Save the changes
            printf("Category updated!\n");
            break;                               
        }
    }
    
    if (i == category_count) {
        printf("Category not found!\n");
    }
}

// Delete a category
void delete_category() {
    int id, i;                                    
    
    printf("Enter category ID to delete: ");          // Ask which one to delete
    scanf("%d", &id);
    
    // Look for the category with this ID
    for (i = 0; i < category_count; i++) {
        if (categories[i].id == id) {                 // Found the category to delete
            // Shift all elements after this position one step back to fill the gap
            for (int j = i; j < category_count - 1; j++) {
                categories[j] = categories[j + 1];    // Move the next element to current position
            }
            category_count--;                         // We now have one less category
            save_category();                          // Save the updates
            printf("Category deleted successfully!\n");
            return;                                  // Exit
        }
    }
    
    printf("Category not found!\n");                 // Category not found
}

// Reads supplier information
void load_supplier() {
    FILE *file = fopen("database/supplier.txt", "r");        // Open supplier file for reading
    if (file == NULL) {                             // Error message, file not found
        printf("database/ file not found. Starting with empty supplier list.\n");
        supplier_count = 0;                         // Start with empty list
        return;
    }
    
    supplier_count = 0;                           
    char line[512];
    
    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%99[^,],%49[^,],%99[^\n]", 
            &suppliers[supplier_count].id, 
            suppliers[supplier_count].name, 
            suppliers[supplier_count].contact, 
            suppliers[supplier_count].email) == 4) {
            supplier_count++;                         
        }
    }
    fclose(file);                                  // Close supplier file
}

// Save supplier information
void save_supplier() {
    FILE *file = fopen("database/supplier.txt", "w");       // Open supplier file for writing
    
    // Write each supplier to the file
    for (int i = 0; i < supplier_count; i++) {
        fprintf(file, "%d,%s,%s,%s\n", suppliers[i].id, suppliers[i].name, suppliers[i].contact, suppliers[i].email);
    }
    fclose(file);                                  // Close supplier file
}

// Find the next available supplier ID
int next_supplierID() {
    int nextID = 1;               // Start checking from ID 1
    
    while (1) {                   // Find available ID
        int found = 0;            // Check if current ID is already used
        
        // Check if this ID already exists
        for (int i = 0; i < supplier_count; i++) {
            if (suppliers[i].id == nextID) {
                found = 1;         // ID already in use
                break;
            }
        }
        
        if (!found) {              // ID not found in existing suppliers, ID available
            return nextID;
        }
        
        nextID++;                  // Next ID
    }
}

// Add a new supplier
void add_supplier() {
    // Check if reached the maximum capacity
    if (supplier_count >= max_suppliers) {
        printf("Maximum number of suppliers reached! Cannot add more.\n");
        return;
    }
    
    int newID = next_supplierID();                       // Get the next available supplierID
    printf("Adding new supplier with ID: %d\n", newID);  // Imform assigned ID
    
    suppliers[supplier_count].id = newID;                // Give this supplier the new ID number
    
    printf("Enter supplier name: ");                     // Ask for supplier information
    scanf(" %[^\n]", suppliers[supplier_count].name);
    printf("Enter supplier contact: ");
    scanf(" %[^\n]", suppliers[supplier_count].contact);
    printf("Enter supplier email: ");
    scanf(" %[^\n]", suppliers[supplier_count].email);
    
    supplier_count++;                                
    save_supplier();                                     // Save
    printf("Supplier added successfully with ID %d!\n", newID);
}

// View all supplier
void view_supplier() {
    printf("Suppliers:\n");                         
    
    // Check if there are any suppliers
    if (supplier_count == 0) {
        printf("No records found. The supplier file is empty.\n");
        return;
    }
    
    // Display all suppliers
    for (int i = 0; i < supplier_count; i++) {
        printf("%d. %s, %s, %s\n", suppliers[i].id, suppliers[i].name, suppliers[i].contact, suppliers[i].email);
    }
}

// Update a supplier
void update_supplier() {
    int id, i;                                    
    
    printf("Enter supplier ID to update: ");         // Ask which supplier to change
    scanf("%d", &id);
    
    // Look for the supplier with this ID
    for (i = 0; i < supplier_count; i++) {
        if (suppliers[i].id == id) {                 // Found
            printf("Enter new name: ");              // Ask for new information
            scanf(" %[^\n]", suppliers[i].name);
            printf("Enter new contact: ");
            scanf(" %[^\n]", suppliers[i].contact);
            printf("Enter new email: ");
            scanf(" %[^\n]", suppliers[i].email);
            save_supplier();                         // Save the changes
            printf("Supplier updated!\n");
            break;                                
        }
    }
    
    if (i == supplier_count) {
        printf("Supplier not found!\n");
    }
}

// Delete a supplier
void delete_supplier() {
    int id, i;                                    
    
    printf("Enter supplier ID to delete: ");         // Ask which one to delete
    scanf("%d", &id);
    
    // Look for the supplier with this ID
    for (i = 0; i < supplier_count; i++) {
        if (suppliers[i].id == id) {                  // Found the supplier to delete
            // Shift all elements after this position one step back to fill the gap
            for (int j = i; j < supplier_count - 1; j++) {
                suppliers[j] = suppliers[j + 1];      // Move the next element to current position
            }
            supplier_count--;                         // We now have one less supplier
            save_supplier();                          // Save the updates
            printf("Supplier deleted successfully!\n");
            return;                                   // Exit
        }
    }
    
    printf("Supplier not found!\n");                 // Supplier not found
}

// Category menu
void category_menu() {
    int choice;                                    
    int result;
    
    printf("\nCategory Menu:\n1. Add\n2. View\n3. Update\n4. Delete\n0. Back\nChoice: ");
    result = scanf("%d", &choice);
    
    // Clear input buffer if scanf failed
    if (result != 1) {
        printf("Invalid choice! Please try again.\n");
        while (getchar() != '\n'); // Clear input buffer
        category_menu();
        return;
    }
    
    switch (choice) {
        case 1:
            add_category();           // 1 = Add a new category
            category_menu();          
            break;
        case 2:
            view_category();         // 2 = Show all categories
            category_menu();          
            break;
        case 3:
            update_category();        // 3 = Change a category
            category_menu();          
            break;
        case 4:
            delete_category();        // 4 = Delete a category
            category_menu();          
            break;
        case 0:
            while (getchar() != '\n'); // Clear input buffer before returning
            return;                  // Go back to main menu
        default:
            printf("Invalid choice! Please try again.\n");
            category_menu();          
            break;
    }
}

// Supplier menu
void supplier_menu() {
    int choice;                                   
    int result;
    
    printf("\nSupplier Menu:\n1. Add\n2. View\n3. Update\n4. Delete\n0. Back\nChoice: ");
    result = scanf("%d", &choice);
    
    // Clear input buffer if scanf failed
    if (result != 1) {
        printf("Invalid choice! Please try again.\n");
        while (getchar() != '\n'); // Clear input buffer
        supplier_menu();
        return;
    }
    
    switch (choice) {
        case 1:
            add_supplier();          // 1 = Add a new supplier
            supplier_menu();         
            break;
        case 2:
            view_supplier();        // 2 = Show all suppliers
            supplier_menu();         
            break;
        case 3:
            update_supplier();       // 3 = Change a supplier
            supplier_menu();         
            break;
        case 4:
            delete_supplier();       // 4 = Delete a supplier
            supplier_menu();         
            break;
        case 0:
            while (getchar() != '\n'); // Clear input buffer before returning
            return;                  // Go back to main menu
        default:
            printf("Invalid choice! Please try again.\n");
            supplier_menu();         
            break;
    }
}
