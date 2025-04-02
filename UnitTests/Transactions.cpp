#include "pch.h"
#include "CppUnitTest.h"
#define _CRT_SECURE_NO_WARNINGS
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
extern "C" Account* accounts;
extern "C" extern Transaction** transactions;
extern "C" extern int* transactionCount;
extern "C" int accountCount;
extern "C" extern char currentUser[MAX_USERNAME_LEN];
extern "C" extern int userCount;
extern "C" extern int maxUsers;
extern "C" extern User* users;

namespace TransactionsTests {

    TEST_CLASS(TransactionsTests)
    {
    public:
        TEST_METHOD(Deposit_ValidAmount_Success) {
            Account acc;
            char* accName = "Username2";
            char* accType = "Checking";
            double initialBalance = 500.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;

            deposit("Checking", 50.0);

            Assert::AreEqual(500.00, acc.balance);
        }

        // Test deposit with zero amount
        TEST_METHOD(Deposit_ZeroAmount_Error) {
            Account acc;
            char* accName = "Username3";
            char* accType = "Checking";
            double initialBalance = 200.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            deposit("Checking", 0.0);
            Assert::AreEqual(200.0, acc.balance);
        }

        // Test deposit with negative amount
        TEST_METHOD(Deposit_NegativeAmount_Error) {
            Account acc;
            char* accName = "Username4";
            char* accType = "Investing";
            double initialBalance = 500.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            deposit("Investing", -50.0);
            Assert::AreEqual(500.00, acc.balance);
        }

        // Test withdrawal with sufficient funds
        TEST_METHOD(Withdraw_SufficientFunds_Success) {
            Account acc;
            char* accName = "Username4";
            char* accType = "Savings";
            double initialBalance = 50.00;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            withdraw("Savings", 50.0);
            Assert::AreEqual(50.0, acc.balance);
        }

        // Test withdrawal with insufficient funds
        TEST_METHOD(Withdraw_InsufficientFunds_Error) {
            Account acc;
            char* accName = "Username4";
            char* accType = "Checking";
            double initialBalance = 20;
            snprintf(acc.username, 49, "%s", accName);
            snprintf(acc.accountType, 20, "%s", accType);
            acc.balance = initialBalance;
            withdraw("Checking", 50.0);
            Assert::AreEqual(20.0, acc.balance);
        }

        // Test transfer between valid accounts
        TEST_METHOD(Transfer_ValidAccounts_Success) {
            Account acc1;
            char* acc1Name = "sender";
            char* acc1Type = "Savings";
            double initialBalance = 250;
            snprintf(acc1.username, 49, "%s", acc1Name);
            snprintf(acc1.accountType, 20, "%s", acc1Type);
            acc1.balance = initialBalance;
            Account acc2;
            char* acc2Name = "receiver";
            char* acc2Type = "Checking";
            double initialBalance1 = 150;
            snprintf(acc2.username, 49, "%s", acc2Name);
            snprintf(acc2.accountType, 20, "%s", acc2Type);
            acc2.balance = initialBalance1;
            transfer("sender", "Savings", "receiver", "Checking", 50.0);
            Assert::AreEqual(250.0, acc1.balance);
            Assert::AreEqual(150.0, acc2.balance);
        }

        // Test transfer with insufficient funds
        TEST_METHOD(Transfer_InsufficientFunds_Error) {
            Account acc1;
            char* accName = "sender3";
            char* accType = "Savings";
            double initialBalance = 50;
            snprintf(acc1.username, 49, "%s", accName);
            snprintf(acc1.accountType, 20, "%s", accType);
            acc1.balance = initialBalance;
            Account acc2;
            char* acc1Name = "receiver3";
            char* acc1Type = "Checking";
            double initialBalance1 = 100;
            snprintf(acc2.username, 49, "%s", acc1Name);
            snprintf(acc2.accountType, 20, "%s", acc1Type);
            acc2.balance = initialBalance1;
            transfer("sender", "Savings", "receiver", "Checking", 100.0);
            Assert::AreEqual(50.0, acc1.balance);
            Assert::AreEqual(100.0, acc2.balance);
        }

    };
}
