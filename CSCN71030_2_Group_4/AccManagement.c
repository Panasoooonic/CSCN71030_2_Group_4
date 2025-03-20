// main.c file 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User Authentication.h"
#include "AccManagement.h"

#define MAX_ACCOUNTS 3
#define FILE_NAME "accounts.txt"


int validateAccountLimits(const char* customerId) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Unable to open %s for reading.\n", FILE_NAME);
        return 1; // Allow as file is empty
    }

    AccountTypeInfo acc;
    int accountCount = 0;

    while (fscanf(file, "%49s %19s %lf", acc.customerId, acc.accountType, &acc.balance) != EOF) {
        if (strcmp(acc.customerId, customerId) == 0) {
            accountCount++;
        }
    }

    fclose(file);
    return accountCount < MAX_ACCOUNTS ? 1 : 0; // Return 1 if below limit, 0 otherwise
}

int checkDuplicateAccount(const char* customerId, const char* accountType) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Unable to open %s for reading.\n", FILE_NAME);
        return 1; // Allow as file is empty
    }

    AccountTypeInfo acc;
    while (fscanf(file, "%49s %19s %lf", acc.customerId, acc.accountType, &acc.balance) != EOF) {
        if (strcmp(acc.customerId, customerId) == 0 && strcmp(acc.accountType, accountType) == 0) {
            fclose(file);
            return 0; // Duplicate found
        }
    }

    fclose(file);
    return 1; // No duplicate
}

void getAccountBalances(const char* customerId) {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Unable to open %s for reading.\n", FILE_NAME);
        return;
    }

    AccountTypeInfo acc;
    int found = 0;

    printf("Account Details for Customer ID: %s\n", customerId);
    while (fscanf(file, "%49s %19s %lf", acc.customerId, acc.accountType, &acc.balance) != EOF) {
        if (strcmp(acc.customerId, customerId) == 0) {
            printf("Account Type: %s | Balance: %.2f\n", acc.accountType, acc.balance);
            found = 1;
        }
    }

    if (!found) {
        printf("No accounts found for Customer ID: %s\n", customerId);
    }

    fclose(file);
}

int saveAccountsToFile(AccountTypeInfo* account) {
    FILE* file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error: Unable to open %s for writing.\n", FILE_NAME);
        return 0;
    }

    fprintf(file, "%s %s %.2f\n", account->customerId, account->accountType, account->balance);
    fclose(file);

    return 1;
}

void createNewAccount(const char* customerId) {
    if (!validateAccountLimits(customerId)) {
        printf("Error: Maximum account limit reached.\n");
        return;
    }

    char accountType[20];
    double initialBalance;

    printf("Enter Account Type (Savings/Chequing/Investment): ");
    scanf("%19s", accountType);

    if (!checkDuplicateAccount(customerId, accountType)) {
        printf("Error: Duplicate account type not allowed.\n");
        return;
    }

    printf("Enter Initial Balance: ");
    scanf("%lf", &initialBalance);

    AccountTypeInfo newAccount;
    strcpy(newAccount.customerId, customerId);
    strcpy(newAccount.accountType, accountType);
    newAccount.balance = initialBalance;

    if (saveAccountsToFile(&newAccount)) {
        printf("Account successfully created!\n");
    }
    else {
        printf("Error: Unable to save account details.\n");
    }
}

int logicSuccess() {
    int choice;
    while (1) {
        printf("\n1. Create Account\n2. View Balances\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        char customerId[50];
        switch (choice) {
        case 1:
            printf("Enter Customer ID: ");
            scanf("%49s", customerId);
            createNewAccount(customerId);
            break;
        case 2:
            printf("Enter Customer ID: ");
            scanf("%49s", customerId);
            getAccountBalances(customerId);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
