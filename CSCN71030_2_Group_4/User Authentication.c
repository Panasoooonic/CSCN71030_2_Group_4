#define _CRT_SECURE_NO_WARNINGS
#include "user_authentication.h"

char currentUser[MAX_USERNAME_LEN] = "";
int userCount = 0;
int maxUsers = 100;
User* users = NULL;

// Initialize user storage
void initializeUsers() {
    users = (User*)malloc(maxUsers * sizeof(User));
    if (!users) {
        printf("Memory allocation failed for users.\n");
        exit(EXIT_FAILURE);
    }
}

// Free allocated memory for users
void freeUserMemory() {
    free(users);
}

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

// Register a new user
void registerUser() {
    if (userCount >= maxUsers) {
        maxUsers *= 2;
        users = (User*)realloc(users, maxUsers * sizeof(User));
        if (!users) {
            printf("Memory allocation failed. Cannot register more users.\n");
            return;
        }
    }

    User newUser;
    printf("Enter First Name: ");
    fgets(newUser.firstName, MAX_NAME_LEN, stdin);
    newUser.firstName[strcspn(newUser.firstName, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(newUser.lastName, MAX_NAME_LEN, stdin);
    newUser.lastName[strcspn(newUser.lastName, "\n")] = 0;

    int isDuplicate;
    do {
        isDuplicate = 0;
        printf("Enter Username: ");
        fgets(newUser.username, MAX_USERNAME_LEN, stdin);
        newUser.username[strcspn(newUser.username, "\n")] = 0;

        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, newUser.username) == 0) {
                printf("Username already exists! Choose another one.\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate);

    do {
        printf("Enter Password (8-15 characters): ");
        fgets(newUser.password, MAX_PASSWORD_LEN, stdin);
        newUser.password[strcspn(newUser.password, "\n")] = 0;

        int len = strlen(newUser.password);
        if (len < 8 || len > 15) {
            printf("Invalid password length. Try again.\n");
        }
    } while (strlen(newUser.password) < 8 || strlen(newUser.password) > 15);

    newUser.status = 1;
    users[userCount++] = newUser;
    saveUsersToFile();
    printf("User registered successfully!\n");
}

// Login function
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
            users[userIndex].failedAttempts = 0;  // Reset on success
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

            // Check if this was the third failed attempt
            if (attempts == 3) {
                users[userIndex].status = 0;  // Lock the account
                saveUsersToFile();
                printf("Account locked after 3 failed attempts. Contact support to unlock.\n");
                return;
            }
        }
    }
}