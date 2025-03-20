#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "User Authentication.h"
#include "AccManagement.h"


int main() {
    int choice;
    while (1) {
        printf("\n1. Create Account\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: createAccount(); break;
        case 2:
            if (login()) {
                int loggedInChoice;
                while (1) {
                    printf("\n1. View All Accounts\n2. Logout\nEnter your choice: ");
                    scanf("%d", &loggedInChoice);
                    getchar();

                    if (loggedInChoice == 1) {
                        viewAccounts();
                    }
                    else if (loggedInChoice == 2) {
                        printf("Logged out successfully.\n");
                        break;
                    }
                    else {
                        printf("Invalid choice.\n");
                    }
                }
            }
            break;
        case 3: exit(0);
        default: printf("Invalid choice.\n");
        }
    }
}