#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_NAME_LEN 50

// User Structure
typedef struct {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int status; // 1 for active, 0 for locked
    int failedAttempts;
} User;

void initializeUsers();
void saveUsersToFile();
void loadUsersFromFile();
void registerUser();
void loginUser();
void freeUserMemory();

extern char currentUser[MAX_USERNAME_LEN];
extern int userCount;
extern int maxUsers;
extern User* users;

#endif // USER_AUTHENTICATION_H

