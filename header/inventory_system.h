#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE_LENGTH 256
#define MAX_USERS 100

// Data Structures
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} User;

typedef struct {
    char name[100];
    float price;
    int quantity;
    char category[50];
    char supplier[50];
} Product;

// For Global Variables Declaration
extern User users[MAX_USERS];
extern int userCount;
extern User currentUser;

// Functions
void loadUsers();
int login();
void changePassword();
void addUser();
void deleteUser();

void displayMainMenu();
void role1Menu();
void role2Menu();
void role3Menu();
void role4Menu();
void adminMenu();

void clearScreen();

#endif