#define _CRT_SECURE_NO_WARNINGS

#include "account_management.h"
#include "transactions.h"


//define Market Struct
typedef struct
{
    char name[50];
    int chanceOfSuccess;
    int Trend;
} Market;

//functionsA
void Invest(int marketCount);
int getAccount(const char* sender);
Market CreateRandomMarket(int i);
double newInvestment(Account* acc, Market market, int inputMoney);