#define _CRT_SECURE_NO_WARNINGS
#include "transactions.h"

Transaction** transactions;
int* transactionCount;
double transactionLog[MAX_USERS][MAX_TRANSACTIONS] = { 0 };

// Initialize the transaction data structure
void initializeTransactions() {
    transactions = (Transaction**)malloc(MAX_USERS * sizeof(Transaction*));
    transactionCount = (int*)malloc(MAX_USERS * sizeof(int));
    for (int i = 0; i < MAX_USERS; i++) {
        transactions[i] = (Transaction*)malloc(MAX_TRANSACTIONS * sizeof(Transaction));
        transactionCount[i] = 0;
    }
}

// Log transaction amounts in the multi-dimensional array
void logTransaction(int userId, int transactionId, double amount) {
    if (userId < MAX_USERS && transactionId < MAX_TRANSACTIONS) {
        transactionLog[userId][transactionId] = amount;
        // Removed the unnecessary print statement
    }
}

// Save transactions to file
void saveTransactionsToFile() {
    FILE* file = fopen("transactions.txt", "w");
    if (!file) {
        printf("Error opening transactions file!\n");
        return;
    }
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < transactionCount[i]; j++) {
            fprintf(file, "%s;%s;%s;%.2f\n",
                transactions[i][j].username,
                transactions[i][j].accountType,
                transactions[i][j].transactionType,
                transactions[i][j].amount);
        }
    }
    fclose(file);
}

// Load transactions from file
void loadTransactionsFromFile() {
    FILE* file = fopen("transactions.txt", "r");
    if (!file) return;
    for (int i = 0; i < MAX_USERS; i++) transactionCount[i] = 0;

    char username[MAX_USERNAME_LEN], accountType[20], transactionType[20];
    double amount;
    int userId = 0;

    while (fscanf(file, "%49[^;];%19[^;];%19[^;];%lf\n",
        username, accountType, transactionType, &amount) == 4) {
        int userIndex = findAccountIndex(username, accountType);
        if (userIndex == -1 || transactionCount[userId] >= MAX_TRANSACTIONS) continue;
        Transaction* t = &transactions[userId][transactionCount[userId]++];
        strcpy(t->username, username);
        strcpy(t->accountType, accountType);
        strcpy(t->transactionType, transactionType);
        t->amount = amount;
        logTransaction(userId, transactionCount[userId], amount);
    }
    fclose(file);
}

// Record a transaction
void recordTransaction(const char* username, const char* accountType, const char* transactionType, double amount) {
    int userIndex = findAccountIndex(username, accountType);
    if (userIndex == -1 || transactionCount[userIndex] >= MAX_TRANSACTIONS) return;

    Transaction* t = &transactions[userIndex][transactionCount[userIndex]++];
    strcpy(t->username, username);
    strcpy(t->accountType, accountType);
    strcpy(t->transactionType, transactionType);
    t->amount = amount;

    logTransaction(userIndex, transactionCount[userIndex], amount);
    saveTransactionsToFile();
}

// Deposit function
void deposit(const char* accountType, double amount) {
    int accountIndex = findAccountIndex(currentUser, accountType);
    if (accountIndex == -1) {
        printf("Account not found!\n");
        return;
    }
    accounts[accountIndex].balance += amount;
    saveAccountsToFile();
    recordTransaction(currentUser, accountType, "Deposit", amount);
    printf("Deposit successful! New balance: %.2f\n", accounts[accountIndex].balance);
}

// Withdraw function
void withdraw(const char* accountType, double amount) {
    int accountIndex = findAccountIndex(currentUser, accountType);
    if (accountIndex == -1) {
        printf("Account not found!\n");
        return;
    }
    if (accounts[accountIndex].balance < amount) {
        printf("Insufficient funds!\n");
        return;
    }
    accounts[accountIndex].balance -= amount;
    saveAccountsToFile();
    recordTransaction(currentUser, accountType, "Withdraw", amount);
    printf("Withdrawal successful! New balance: %.2f\n", accounts[accountIndex].balance);
}

// Transfer function
void transfer(const char* sender, const char* senderAccount, const char* receiver, const char* receiverAccount, double amount) {
    int senderIndex = findAccountIndex(sender, senderAccount);
    int receiverIndex = findAccountIndex(receiver, receiverAccount);
    if (senderIndex == -1 || receiverIndex == -1) {
        printf("Error: Invalid account information.\n");
        return;
    }
    if (accounts[senderIndex].balance < amount) {
        printf("Insufficient funds!\n");
        return;
    }

    accounts[senderIndex].balance -= amount;
    accounts[receiverIndex].balance += amount;
    saveAccountsToFile();

    recordTransaction(sender, senderAccount, "Transfer Out", amount);
    recordTransaction(receiver, receiverAccount, "Transfer In", amount);
    printf("Transfer successful! %.2f transferred from %s to %s.\n", amount, senderAccount, receiverAccount);
}

// View transactions
// View transactions
void viewTransactions() {
    int found = 0;
    printf("\nTransactions for %s:\n", currentUser);
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < transactionCount[i]; j++) {
            if (strcmp(transactions[i][j].username, currentUser) == 0) {
                Transaction* t = &transactions[i][j];
                printf("%s - %s: $%.2f\n", t->transactionType, t->accountType, t->amount);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("No transactions found for %s.\n", currentUser);
    }
}

// Free dynamically allocated memory for transactions
void freeTransactionMemory() {
    for (int i = 0; i < MAX_USERS; i++) {
        if (transactions[i]) {
            free(transactions[i]);
            transactions[i] = NULL;
        }
    }
    free(transactions);
    free(transactionCount);
}