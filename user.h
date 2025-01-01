#ifndef USER_H
#define USER_H

#include "bankaccount.h"
#include "transaction.h"

typedef struct user {
    char userID[20];
    char userPassword[20];
    char name[50];
    char mobile[15];
    char email[50];
    char address[100];
    bankAccount account;
    transaction *transactions;
    struct user *next;
} user;


user* userLogin(user *head);
user *userMenu(user *loggedInUser, user *head);
user *deposit(user *loggedInUser);
user *withdraw(user *loggedInUser);
user *transfer(user *loggedInUser, user *head);
void checkBalance(user *loggedInUser);
void viewTransactionHistory(user* loggedInUser) ;

#endif
