#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_authentication.h"
#include "account_management.h"
#include "transactions.h"

// Function to clear input buffer
static void clearInputBuffer() {
    while (getchar() != '\n'); // Flush input buffer
}

// Function to safely get user choice
static int getUserChoice() {
    int choice;
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return -1; // Invalid input
    }
    clearInputBuffer(); // Ensure buffer is flushed
    return choice;
}

int main() {
    //// Allow setting max users from command line argument
    //if (argc > 1) {
    //    maxUsers = atoi(argv[1]);
    //    if (maxUsers <= 0) {
    //        printf("Invalid number of max users. Defaulting to 100.\n");
    //        maxUsers = 100;
    //    }
    //}

    int maxUsers = 100;

    // Initialize memory and load data
    initializeUsers();
    initializeAccounts();
    initializeTransactions();

    loadUsersFromFile();
    loadAccountsFromFile();
    loadTransactionsFromFile();

    int choice;
    while (1) {
        printf("\n--- Banking System Menu ---\n");
        printf("1. Register\n2. Login\n3. Exit\nEnter choice: ");
        choice = getUserChoice();

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
            while (strlen(currentUser) > 0) { // While user is logged in
                printf("\n--- Welcome, %s ---\n", currentUser);
                printf("1. View Accounts\n2. Make an Account\n3. Make a Transaction\n4. View Transactions\n5. Logout\nEnter choice: ");
                choice = getUserChoice();

                if (choice == 1) { // View Accounts
                    viewAccounts();
                }
                else if (choice == 2) { // Make an Account (Savings, Checking, Investing)
                    char accountType[20];
                    double initialBalance;

                    printf("\nSelect Account Type:\n1. Savings\n2. Checking\n3. Investing\nEnter choice: ");
                    int accChoice = getUserChoice();

                    if (accChoice == 1) {
                        strcpy(accountType, "Savings");
                    }
                    else if (accChoice == 2) {
                        strcpy(accountType, "Checking");
                    }
                    else if (accChoice == 3) {
                        strcpy(accountType, "Investing");
                    }
                    else {
                        printf("Invalid choice! Try again.\n");
                        continue;
                    }

                    // Check for duplicate account
                    if (findAccountIndex(currentUser, accountType) != -1) {
                        printf("Error: You already have a %s account.\n", accountType);
                        continue;
                    }

                    // Get initial balance
                    printf("Enter Initial Deposit Amount: ");
                    if (scanf("%lf", &initialBalance) != 1 || initialBalance < 0) {
                        printf("Invalid deposit amount. Try again.\n");
                        clearInputBuffer();
                        continue;
                    }

                    createAccount(currentUser, accountType, initialBalance);
                }
                else if (choice == 3) { // Make a Transaction
                    printf("\n1. Deposit\n2. Withdraw\n3. Transfer\nEnter choice: ");
                    choice = getUserChoice();

                    char accountType[20], receiver[50], receiverAccount[20];
                    double amount;

                    if (choice == 1) { // Deposit
                        printf("Enter Account Type: ");
                        fgets(accountType, sizeof(accountType), stdin);
                        accountType[strcspn(accountType, "\n")] = 0; // Remove newline

                        printf("Enter Amount: ");
                        if (scanf("%lf", &amount) != 1) {
                            printf("Invalid input for amount.\n");
                            clearInputBuffer();
                            continue;
                        }
                        deposit(accountType, amount);
                    }
                    else if (choice == 2) { // Withdraw
                        printf("Enter Account Type: ");
                        fgets(accountType, sizeof(accountType), stdin);
                        accountType[strcspn(accountType, "\n")] = 0;

                        printf("Enter Amount: ");
                        if (scanf("%lf", &amount) != 1) {
                            printf("Invalid input for amount.\n");
                            clearInputBuffer();
                            continue;
                        }
                        withdraw(accountType, amount);
                    }
                    else if (choice == 3) { // Transfer
                        printf("Enter Sender Account: ");
                        fgets(accountType, sizeof(accountType), stdin);
                        accountType[strcspn(accountType, "\n")] = 0;

                        printf("Enter Receiver Username: ");
                        fgets(receiver, sizeof(receiver), stdin);
                        receiver[strcspn(receiver, "\n")] = 0;

                        printf("Enter Receiver Account: ");
                        fgets(receiverAccount, sizeof(receiverAccount), stdin);
                        receiverAccount[strcspn(receiverAccount, "\n")] = 0;

                        printf("Enter Amount: ");
                        if (scanf("%lf", &amount) != 1) {
                            printf("Invalid input for amount.\n");
                            clearInputBuffer();
                            continue;
                        }
                        transfer(currentUser, accountType, receiver, receiverAccount, amount);
                    }
                    else {
                        printf("Invalid choice! Try again.\n");
                    }
                }
                else if (choice == 4) { // View Transactions
                    viewTransactions();
                }
                else if (choice == 5) { // Logout
                    strcpy(currentUser, "");
                    printf("Logged out successfully.\n");
                }
                else {
                    printf("Invalid choice! Try again.\n");
                }
            }
        }
        else if (choice == 3) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    // Free allocated memory before exiting
    freeUserMemory();
    freeAccountMemory();
    freeTransactionMemory();

    return 0;
}