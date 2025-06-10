#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define Max_users 100

// Data Structures
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} Staff;

// For Global Variables Declaration
extern Staff users[Max_users];
extern int userCount;
extern Staff currentUser;

// Functions
void loadUsers();
int login();
void changePassword();
void addUser();
void deleteUser();
void getValidInput(char* prompt, char* buffer, int maxLength);

void displayMainMenu();
void role1Menu(int isAdmin);
void role2Menu(int isAdmin);
void role3Menu(int isAdmin);
void role4Menu(int isAdmin);
void adminMenu();

void clearScreen();
void clearInputBuffer();

#endif