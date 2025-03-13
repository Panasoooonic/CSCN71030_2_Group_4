#pragma once

typedef struct {
    char firstName[50];
    char lastName[50];
    char username[50];
    char password[50];
    int status;
} Account;

void createAccount();
int login();
void viewAccounts();
