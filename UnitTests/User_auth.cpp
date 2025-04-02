#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

extern "C" void Invest(int marketCount);
extern "C" int getAccount(const char* sender);
extern "C" Market CreateRandomMarket(int i);
extern "C" double newInvestment(Account* acc, Market market, int inputMoney);
extern "C" void loginUser();
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


namespace UserAuthentication
{
    TEST_CLASS(UserAuthentication)
    {
    public:
        // Test for Empty Username during Registration
        TEST_METHOD(EmptyUsernameRegistration)
        {
            Account acc;
            char* accName = "";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            // Test registration with empty username
            createAccount("", "password123", initialBalance);
            loadAccountsFromFile();
            // Assert that registration fails due to empty username
            Assert::IsFalse(acc.username == accName);
        }

        // Test for Empty Password during Registration
        TEST_METHOD(EmptyPasswordRegistration)
        {
            // Test registration with empty passwor
            User newUser;
            char* firstName = "FirstName";
            char* lastName = "LastName";
            char* username = "user";
            char* result = "";
            snprintf(newUser.firstName, 49, "%s", firstName);
            snprintf(newUser.lastName, 49, "%s", lastName);
            snprintf(newUser.username, 49, "%s", username);
            snprintf(newUser.password, 49, "%s", result);
            newUser.status = 1;
            newUser.failedAttempts = 0;

            // Assert that registration fails due to empty password
            Assert::IsFalse(newUser.password == result);
        }

        // Test for Invalid Character in Username (Edge Case)
        TEST_METHOD(InvalidUsernameCharacters)
        {
            // Test registration with invalid character (space) in username
            Account acc;
            char* accName = "test user";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;

            createAccount("test user", "password123", 0.00);

            // Assert that registration fails due to invalid character in the username
            Assert::IsFalse(acc.username == accName);
        }
    };
}