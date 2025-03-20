#define _CRT_SECURE_NO_WARNINGS
#include "transactions.h"

Transaction* transactions = NULL;
int transactionCount = 0;
int maxTransactions = DEFAULT_MAX_TRANSACTIONS;

// Initialize memory for transactions
void initializeTransactions() {
    transactions = (Transaction*)malloc(maxTransactions * sizeof(Transaction));
    if (!transactions) {
        printf("Memory allocation failed for transactions.\n");
        exit(EXIT_FAILURE);
    }
}

// Free allocated memory for transactions
void freeTransactionMemory() {
    free(transactions);
}

// Save transactions to file
void saveTransactionsToFile() {
    FILE* file = fopen("transactions.txt", "w");
    if (!file) {
        printf("Error opening transactions file for writing!\n");
        return;
    }
    for (int i = 0; i < transactionCount; i++) {
        fprintf(file, "%s;%s;%s;%.2f\n",
            transactions[i].username, transactions[i].accountType,
            transactions[i].transactionType, transactions[i].amount);
    }
    fclose(file);
}

// Load transactions from file
void loadTransactionsFromFile() {
    FILE* file = fopen("transactions.txt", "r");
    if (!file) {
        printf("Transactions file not found. Initializing empty transactions list.\n");
        return;
    }

    transactionCount = 0;
    while (transactionCount < maxTransactions &&
        fscanf(file, "%49[^;];%19[^;];%19[^;];%lf\n",
            transactions[transactionCount].username,
            transactions[transactionCount].accountType,
            transactions[transactionCount].transactionType,
            &transactions[transactionCount].amount) == 4) {
        transactionCount++;

        // Expand memory if needed
        if (transactionCount >= maxTransactions) {
            maxTransactions *= 2;
            transactions = (Transaction*)realloc(transactions, maxTransactions * sizeof(Transaction));
            if (!transactions) {
                printf("Memory allocation failed while expanding transactions storage.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);
}

// Record a transaction
void recordTransaction(const char* username, const char* accountType, const char* transactionType, double amount) {
    if (transactionCount >= maxTransactions) {
        maxTransactions *= 2;
        Transaction* temp = (Transaction*)realloc(transactions, maxTransactions * sizeof(Transaction));
        if (!temp) {
            printf("Memory reallocation failed for transactions.\n");
            return;
        }
        transactions = temp;
    }

    Transaction* t = &transactions[transactionCount++];
    strcpy(t->username, username);
    strcpy(t->accountType, accountType);
    strcpy(t->transactionType, transactionType);
    t->amount = amount;

    saveTransactionsToFile();
}

// Deposit money into an account
void deposit(const char* accountType, double amount) {
    if (amount <= 0) {
        printf("Error: Deposit amount must be greater than zero.\n");
        return;
    }

    int accountIndex = findAccountIndex(currentUser, accountType);
    if (accountIndex == -1) {
        printf("Error: Account not found.\n");
        return;
    }

    accounts[accountIndex].balance += amount;
    saveAccountsToFile();
    recordTransaction(currentUser, accountType, "Deposit", amount);
    printf("Deposited $%.2f into %s account successfully!\n", amount, accountType);
}

// Withdraw money from an account
void withdraw(const char* accountType, double amount) {
    if (amount <= 0) {
        printf("Error: Withdrawal amount must be greater than zero.\n");
        return;
    }

    int accountIndex = findAccountIndex(currentUser, accountType);
    if (accountIndex == -1) {
        printf("Error: Account not found.\n");
        return;
    }

    if (accounts[accountIndex].balance < amount) {
        printf("Error: Insufficient funds.\n");
        return;
    }

    accounts[accountIndex].balance -= amount;
    saveAccountsToFile();
    recordTransaction(currentUser, accountType, "Withdraw", amount);
    printf("Withdrew $%.2f from %s account successfully!\n", amount, accountType);
}

// Transfer money between users
void transfer(const char* sender, const char* senderAccount, const char* receiver, const char* receiverAccount, double amount) {
    if (amount <= 0) {
        printf("Error: Transfer amount must be greater than zero.\n");
        return;
    }

    int senderIndex = findAccountIndex(sender, senderAccount);
    int receiverIndex = findAccountIndex(receiver, receiverAccount);

    if (senderIndex == -1 || receiverIndex == -1) {
        printf("Error: Invalid sender or receiver account.\n");
        return;
    }

    if (accounts[senderIndex].balance < amount) {
        printf("Error: Insufficient funds.\n");
        return;
    }

    accounts[senderIndex].balance -= amount;
    accounts[receiverIndex].balance += amount;
    saveAccountsToFile();

    recordTransaction(sender, senderAccount, "Transfer Out", amount);
    recordTransaction(receiver, receiverAccount, "Transfer In", amount);

    printf("Transferred $%.2f from %s's %s account to %s's %s account successfully!\n",
        amount, sender, senderAccount, receiver, receiverAccount);
}

// View transactions for the logged-in user
void viewTransactions() {
    if (transactionCount == 0) {
        printf("No transactions found.\n");
        return;
    }

    printf("\nTransactions for %s:\n", currentUser);
    int found = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].username, currentUser) == 0) {
            printf("%s - %s: $%.2f\n", transactions[i].transactionType, transactions[i].accountType, transactions[i].amount);
            found = 1;
        }
    }
    if (!found) {
        printf("No transactions found for %s.\n", currentUser);
    }
}
