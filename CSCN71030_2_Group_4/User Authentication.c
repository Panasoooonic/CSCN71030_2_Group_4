#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "User Authentication.h"

#define ACTIVE 1
#define LOCKED 0
#define MAX_ATTEMPTS 3

void createAccount() {
    FILE* file = fopen("accounts.txt", "a+");  // Open file in read/write mode
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    Account acc;
    Account tempAcc;  // Temporary account structure for reading file data
    char usernameToCheck[50];
    int usernameExists = 0;

    // Prompt user for first name, last name, and username
    printf("Enter First Name: ");
    scanf("%49s", acc.firstName);
    printf("Enter Last Name: ");
    scanf("%49s", acc.lastName);

    // Check for existing username
    do {
        usernameExists = 0;
        printf("Enter Username (No space): ");
        scanf("%49s", acc.username);

        // Read through the file to check for an existing username
        rewind(file);  // Reset file pointer to the beginning
        while (fscanf(file, "%49s %49s %49s %49s %d", tempAcc.firstName, tempAcc.lastName, usernameToCheck, tempAcc.password, &tempAcc.status) != EOF) {
            if (strcmp(acc.username, usernameToCheck) == 0) {
                usernameExists = 1;
                printf("Username already exists. Choose another username.\n");
                break;  // Exit the loop to prompt the user again
            }
        }
    } while (usernameExists);  // Repeat the loop if the username already exists

    // Prompt for password
    do {
        printf("Enter Password: ");
        scanf("%49s", acc.password);

        if (strlen(acc.password) <= 8) {
            printf("Password must be longer than 8 characters. Try again.\n");
        }
        else if (strlen(acc.password) >= 15) {
            printf("Password must be shorter than 15 characters. Try again.\n");
        }

    } while (strlen(acc.password) < 8 || strlen(acc.password) > 15);  // Ensure valid password length

    acc.status = ACTIVE;

    // Write the new account details to the file
    fprintf(file, "%s %s %s %s %d\n", acc.firstName, acc.lastName, acc.username, acc.password, acc.status);
    fclose(file);

    printf("Account created successfully!\n");
}

int login() {
    FILE* file = fopen("accounts.txt", "r+");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }

    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    Account acc;
    int found = 0, attempts = 0;
    while (fscanf(file, "%49s %49s %49s %49s %d", acc.firstName, acc.lastName, acc.username, acc.password, &acc.status) != EOF) {
        if (strcmp(acc.username, username) == 0) {
            found = 1;
            if (acc.status == LOCKED) {
                printf("Account is locked. Contact support.\n");
                fclose(file);
                return 0;
            }

            while (attempts < MAX_ATTEMPTS) {
                if (strcmp(acc.password, password) == 0) {
                    printf("Login successful! Welcome %s %s!\n", acc.firstName, acc.lastName);
                    fclose(file);
                    return 1;
                }
                else {
                    attempts++;
                    printf("Incorrect password. Attempts left: %d\n", MAX_ATTEMPTS - attempts);
                    if (attempts < MAX_ATTEMPTS) {
                        printf("Re-enter Password: ");
                        scanf("%49s", password);
                    }
                }
            }

            printf("Too many failed attempts. Account is now locked.\n");
            FILE* tempFile = fopen("temp.txt", "w");
            rewind(file);
            while (fscanf(file, "%49s %49s %49s %49s %d", acc.firstName, acc.lastName, acc.username, acc.password, &acc.status) != EOF) {
                if (strcmp(acc.username, username) == 0) {
                    acc.status = LOCKED;
                }
                fprintf(tempFile, "%s %s %s %s %d\n", acc.firstName, acc.lastName, acc.username, acc.password, acc.status);
            }
            fclose(file);
            fclose(tempFile);
            remove("accounts.txt");
            rename("temp.txt", "accounts.txt");
            return 0;
        }
    }

    fclose(file);
    if (!found) {
        printf("Username not found.\n");
    }
    return 0;
}

void viewAccounts() {
    FILE* file = fopen("accounts.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    Account acc;
    printf("\nAll Accounts:\n");
    while (fscanf(file, "%49s %49s %49s %49s %d", acc.firstName, acc.lastName, acc.username, acc.password, &acc.status) != EOF) {
        printf("%s %s (%s) - %s\n", acc.firstName, acc.lastName, acc.username, acc.status == ACTIVE ? "Active" : "Locked");
    }
    fclose(file);
}