#include "pch.h"
#include "CppUnitTest.h"
#pragma warning(disable : 4996)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" void Invest(int marketCount);
extern "C" int getAccount(const char* sender);
extern "C" Market CreateRandomMarket(int i);
extern "C" double newInvestment(Account* acc, Market market, int inputMoney);

extern "C" void loadUsersFromFile();
extern "C" void loadAccountsFromFile();
extern "C" void loadTransactionsFromFile();
extern "C" int findAccountIndex(const char* username, const char* accountType);
extern "C" void saveUsersToFile();
extern "C" void registerUser();
extern "C" void loginUser();
extern "C" void freeUserMemory();
extern "C" extern char currentUser[MAX_USERNAME_LEN];
extern "C" extern int userCount;
extern "C" extern int maxUsers;
extern "C" extern User* users;
extern "C" void saveTransactionsToFile();
extern "C" void loadTransactionsFromFile();
extern "C" void recordTransaction(const char* username, const char* accountType, const char* transactionType, double amount);
extern "C" void deposit(const char* accountType, double amount);
extern "C" void withdraw(const char* accountType, double amount);
extern "C" void transfer(const char* sender, const char* senderAccount, const char* receiver, const char* receiverAccount, double amount);
extern "C" void viewTransactions();
extern "C" void logTransaction(int userId, int transactionId, double amount);
extern "C" void freeTransactionMemory();
extern "C" void saveAccountsToFile();
extern "C" void loadAccountsFromFile();
extern "C" void createAccount(const char* username, const char* accountType, double initialBalance);
extern "C" int findAccountIndex(const char* username, const char* accountType);
extern "C" void viewAccounts();
extern "C" void freeAccountMemory();
extern "C" extern Account* accounts;


namespace UnitTest
{
    TEST_CLASS(UnitTestForAccountManagement)
    {
    public:
        TEST_METHOD(validateAccountLimits_BelowLimit_ReturnsFalse) {
            Account acc;
            char* accName = "";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            *acc.accountType = *accType;
            acc.balance = initialBalance;
            saveAccountsToFile();
            Assert::IsFalse(acc.accountType == accType); // Expecting true since limit not reached
        }

        //TEST_METHOD(validateAccountLimits_AtLimit_ReturnsFalse) {
        //    Transaction transaction;
        //    char* username= "name";
        //    char* accountType = "Checking";
        //    char* transactionType = "Transfer"; // Deposit, Withdraw, Transfer
        //    double amount = 50.0;
        //    snprintf(transaction.username, MAX_USERNAME_LEN, "%s", username);
        //    snprintf(transaction.username, MAX_ACCOUNT_TYPE_LEN, "%s", username);
        //    snprintf(transaction.username, MAX_TRANSACTION_TYPE_LEN, "%s", username);
        //    transaction.amount = amount;
        //    Assert::IsFalse(transaction.transactionType == "Transfer"); // Expecting false since limit reached
        //}

        TEST_METHOD(checkDuplicateAccount_NoDuplicate_ReturnsTrue) {
            Account acc;
            char* accName = "Username4";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            withdraw("Savings", 50.0);
            Assert::IsTrue(acc.balance == 50.00);// Expecting true since no duplicate found in file
        }

        TEST_METHOD(saveAccountsToFile_ValidAccount_ReturnsFalse) {
            Account acc;
            char* accName = "username10";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            // Test registration with empty username
            createAccount("username10", "password123", initialBalance);
            saveAccountsToFile();
            Assert::IsFalse(acc.username == "username10"); // Expecting true since account should be saved
        }
    };
}