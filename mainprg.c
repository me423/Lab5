#include "sysFunctions.h"
#include "cli.h"
#include "sqlite3.h"
#include <stdio.h>

void showMenu(USERTYPE usertype);
int makeChoice(USERTYPE usertype);

int main()
{
    int choice = 0;
    //sqlite3_open("/Users/admin/LABS/lab5reserve/BANK_DB.db", &db);
    sqlite3_open("BANK_DB.db", &db);
    USERTYPE currentUser = NOTUSER;
    do
    {
        showMenu(currentUser);
        choice = makeChoice(currentUser);
        if (choice == 0)
            break;
        if (currentUser == NOTUSER)
        {
            currentUser = startLogin();
            continue;
        }
        switch (choice) {
            case 1:
                startAddMoney();
                break;
            case 2:
                startGetMoney();
                break;
            case 3:
                startCheckBalance();
                break;
            case 4:
                startDeliverMoney();
                break;
            case 5:
                startShowClientsAccount();
                break;
            case 6:
                startRegistration();
                break;
            case 7:
                startDeleteUser();
                break;
            case 8:
                startProvideOverdraft();
                break;
            case 9:
                startOnOverdraft();
                break;
            case 10:
                startCreateNewAccount();
                break;
            case 11:
                startDeleteAccount();
                break;
            case 12:
                startAddClient();
                break;
            case 13:
                startDeleteClient();
            default:
                break;
        }
    }while (TRUE);
    
    
    sqlite3_close(db);
    return 0;
}

void showMenu(USERTYPE usertype)
{
    printf("------------------MENU------------------\n");
    printf("0) Exit\n");
    if (usertype == NOTUSER)
    {
        printf("1) Sign in\n");
        return;
    }
    
    printf("1) Add money to account\n");
    printf("2) Get money from account\n");
    printf("3) Check balance on account\n");
    printf("4) Deliver money from one account to another\n");
    printf("5) Show client accountes\n");
    
    if (usertype == OPERATOR)
        return;
    printf("6) Register new user\n");
    printf("7) Delete user\n");
    printf("8) Provide overdraft\n");
    printf("9) Add possibility of overdraft\n");
    printf("10) Create new account\n");
    printf("11) Delete account\n");
    printf("12) Add new client\n");
    printf("13) Delete client\n");
}

int makeChoice(USERTYPE usertype)
{
    int rBoundary = 1, lBoundary = 0, choice = 1;
    if (usertype == OPERATOR)
        rBoundary = 5;
    if (usertype == ADMIN)
        rBoundary = 13;
    printf("Select menu point: ");
    do
    {
        scanf("%d", &choice);
        getchar();
        if (choice < lBoundary || choice > rBoundary)
            printf("Incorrect menu point. Try again:\n");
        break;
    }while (TRUE);
    return choice;
}
/*
    USERTYPE startLogin();
 BOOL startRegister();
 BOOL startDeleteUser();
  BOOL startAddMoney();
  BOOL startGetMoney();
  BOOL startCheckBalance();
 BOOL startProvideOverdraft();
 BOOL onOverdraft(int accountNumber);
 BOOL startCreateNewAccount();
 BOOL startDeleteAccount();
  BOOL startDeliverMoney();
 BOOL startAddClient();
 BOOL startDeleteClient();
  BOOL startShowClientsAccount();
*/