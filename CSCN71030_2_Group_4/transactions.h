#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "account_management.h"

#define MAX_TRANSACTIONS 100
#define MAX_TRANSACTION_TYPE_LEN 20
#define MAX_USERS 100

// Transaction Structure
typedef struct {
    char username[MAX_USERNAME_LEN];
    char accountType[MAX_ACCOUNT_TYPE_LEN];
    char transactionType[MAX_TRANSACTION_TYPE_LEN]; // Deposit, Withdraw, Transfer
    double amount;
} Transaction;

// Multi-dimensional array for transaction logs
extern double transactionLog[MAX_USERS][MAX_TRANSACTIONS];

// Function Prototypes
void saveTransactionsToFile();
void loadTransactionsFromFile();
void recordTransaction(const char* username, const char* accountType, const char* transactionType, double amount);
void deposit(const char* accountType, double amount);
void withdraw(const char* accountType, double amount);
void transfer(const char* sender, const char* senderAccount, const char* receiver, const char* receiverAccount, double amount);
void viewTransactions();
void logTransaction(int userId, int transactionId, double amount);
void freeTransactionMemory();

// Extern Variables
extern Transaction** transactions;
extern int* transactionCount;

#endif // TRANSACTIONS_H