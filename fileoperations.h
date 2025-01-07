#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include "user.h"


user* loadAccountsFromFile(user *head);
void saveAccountToFile(user *newuser);
void updateAccountInFile(int accountNumber, int fieldToUpdate, void *newValue);


void updateBalanceAfterTransaction(user *userRef, float amount);
void saveTransactionToFile(user *userRef, transaction *newTransaction);
void loadTransactionsFromFile(user *head);


#endif
