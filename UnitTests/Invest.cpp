#include "pch.h"
#include "CppUnitTest.h"

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


namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		// Check if account balance is updated after investment
		TEST_METHOD(is_Account_Updated_True)
		{
			Market newMarket;
			char* marketName = "Market Name";
			snprintf(newMarket.name, 49, "%s", marketName);
			newMarket.chanceOfSuccess = 50;
			newMarket.Trend = 14;

			Account acc;
			char* accName = "Username";
			char* accType = "Checking";
			double initialBalance = 500.00;
			snprintf(acc.username, 49, "%s", accName);
			snprintf(acc.accountType, 20, "%s", accType);
			acc.balance = initialBalance;
			double balance = newInvestment(&acc, newMarket, 400);
			Assert::AreNotEqual(initialBalance, balance);
		}

		TEST_METHOD(is_InvestmentInitialized_False)
		{
			Market newMarket;
			char* marketName = "Market Name";
			snprintf(newMarket.name, 49, "%s", marketName);
			newMarket.chanceOfSuccess = 50;
			newMarket.Trend = 14;

			Account acc;
			char* accName = "Username";
			char* accType = "Checking";
			double initialBalance = 500.00;
			snprintf(acc.username, 49, "%s", accName);
			snprintf(acc.accountType, 20, "%s", accType);
			acc.balance = initialBalance;
			double balance = newInvestment(&acc, newMarket, 600);
			Assert::AreEqual(acc.balance, 500.00);
		}

		TEST_METHOD(InvestmentInitialized_TooHigh_True)
		{
			Market newMarket;
			char* marketName = "Market Name";
			snprintf(newMarket.name, 49, "%s", marketName);
			newMarket.chanceOfSuccess = 50;
			newMarket.Trend = 14;

			Account acc;
			char* accName = "Username1";
			char* accType = "Savings";
			double initialBalance = 100.00;
			snprintf(acc.username, 49, "%s", accName);
			snprintf(acc.accountType, 20, "%s", accType);
			acc.balance = initialBalance;
			double balance = newInvestment(&acc, newMarket, 1000);
			Assert::AreEqual(balance, 0.00);
		}

		TEST_METHOD(InvestmentInitialized_InvestmentFailure_True)
		{
			Market newMarket;
			char* marketName = "Market Name";
			snprintf(newMarket.name, 49, "%s", marketName);
			newMarket.chanceOfSuccess = 0;
			newMarket.Trend = 14;

			Account acc;
			char* accName = "Username1";
			char* accType = "Savings";
			double initialBalance = 100.00;
			snprintf(acc.username, 49, "%s", accName);
			snprintf(acc.accountType, 20, "%s", accType);
			acc.balance = initialBalance;
			double balance = newInvestment(&acc, newMarket, 50);
			Assert::AreEqual(balance, 0.00);
		}

	};
}
