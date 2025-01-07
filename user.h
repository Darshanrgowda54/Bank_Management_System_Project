#ifndef USER_H
#define USER_H

#include "bankaccount.h"
#include "transaction.h"

typedef struct user {
    char userID[10];
    char userPassword[10];
    char name[30];
    char mobile[12];
    char email[30];
    char address[30];
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
