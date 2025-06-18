const char *menutext = "\n--- User and Transaction Management System ---\n\n";
const char *customerFile = "customer_credentials.txt";

#define MAX_CUSTOMERS 100

void user();
void transactions();
void getValidInput();
void addUser();
void deleteUser();
void loadCustomerCredentials();
void updateUser();
bool duplicateChecker();

extern int customerCount;

typedef struct {
    char username[50];
    char password[50];
} Customer;