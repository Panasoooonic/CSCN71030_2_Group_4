#pragma once

typedef struct {
    char customerId[50];
    char accountType[20]; // e.g., Savings, Chequing, Investment
    double balance;
} AccountTypeInfo;

int validateAccountLimits(const char* customerId);
int checkDuplicateAccount(const char* customerId, const char* accountType);
void getAccountBalances(const char* customerId);
int saveAccountsToFile(AccountTypeInfo* account);
int logicSuccess();
