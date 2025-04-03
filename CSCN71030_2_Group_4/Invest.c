#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "Invest.h"
#include "account_management.h"

#pragma warning(disable : 4996)


//Market Names
char* marketNames[] = {
    "Amazeon             ",
    "Consistant Market   ",
    "Tyota               ",
    "Liban Enterprises   ",
    "Bite-coin           ",
    "Investa             ",
    "Nasir Productions   ",
    "Console Bank        ",
    "Bestest Construction",
    "Please Invest      ",
    "Duke Industries    ",
    "Giigle             ",
    "NULL             ",
};


//Market number ranges
int investRanges[12][2] = {
    {80, 100}, // min range, max range
    {1, 10},
    {70, 100},
    {45, 100},
    {74, 100},
    {78, 100},
    {5, 100},
    {95, 100},
    {1, 55},
    {23, 84},
    {56, 100},
    {90, 100},
};

// Sssign random values to the market based on ranges
Market CreateRandomMarket(int i)
{
    Market newMarket;
    snprintf(newMarket.name, 49, "%s", marketNames[i]);

    int min = investRanges[i][0];
    int max = investRanges[i][1];

    newMarket.chanceOfSuccess = rand() % (max - min + 1) + min;
    newMarket.Trend = rand() % (20 - -20 + 1) + -20;

    return newMarket;
}


// Get how much money user wants to invest then calculates a random answer based on ranges
double newInvestment(Account* acc, Market market, int inputMoney)
{
    if (inputMoney < acc->balance)
    {
        double isSuccess = rand() % (100 - 1);
        if (isSuccess <= market.chanceOfSuccess) // win
        {
            acc->balance -= inputMoney;
            int storedValue = market.Trend;
            market.Trend = rand() % (20 - market.Trend) + market.Trend;

            float multiplier = (float)market.Trend / 100;
            double newBalance = inputMoney + (inputMoney * multiplier);
            acc->balance += newBalance;

            printf("In 30 days, the market value of %s went from %d%% to: %d%%  you now have: %.1f$, \n", market.name, storedValue, market.Trend, acc->balance);
            // recordTransaction(currentUser, "Investing", "Investment", newBalance);
            return newBalance;
        }
        else // lose
        {
            acc->balance -= inputMoney;
            int storedValue = market.Trend;
            market.Trend = rand() % (-20 + market.Trend) + market.Trend;

            float multiplier = (float)market.Trend / 100;
            double newBalance = inputMoney + (inputMoney * multiplier);
            acc->balance += newBalance;

            printf("In 30 days, the market value of %s went from %d%% to: %d%%  you now have: %.1f$, \n", market.name, storedValue, market.Trend, acc->balance);
            // recordTransaction(currentUser, "Investing", "Investment", newBalance);
            return newBalance;
        }
    }
    else
    {
        
        printf("\n You do not have enough money in your balance!");
        return 0.00;
    }
}

// finds the current accouont the user is using
int getAccount(const char* sender)
{
    int accountIndex = findAccountIndex(currentUser, "Investing");
    if (accountIndex == -1) {
        printf("Account not found!\n");
        exit(0);
    }
    return accountIndex;
}


// primary function which sets up and displays all the markets
void Invest(int marketCount)
{
    srand(time(0));
    int choice;
    int accountIndex = getAccount(currentUser);
    int marketNum = marketCount;
    Market marketList[13];
    Account acc = accounts[accountIndex];

    // Create Markets with randomness
    for (int i = 0; i <= marketNum; i++)
    {
        marketList[i] = CreateRandomMarket(i);
    }

    printf("Welcome to the investment page!\n\n");

    // display markets to the user
    for (int i = 1; i <= marketNum; i++)
    {
        int currentIndex = i - 1;
        printf("%d. %s : ", i, marketList[currentIndex].name);
        if (marketList[currentIndex].Trend > 0)
        {
            printf(" UP %d%%", marketList[currentIndex].Trend);
        }
        else
        {
            printf(" DOWN %d%%", marketList[currentIndex].Trend);
        }
        printf("\n");
    }

    // Select the market to choose
    printf("Please select one of the markets you would like to invest in: ");
    scanf_s("%d", &choice);

    if ((choice > 0 && choice <= 12) && choice <= marketNum)
    {
        int inputMoney;
        printf("Please enter how much you would like to invest: ");
        scanf_s("%d", &inputMoney);
        double newBalance = newInvestment(&acc, marketList[choice - 1], inputMoney);
        if (newBalance > 0.00 || newBalance < 0.00)
        {
            accounts[accountIndex].balance = acc.balance;
            recordTransaction(currentUser, "Investing", "Investment", newBalance);
            saveAccountsToFile();
        }

    }
    else
    {
        printf("Not a valid market!");
    }


    return;
}