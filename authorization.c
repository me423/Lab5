#include "sysFunctions.h"
#include "cli.h"
#include "sqlite3.h"
#include <stdio.h>

USERTYPE startLogin()
{
    char login[30], password[30];
    
    printf("Enter login: ");
    scanf("%s", login);
    printf("Enter password: ");
    scanf("%s", password);
    
    return logIn(login, password);
}

USERTYPE logIn(char *login, char *password)
{
    return authentification(login, password);
}

USERTYPE authentification(char *login, char *password)
{
    char *sql = "SELECT isAdmin FROM BANK_USERS_TBL WHERE login = ? and password = ?";
    int ans;
    sqlite3_stmt * res;
    
    ans = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (ans != SQLITE_OK)
    {
        printf("Operation failed. %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(res);
        return NOTUSER;
    }
    
    sqlite3_bind_text(res, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);
    
    if (sqlite3_step(res) == SQLITE_ROW)
    {
        int isAdmin = sqlite3_column_int(res, 0);
        sqlite3_finalize(res);
        if (isAdmin == 1)
            return ADMIN;
        else
            return OPERATOR;
    }
    sqlite3_finalize(res);
    return NOTUSER;
}