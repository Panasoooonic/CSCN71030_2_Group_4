#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "user_authentication.h"
#include "account_management.h"
#include "transactions.h"
#include "Invest.h"


int main(int argc, char* argv[]) {
    // Handle command-line argument for maximum users
    if (argc > 1) {
        maxUsers = atoi(argv[1]);
        if (maxUsers <= 0) {
            printf("Invalid number of max users. Defaulting to 100.\n");
            maxUsers = 100;
        }
    }
    // Initialize user and account data
    users = (User*)malloc(maxUsers * sizeof(User));
    accounts = (Account*)malloc(100 * MAX_ACCOUNTS * sizeof(Account));
    initializeTransactions();

    if (!accounts) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Load data from files
    loadUsersFromFile();
    loadAccountsFromFile();
    loadTransactionsFromFile();


    int choice;
    while (1) {
        printf("\n--- Banking System ---\n");
        printf("1. Register\n2. Login\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
            while (strlen(currentUser) > 0) {
                printf("\n--- Welcome, %s ---\n", currentUser);
                printf("1. View Accounts\n2. Make an Account\n3. Make a Transaction\n4. View Transactions\n5. Logout\nEnter choice: ");
                scanf("%d", &choice);

                if (choice == 1) {
                    viewAccounts();
                }
                else if (choice == 2) {
                    char accountType[20];
                    double initialBalance;
                    printf("Enter Account Type (Savings/Checking/Investing): ");
                    scanf("%s", accountType);
                    printf("Enter Initial Balance: ");
                    scanf("%lf", &initialBalance);
                    createAccount(currentUser, accountType, initialBalance);
                }
                else if (choice == 3) {
                    printf("1. Deposit\n2. Withdraw\n3. Transfer\n4. Invest\nEnter choice: ");
                    scanf("%d", &choice);

                    char accountType[20], receiver[50], receiverAccount[20];
                    double amount;

                    if (choice == 1) {
                        printf("Enter Account Type: ");
                        scanf("%s", accountType);
                        printf("Enter Amount: ");
                        scanf("%lf", &amount);
                        deposit(accountType, amount);
                    }
                    else if (choice == 2) {
                        printf("Enter Account Type: ");
                        scanf("%s", accountType);
                        printf("Enter Amount: ");
                        scanf("%lf", &amount);
                        withdraw(accountType, amount);
                    }
                    else if (choice == 3) {
                        printf("Enter Sender Account: ");
                        scanf("%s", accountType);
                        printf("Enter Receiver Username: ");
                        scanf("%s", receiver);
                        printf("Enter Receiver Account: ");
                        scanf("%s", receiverAccount);
                        printf("Enter Amount: ");
                        scanf("%lf", &amount);
                        transfer(currentUser, accountType, receiver, receiverAccount, amount);
                    }
                    else if (choice == 4)
                    {
                        Invest(argc);
                    }
                    else {
                        printf("Invalid transaction choice.\n");
                    }
                }
                else if (choice == 4) {
                    viewTransactions();
                }
                else if (choice == 5) {
                    strcpy(currentUser, "");
                    printf("Logged out successfully.\n");
                    break;
                }
                else {
                    printf("Invalid choice. Try again.\n");
                }
            }
        }
        else if (choice == 3) {
            printf("Exiting the system. Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    // Clean up and free memory
    freeUserMemory();
    freeAccountMemory();
    freeTransactionMemory();
    return 0;
}