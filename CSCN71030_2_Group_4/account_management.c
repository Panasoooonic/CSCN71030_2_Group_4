#define _CRT_SECURE_NO_WARNINGS
#include "account_management.h"

Account* accounts;
int accountCount = 0;

void saveAccountsToFile() {
    FILE* file = fopen("accounts.txt", "w");
    if (!file) {
        printf("Error opening accounts file!\n");
        return;
    }
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%s;%s;%.2f\n", accounts[i].username, accounts[i].accountType, accounts[i].balance);
    }
    fclose(file);
}

void loadAccountsFromFile() {
    FILE* file = fopen("accounts.txt", "r");
    if (!file) return;
    accountCount = 0;
    while (fscanf(file, "%49[^;];%19[^;];%lf\n", accounts[accountCount].username, accounts[accountCount].accountType, &accounts[accountCount].balance) == 3) {
        accountCount++;
    }
    fclose(file);
}

int findAccountIndex(const char* username, const char* accountType) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].accountType, accountType) == 0) {
            return i;
        }
    }
    return -1;
}

void createAccount(const char* username, const char* accountType, double initialBalance) {
    // Check for duplicate account type for the same user
    int duplicate = findAccountIndex(username, accountType);
    if (duplicate != -1) {
        printf("Error: You already have a %s account.\n", accountType);
        return;
    }

    // Check the number of accounts the user already has
    int userAccountCount = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            userAccountCount++;
        }
    }
    if (userAccountCount >= MAX_ACCOUNTS) {
        printf("Error: You cannot have more than %d accounts.\n", MAX_ACCOUNTS);
        return;
    }

    // Allocate memory for a new account
    accounts = realloc(accounts, (accountCount + 1) * sizeof(Account));
    if (!accounts) {
        printf("Memory allocation failed for new account.\n");
        return;
    }

    // Create and store the new account
    strcpy(accounts[accountCount].username, username);
    strcpy(accounts[accountCount].accountType, accountType);
    accounts[accountCount].balance = initialBalance;
    accountCount++;
    saveAccountsToFile();
    printf("%s account created successfully!\n", accountType);
}

void viewAccounts() {
    int found = 0;
    printf("Accounts for %s:\n", currentUser);
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, currentUser) == 0) {
            printf("%s: $%.2f\n", accounts[i].accountType, accounts[i].balance);
            found = 1;
        }
    }
    if (!found) {
        printf("No accounts found.\n");
    }
}

void freeAccountMemory() {
    if (accounts) {
        free(accounts);
        accounts = NULL;
    }
}