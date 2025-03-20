#ifndef ACCOUNT_MANAGEMENT_H
#define ACCOUNT_MANAGEMENT_H

#include "user_authentication.h"

#define DEFAULT_MAX_ACCOUNTS 100 // Default initial allocation

// Account Structure
typedef struct {
    char username[MAX_USERNAME_LEN];
    char accountType[20];
    double balance;
} Account;

void initializeAccounts();
void saveAccountsToFile();
void loadAccountsFromFile();
void createAccount(const char* username, const char* accountType, double initialBalance);
void viewAccounts();
void freeAccountMemory();
int findAccountIndex(const char* username, const char* accountType);

extern Account* accounts;
extern int accountCount;
extern int maxAccounts;

#endif // ACCOUNT_MANAGEMENT_H
