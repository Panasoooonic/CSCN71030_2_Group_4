#define _CRT_SECURE_NO_WARNINGS
#include "user_authentication.h"

char currentUser[MAX_USERNAME_LEN] = "";
int userCount = 0;
int maxUsers = 100;
User* users;

void saveUsersToFile() {
    FILE* file = fopen("users.txt", "w");
    if (!file) {
        printf("Error opening users file!\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s;%s;%s;%s;%d;%d\n",
            users[i].firstName, users[i].lastName,
            users[i].username, users[i].password,
            users[i].status, users[i].failedAttempts);
    }
    fclose(file);
}

void loadUsersFromFile() {
    FILE* file = fopen("users.txt", "r");
    if (!file) return;
    userCount = 0;
    while (fscanf(file, "%49[^;];%49[^;];%49[^;];%49[^;];%d;%d\n",
        users[userCount].firstName, users[userCount].lastName,
        users[userCount].username, users[userCount].password,
        &users[userCount].status, &users[userCount].failedAttempts) == 6) {
        userCount++;
    }
    fclose(file);
}

void registerUser() {
    if (userCount >= maxUsers) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    User newUser;
    printf("Enter First Name: ");
    scanf("%s", newUser.firstName);
    printf("Enter Last Name: ");
    scanf("%s", newUser.lastName);

    // Check for duplicate username
    int isDuplicate;
    do {
        isDuplicate = 0;
        printf("Enter Username: ");
        scanf("%s", newUser.username);
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, newUser.username) == 0) {
                printf("Username already exists! Choose another one.\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate);

    // Ensure password length is between 8 and 15 characters
    do {
        printf("Enter Password (8-15 characters): ");
        scanf("%s", newUser.password);
        int len = strlen(newUser.password);
        if (len < 8 || len > 15) {
            printf("Invalid password length. Try again.\n");
        }
    } while (strlen(newUser.password) < 8 || strlen(newUser.password) > 15);

    newUser.status = 1;          // Account is active
    newUser.failedAttempts = 0;  // No failed attempts on registration
    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User registered successfully!\n");
}

void loginUser() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
    printf("Enter Username: ");
    scanf("%s", username);

    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Invalid username!\n");
        return;
    }

    // Check if the account is locked before proceeding
    if (users[userIndex].status == 0) {
        printf("Account is locked! Contact support.\n");
        return;
    }

    int attempts = 0;
    while (attempts < 3) {
        printf("Enter Password: ");
        scanf("%s", password);

        if (strcmp(users[userIndex].password, password) == 0) {
            // Successful login
            users[userIndex].failedAttempts = 0;  // Reset failed attempts on success
            strcpy(currentUser, username);
            saveUsersToFile();
            printf("Login successful!\n");
            return;
        }
        else {
            attempts++;
            users[userIndex].failedAttempts++;

            if (attempts < 3) {
                printf("Wrong password! Try again. (Attempt %d of 3)\n", attempts);
            }

            // Lock account after 3 failed attempts
            if (attempts == 3) {
                users[userIndex].status = 0;  // Lock the account
                saveUsersToFile();
                printf("Account locked after 3 failed attempts. Contact support to unlock.\n");
                return;
            }
        }
    }
}

void freeUserMemory() {
    if (users) {
        free(users);
        users = NULL;
    }
}