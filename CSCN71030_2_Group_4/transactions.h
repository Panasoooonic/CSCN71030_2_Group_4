#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "account_management.h"

#define DEFAULT_MAX_TRANSACTIONS 100

// Transaction Structure
typedef struct {
    char username[MAX_USERNAME_LEN];
    char accountType[20];
    char transactionType[20]; // Deposit, Withdraw, Transfer
    double amount;
} Transaction;

void initializeTransactions();
void saveTransactionsToFile();
void loadTransactionsFromFile();
void recordTransaction(const char* username, const char* accountType, const char* transactionType, double amount);
void deposit(const char* accountType, double amount);
void withdraw(const char* accountType, double amount);
void transfer(const char* sender, const char* senderAccount, const char* receiver, const char* receiverAccount, double amount);
void viewTransactions();
void freeTransactionMemory();

extern Transaction* transactions;
extern int transactionCount;
extern int maxTransactions;

#endif // TRANSACTIONS_H
