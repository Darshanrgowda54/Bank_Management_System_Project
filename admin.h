#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"


typedef struct Admin
{
    char adminID[20];
    char adminPassword[20];
} Admin;


int adminLogin();
user *adminMenu(user *head);
user *createAccount(user *head);
user *deleteAccount(user *head);
user *updateAccount(user *head);
user *viewAccountDetails(user *head);
user *sortAccountsType(user* head);


#endif
