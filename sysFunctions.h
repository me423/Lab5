#ifndef SYSFUNCTIONS_H
#define SYSFUNCTIONS_H

#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int BOOL;
typedef int USERTYPE;

#define NOTUSER 0
#define OPERATOR 1
#define ADMIN 2

#define TRUE 1
#define FALSE 0

typedef struct User {
    char login[30];
    char password[30];
    char firstname[30];
    char secondname[30];
    BOOL isAdmin;
} User;

sqlite3 *db;

USERTYPE logIn(char *login, char *password);

USERTYPE authentification(char *login, char *password);

BOOL registration(char *firstname, char *lastname, char *login, char *password, BOOL isAdmin);

BOOL deleteUser(char *login);

//accountNumber is an id in a table
BOOL addMoney(int accountNumber, double sum);

//accountNumber is an id in a table
BOOL checkBalance(int accountNumber, double *balance);

//accountNumber is an id in a table
BOOL provideOverdraft(int accountNumber, double sum);

BOOL onOverdraft(int accountNumber);

BOOL createNewAccount(double balance, int clientID, char *type);

//accountNumber is an id in a table
BOOL deleteAccount(int accountNumber);

//AcNumber is an id in a table
BOOL deliverMoneyFromAcToAc(int srcAcNumber, int dstAcNumber, double sum);

BOOL addClient(char *firstname, char *lastname, char *passportNumber, char *birthdate, char *photo);

BOOL deleteClient(char *passport);

BOOL showClientsAccount(char *passportNumber);

#endif