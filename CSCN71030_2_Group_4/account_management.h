#ifndef ACCOUNT_MANAGEMENT_H
#define ACCOUNT_MANAGEMENT_H

#include "user_authentication.h"

#define MAX_ACCOUNTS 3
#define MAX_ACCOUNT_TYPE_LEN 20

// Account Structure
typedef struct {
    char username[MAX_USERNAME_LEN];
    char accountType[MAX_ACCOUNT_TYPE_LEN];
    double balance;
} Account;

// Function Prototypes
void saveAccountsToFile();
void loadAccountsFromFile();
void createAccount(const char* username, const char* accountType, double initialBalance);
int findAccountIndex(const char* username, const char* accountType);
void viewAccounts();
void freeAccountMemory();

// Extern Variables
extern Account* accounts;
extern int accountCount;

#endif // ACCOUNT_MANAGEMENT_H