#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "fileoperations.h"

enum mainMenuOption
{
    ADMIN = 1,
    USER,
    EXIT
};

int mainMenu()
{
    user *head = NULL;

    head = loadAccountsFromFile(head);
    loadTransactionsFromFile(head);

    //head = loadUserDataFromFile("users.txt", "transactions.txt");

    int choice;

    while (1)
    {
        printf("\n________ Bank Management System ________\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case ADMIN:
            if (adminLogin())
            {
                printf("Admin login Successful.\n");
                head = adminMenu(head);
            }
            else
            {
                printf("Invalid admin credentials.\n");
            }
            break;

        case USER:
        {
            user *loggedInUser = userLogin(head);
            if (loggedInUser != NULL)
            {
                userMenu(loggedInUser, head);
            }
            break;
        }

        case EXIT:
            //saveUserDataToFile(head, "users.txt", "transactions.txt");
            printf("Thank you. Please visit again\n");
            free(head);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}
