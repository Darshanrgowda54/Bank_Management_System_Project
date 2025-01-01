#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileoperations.h"

int adminLogin()
{
    char adminID[20], adminPassword[20];

    printf("Enter Admin ID: ");
    scanf("%s", adminID);
    printf("Enter Admin Password: ");
    scanf("%s", adminPassword);

    if (strcmp(adminID, "123") == 0 && strcmp(adminPassword, "123") == 0)
    {
        return 1;
    }
    return 0;
}



enum adminMenuOption
{
    CREATACCOUNT = 1,
    DELETEACCOUNT,
    UPDATEACCOUNT,
    VIEWACCOUNTDETAILS,
    SORTACCOUNTSTYPE,
    LOGOUT
};


user *adminMenu(user *head)
{
    int choice;

    while (1) {
        printf("\n________ Admin Menu ________\n");
        printf("1. Create Account\n");
        printf("2. Delete Account\n");
        printf("3. Update Account\n");
        printf("4. view Account Details\n");
        printf("5. Sort Account Type\n");
        printf("6. Logout from Admin\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case CREATACCOUNT:
            head = createAccount(head);
            break;

        case DELETEACCOUNT:
            head = deleteAccount(head);
            break;

        case UPDATEACCOUNT:
            head = updateAccount(head);
            break;

        case VIEWACCOUNTDETAILS:
            viewAccountDetails(head);
            break;

        case SORTACCOUNTSTYPE:
            head = sortAccountsType(head);
            break;

        case LOGOUT:
            printf("________ Logout from Admin ________\n");
            printf("\n");
            return head ;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return head;
}



int accountCounter = 1001;

user *createAccount(user * head)
{
    user *newuser = (user*)malloc(sizeof(user));
    if(newuser == NULL)
    {
        printf("Memory Allocation Failed\n");
        return head;
    }

    printf("Enter User ID: ");
    scanf(" %[^\n]", newuser->userID);
    printf("Enter Password: ");
    scanf(" %[^\n]", newuser->userPassword);
    printf("Enter Name: ");
    scanf(" %[^\n]", newuser->name);
    printf("Enter Mobile Number: ");
    scanf(" %[^\n]", newuser->mobile);
    printf("Enter Email: ");
    scanf("%s", newuser->email);
    printf("Enter Address: ");
    scanf(" %[^\n]", newuser->address);

    newuser->next = NULL;


    while (1)
    {
        printf("Enter Account Type (Savings/Current): ");
        scanf("%s", newuser->account.accountType);
        if (strcmp(newuser->account.accountType, "Savings") == 0 ||strcmp(newuser->account.accountType, "Current") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Account Type. Please enter 'Savings' or 'Current'.\n");
        }
    }


    while (1)
    {
        int Duplicate = 0;
        user *temp = head;

        while (temp != NULL)
        {
            if (temp->account.accountNumber == accountCounter)
            {
                Duplicate = 1;
                break;
            }
            temp = temp->next;
        }

        if (Duplicate == 0)
        {
            newuser->account.accountNumber = accountCounter++;
            break;
        }
        else
        {
            accountCounter++;
        }
    }


    printf("Enter Initial Amount: ");
    scanf("%f", &newuser->account.balance);
    if (newuser->account.balance < 0)
    {
        printf("Initial amount cannot be negative.\n");
        newuser->account.balance = 0;
    }

    newuser->transactions = NULL;

    if(head == NULL)
    {
        head = newuser;
    }
    else
    {
        user *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newuser;
    }

    //saveToFile(head);

    appendNewAccount(newuser);

    printf("Account created successfully with Account Number: %d\n", newuser->account.accountNumber);
    return head;
}


user* deleteAccount(user* head)
{
    user *temp = head;
    user *previous = NULL;
    int accountNumber;

    printf("Enter Account Number to Delete: ");
    scanf("%d", &accountNumber);

    while(temp != NULL)
    {
        if(temp->account.accountNumber == accountNumber)
        {
            if (previous == NULL)
            {
                head = temp->next;
            }
            else
            {
                previous->next = temp->next;
            }
            free(temp);

            // 1.deleteFromFile(head, accountNumber);

            deleteRecord(accountNumber);

            printf("Account Number %d deleted successfully.\n", accountNumber);
            return head;
        }
        previous = temp;
        temp = temp->next;
    }
    printf("Account Number %d not found.\n", accountNumber);
    return head;
}


enum  updateAccountMenu{
    NAME = 1,
    MOBILENUMBER,
    EMAIL,
    ADDRESS,
    EXIT
} ;


user *updateAccount(user * head)
{
    user *temp = head;
    int accountNumber;
    int choice;

    printf("Enter Account Number to Update: ");
    scanf("%d", &accountNumber);

    while (temp !=NULL)
    {
        if(temp->account.accountNumber == accountNumber)
        {
            while (1)
            {
                printf("\nSelect the field you want to update:\n");
                printf("1. Name\n");
                printf("2. Mobile Number\n");
                printf("3. Email\n");
                printf("4. Address\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case NAME:
                    printf("Enter New Name: ");
                    scanf(" %[^\n]", temp->name);
                    updateRecord(temp);
                    //updateToFile(head);
                    printf("Name updated successfully.\n");
                    break;
                case MOBILENUMBER:
                    printf("Enter New Mobile Number: ");
                    scanf(" %[^\n]", temp->mobile);
                    updateRecord(temp);
                    //updateToFile(head);
                    printf("Mobile number updated successfully.\n");
                    break;
                case EMAIL:
                    printf("Enter New Email: ");
                    scanf("%s", temp->email);
                    updateRecord(temp);
                    //updateToFile(head);
                    printf("Email updated successfully.\n");
                    break;
                case ADDRESS:
                    printf("Enter New Address: ");
                    scanf(" %[^\n]", temp->address);
                    updateRecord(temp);
                    //updateToFile(head);
                    printf("Address updated successfully.\n");
                    break;
                case EXIT:
                    printf("Exiting update menu\n\n");
                    return head;
                default:
                    printf("Invalid choice. Please try again.\n");
                }
            }
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
    return head;
}


user *viewAccountDetails(user* head)
{
    user *temp = head;
    int accountNumber;

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while(temp != NULL)
    {
        if(temp->account.accountNumber == accountNumber)
        {
            printf("\n________ Account Details ________\n");
            printf("Account Number: %d\n", temp->account.accountNumber);
            printf("Name: %s\n", temp->name);
            printf("Mobile: %s\n", temp->mobile);
            printf("Email: %s\n", temp->email);
            printf("Address: %s\n", temp->address);
            printf("Account Type: %s\n", temp->account.accountType);
            printf("Balance: %.2f\n", temp->account.balance);
            return head;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
    return head;
}




user *sortAccountsType(user* head)
{
    if (head == NULL || head->next == NULL)
    {
        printf("No accounts found or only one account exists. Sorting not required.\n");
        return head;
    }

    int swapped = 1;
    user *lptr = NULL;

    while (swapped)
    {
        swapped = 0;
        user *ptr1 = head;
        user *prev = NULL;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->account.accountType, ptr1->next->account.accountType) > 0)
            {
                user *temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;

                if (prev == NULL) {
                    head = temp;
                } else {
                    prev->next = temp;
                }

                prev = temp;
                swapped = 1;
            }
            else
            {
                prev = ptr1;
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    }

    printf("________ Accounts Sorted by Account Type ________\n");
    printf("\n");
    user *temp = head;
    while (temp != NULL)
    {
        printf("Account Number: %d\n", temp->account.accountNumber);
        printf("Name: %s\n", temp->name);
        printf("Account Type: %s\n", temp->account.accountType);
        printf("Balance: %.2f\n", temp->account.balance);
        printf("-------------------------------------------\n");
        temp = temp->next;
    }

    printf("Accounts sorted by account type successfully.\n");
    return head;
}

