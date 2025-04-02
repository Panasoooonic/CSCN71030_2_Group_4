// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_NAME_LEN 50
#define MAX_TRANSACTIONS 100
#define MAX_TRANSACTION_TYPE_LEN 20
#define MAX_USERS 100
#define MAX_ACCOUNT_TYPE_LEN 20

typedef struct
{
    char name[50];
    int chanceOfSuccess;
    int Trend;
} Market;

typedef struct {
    char username[3];
    char accountType[20];
    double balance;
} Account;

typedef struct {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int status;          // 1 for active, 0 for locked
    int failedAttempts;  // Number of consecutive failed login attempts
} User;




// Transaction Structure
typedef struct {
    char username[MAX_USERNAME_LEN];
    char accountType[MAX_ACCOUNT_TYPE_LEN];
    char transactionType[MAX_TRANSACTION_TYPE_LEN]; // Deposit, Withdraw, Transfer
    double amount;
} Transaction;

extern char currentUser[50];
// add headers that you want to pre-compile here

#endif //PCH_H
