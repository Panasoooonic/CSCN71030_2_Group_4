#define _CRT_SECURE_NO_WARNINGS
#include "account_management.h"

Account* accounts = NULL;
int accountCount = 0;
int maxAccounts = DEFAULT_MAX_ACCOUNTS;

// Initialize memory for accounts
void initializeAccounts() {
    accounts = (Account*)malloc(maxAccounts * sizeof(Account));
    if (!accounts) {
        printf("Memory allocation failed for accounts.\n");
        exit(EXIT_FAILURE);
    }
}

// Free allocated memory for accounts
void freeAccountMemory() {
    free(accounts);
}

// Save accounts to file
void saveAccountsToFile() {
    FILE* file = fopen("accounts.txt", "w");
    if (!file) {
        printf("Error opening accounts file for writing!\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%s;%s;%.2f\n",
            accounts[i].username, accounts[i].accountType, accounts[i].balance);
    }
    fclose(file);
}

// Load accounts from file
void loadAccountsFromFile() {
    FILE* file = fopen("accounts.txt", "r");
    if (!file) {
        printf("Accounts file not found. Initializing empty account list.\n");
        return;
    }

    accountCount = 0;
    while (accountCount < maxAccounts &&
        fscanf(file, "%49[^;];%19[^;];%lf\n",
            accounts[accountCount].username,
            accounts[accountCount].accountType,
            &accounts[accountCount].balance) == 3) {
        accountCount++;

        // Expand memory if needed
        if (accountCount >= maxAccounts) {
            maxAccounts *= 2;
            accounts = (Account*)realloc(accounts, maxAccounts * sizeof(Account));
            if (!accounts) {
                printf("Memory allocation failed while expanding accounts storage.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
}

// Find the index of an account for a user
int findAccountIndex(const char* username, const char* accountType) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].accountType, accountType) == 0) {
            return i;
        }
    }
    return -1; // Account not found
}

// Create an account
void createAccount(const char* username, const char* accountType, double initialBalance) {
    // Validate initial balance
    if (initialBalance < 0) {
        printf("Error: Initial balance cannot be negative.\n");
        return;
    }

    // Ensure the user does not have more than 3 accounts
    int userAccountCount = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            userAccountCount++;
            if (strcmp(accounts[i].accountType, accountType) == 0) {
                printf("Error: You already have a %s account.\n", accountType);
                return;
            }
        }
    }
    if (userAccountCount >= 3) {
        printf("Error: You cannot have more than 3 accounts.\n");
        return;
    }

    // Expand memory if needed
    if (accountCount >= maxAccounts) {
        maxAccounts *= 2;
        accounts = (Account*)realloc(accounts, maxAccounts * sizeof(Account));
        if (!accounts) {
            printf("Memory allocation failed. Cannot create more accounts.\n");
            return;
        }
    }

    // Create the account
    strcpy(accounts[accountCount].username, username);
    strcpy(accounts[accountCount].accountType, accountType);
    accounts[accountCount].balance = initialBalance;
    accountCount++;
    saveAccountsToFile();
    printf("%s account created successfully!\n", accountType);
}

// View all accounts for the logged-in user
void viewAccounts() {
    if (strlen(currentUser) == 0) {
        printf("Error: You must be logged in to view accounts.\n");
        return;
    }

    int found = 0;
    printf("Accounts for %s:\n", currentUser);
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, currentUser) == 0) {
            printf("%s: $%.2f\n", accounts[i].accountType, accounts[i].balance);
            found = 1;
        }
    }
    if (!found) {
        printf("No accounts found for %s.\n", currentUser);
    }
}
